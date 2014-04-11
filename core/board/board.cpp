#include "board.h"
#include <algorithm>
#include <limits>
#include <sstream>
using namespace std;

//constructors
PushMe::Board::Board(int innerSizeX, int innerSizeY)
    :BoardBase(innerSizeX, innerSizeY)
{
    _fField = IntVector(-1);
    _fBlock.Position(IntVector(-1, 0));
    _innerBoard.resize(innerSizeX * innerSizeY, EMPTY_FIELD);
}
PushMe::Board::Board(const Board &other)
    :Board(other._innerSizeX, other._innerSizeY)
{
    for(auto &h:other._hBlocks)
        AddBlockH(h.Y(), h.LeftCell(), h.RightCell());
    for(auto &v:other._vBlocks)
        AddBlockV(v.X(), v.TopCell(), v.BottomCell());
    SetFinalField(other.GetFinalField().x, other.GetFinalField().y);
    SetBlockF(other._fBlock.X(), other._fBlock.Y());
}

//getters setters
int PushMe::Board::GetField(int x, int y) const
{
    if(_fBlock.X() == x && _fBlock.Y() == y) return FINAL_BLOCK;
    if(_fField == IntVector(x,y)) return FINAL_FIELD;
    if(!InBoundsInner(x,y)) return NOT_A_FIELD;
    return _innerBoard[innerIndex(x,y)];
}
int PushMe::Board::AddBlockH(int y, int leftCell, int rightCell)
{
    stringstream err;
    if(!InBoundsInner(leftCell, y) || !InBoundsInner(rightCell, y)){
        err<<"AddBlockH("<<y<<", "<<leftCell<<", "<<rightCell<<")\n"
                      <<"Can't add, because block would be out of bounds";
        throw std::logic_error(err.str());
    }
    for(int x=leftCell; x<=rightCell; ++x)
        if(GetField(x,y)!=EMPTY_FIELD){
            err<<"AddBlockH("<<y<<", "<<leftCell<<", "<<rightCell<<")\n"
                          <<"Can't add, because block would intersect with another";
            throw std::logic_error(err.str());
        }
    _hBlocks.emplace_back(FirstFreeHorizontal(), y, leftCell, rightCell);
    FillBoard(_hBlocks.back());
    return _hBlocks.back().Id();
}
int PushMe::Board::AddBlockV(int x, int topCell, int bottomCell)
{
    stringstream err;
    if(!InBoundsInner(x, topCell) || !InBoundsInner(x, bottomCell)){
        err<<"AddBlockV("<<x<<", "<<topCell<<", "<<bottomCell<<")\n"
                      <<"Can't add, because block would be out of bounds";
        throw std::logic_error(err.str());
    }
    for(int y=topCell; y<=bottomCell; ++y)
        if(GetField(x,y)!=EMPTY_FIELD){
            err<<"AddBlockV("<<x<<", "<<topCell<<", "<<bottomCell<<")\n"
                          <<"Can't add, because block would intersect with another";
            throw std::logic_error(err.str());
        }
    _vBlocks.emplace_back(FirstFreeVertical(), x, topCell, bottomCell);
    FillBoard(_vBlocks.back());
    return _vBlocks.back().Id();
}
void PushMe::Board::SetBlockF(int x, int y)
{
    stringstream err;
    if(!IsFinalOrEmptyOrFBlock(GetField(x,y))){
        err<<"SetBlockF("<<x<<", "<<y<<")\n"
                      <<"Can't set, because block would intersect with another";
        throw std::logic_error(err.str());
    }
    ClearBoard(_fBlock);
    _fBlock.X(x); _fBlock.Y(y);
    FillBoard(_fBlock);
}
void PushMe::Board::SetFinalField(int x, int y)
{
    stringstream err;
    if(!InBoundsOuter(x,y)){
        err<<"SetFinalField("<<x<<", "<<y<<")\n"
                      <<"Can't set, because field would be out of bounds";
        throw std::logic_error(err.str());
    }
    _fField.x = x; _fField.y = y;
}

std::vector<PushMe::MoveDescription> PushMe::Board::GetAvailableMoves() const
{
    vector<PushMe::MoveDescription> res;
    for(const auto &bh : _hBlocks)//why BlockH &bh does not work
        GetAvailableHMoves(bh.Id(), res);
    for(const auto &bv : _vBlocks)
        GetAvailableVMoves(bv.Id(), res);
    return res;
}
//public questions
int PushMe::Board::MaxRegularLeft(int hBlockId) const
{
    const BlockH& blockH = _hBlocks[hBlockId - lowestHorizontalIndex];
    int dist;
    if(FinalSitsOnHorizontal(blockH))
        dist = min(DistToLeft(blockH.LeftCell(), blockH.Y(), false), MaxFinalLeft()+(blockH.RightCell()-_fBlock.X()+1));
    else
    {
        dist = DistToLeft(blockH.LeftCell(), blockH.Y(), false);
        if(_fBlock.Position() == IntVector(blockH.LeftCell()-dist-1,blockH.Y()))
            dist+=MaxFinalLeft();
    }
    return dist;
}
int PushMe::Board::MaxRegularRight(int hBlockId) const
{
    const BlockH& block = _hBlocks[hBlockId - lowestHorizontalIndex];
    int dist;
    if(FinalSitsOnHorizontal(block))
        dist = min(DistToRight(block.RightCell(), block.Y(), false), MaxFinalRight()+(_fBlock.X()-block.LeftCell()+1));
    else
    {
        dist = DistToRight(block.RightCell(), block.Y(), false);
        if(_fBlock.Position() == IntVector(block.RightCell()+dist+1, block.Y()))
            dist+=MaxFinalRight();
    }
    return dist;
}
int PushMe::Board::MaxRegularUp(int vBlockId) const
{
    const BlockV& block = _vBlocks[vBlockId - lowestVerticalIndex];
    int dist=DistToTop(block.X(), block.TopCell(), false);
    if(_fBlock.Position()==IntVector(block.X(), block.TopCell() - dist - 1))
        dist+=MaxFinalUp();
    return dist;
}
int PushMe::Board::MaxRegularDown(int vBlockId) const
{
    const BlockV& block = _vBlocks[vBlockId - lowestVerticalIndex];
    return DistToBottom(block.X(), block.BottomCell(), false);
}

//moves
void PushMe::Board::Move(const MoveDescription &moveDesc)
{
    switch(moveDesc.Dir())
    {
    case Direction::Left: MoveLeft(moveDesc.BlockId(), moveDesc.Distance()); break;
    case Direction::Right: MoveRight(moveDesc.BlockId(), moveDesc.Distance()); break;
    case Direction::Up: MoveUp(moveDesc.BlockId(), moveDesc.Distance()); break;
    case Direction::Down: MoveDown(moveDesc.BlockId(), moveDesc.Distance()); break;
    }
}
void PushMe::Board::MoveLeft(int hBlockId, int distance)
{
    BlockH& block = _hBlocks[hBlockId - lowestHorizontalIndex];
    _lastMove.emplace(hBlockId, Direction::Left, distance, _fBlock.Position());
    ClearBoard(_fBlock);
    ClearBoard(block);
    if(FinalSitsOnHorizontal(block))
        _fBlock.MoveLeft(min(distance, DistToLeft(_fBlock.X(), _fBlock.Y(), false)));
    int x = block.LeftCell();
    block.MoveLeft(distance);
    if(_fBlock.Y() == block.Y() && _fBlock.X()<=x && _fBlock.X()>=block.LeftCell())
        _fBlock.X(block.LeftCell() - 1);
    FillBoard(block);
    _fBlock.MoveDown(DistToBottom(_fBlock.X(), _fBlock.Y(), true));
    FillBoard(_fBlock);
}
void PushMe::Board::MoveRight(int hBlockId, int distance)
{
    BlockH& block = _hBlocks[hBlockId - lowestHorizontalIndex];
    _lastMove.emplace(hBlockId, Direction::Right, distance, _fBlock.Position());
    ClearBoard(_fBlock);
    ClearBoard(block);
    if(FinalSitsOnHorizontal(block))
        _fBlock.MoveRight(min(distance, DistToRight(_fBlock.X(), _fBlock.Y(), false)));
    int x = block.RightCell();
    block.MoveRight(distance);
    if(_fBlock.Y() == block.Y() && _fBlock.X()>=x && _fBlock.X()<=block.RightCell())
        _fBlock.X(block.RightCell() + 1);
    FillBoard(block);
    _fBlock.MoveDown(DistToBottom(_fBlock.X(), _fBlock.Y(), true));
    FillBoard(_fBlock);
}
void PushMe::Board::MoveUp(int vBlockId, int distance)
{
    BlockV &block = _vBlocks[vBlockId - lowestVerticalIndex];
    _lastMove.emplace(vBlockId, Direction::Up, distance, _fBlock.Position());
    ClearBoard(_fBlock);
    ClearBoard(block);
    int y = block.TopCell();
    block.MoveUp(distance);
    if(_fBlock.X()==block.X() && _fBlock.Y()<=y && _fBlock.Y()>=block.TopCell())
        _fBlock.Y(block.TopCell()-1);
    FillBoard(block);
    FillBoard(_fBlock);
}
void PushMe::Board::MoveDown(int vBlockId, int distance)
{
    BlockV &block = _vBlocks[vBlockId - lowestVerticalIndex];
    _lastMove.emplace(vBlockId, Direction::Down, distance, _fBlock.Position());
    ClearBoard(block);
    block.MoveDown(distance);
    FillBoard(block);
    ClearBoard(_fBlock);
    _fBlock.MoveDown(DistToBottom(_fBlock.X(), _fBlock.Y(), true));
    FillBoard(_fBlock);
}
void PushMe::Board::Undo()
{
    if(_lastMove.size()<=0) return;
    MoveDescriptionInner moveDesc { _lastMove.top()}; _lastMove.pop();
    ClearBoard(_fBlock);
    if(moveDesc.Dir() == Direction::Left)
    {
        BlockH& block =_hBlocks[moveDesc.BlockId() - lowestHorizontalIndex];
        ClearBoard(block);
        block.MoveRight(moveDesc.Distance());
        FillBoard(block);
    }
    else if(moveDesc.Dir() == Direction::Right)
    {
        BlockH& block = _hBlocks[moveDesc.BlockId() - lowestHorizontalIndex];
        ClearBoard(block);
        block.MoveLeft(moveDesc.Distance());
        FillBoard(block);
    }
    else if(moveDesc.Dir() == Direction::Up)
    {
        BlockV& block = _vBlocks[moveDesc.BlockId() - lowestVerticalIndex];
        ClearBoard(block);
        block.MoveDown(moveDesc.Distance());
        FillBoard(block);
    }
    else
    {
        BlockV& block = _vBlocks[moveDesc.BlockId() - lowestVerticalIndex];
        ClearBoard(block);
        block.MoveUp(moveDesc.Distance());
        FillBoard(block);
    }
    _fBlock.Position(moveDesc.LastFBlockPos());
    FillBoard(_fBlock);
}

void PushMe::Board::MoveFBlockDown()
{
    ClearBoard(_fBlock);
    _fBlock.MoveDown(DistToBottom(_fBlock.X(), _fBlock.Y(), true));
    FillBoard(_fBlock);
}

//board helpers
void PushMe::Board::FillBoard(const BlockH& block)
{
    for(int x=block.LeftCell(); x<=block.RightCell(); x++)
        _innerBoard[innerIndex(x, block.Y())] = block.Id();
}
void PushMe::Board::FillBoard(const BlockV& block)
{
    for(int y=block.TopCell(); y<=block.BottomCell(); y++)
        _innerBoard[innerIndex(block.X(), y)] = block.Id();
}
void PushMe::Board::FillBoard(const BlockF& block)
{
    if(!InBoundsInner(block.X(), block.Y())) return;
    _innerBoard[innerIndex(block.X(), block.Y())] = block.Id();
}
void PushMe::Board::ClearBoard(const BlockH& block)
{
    for(int x=block.LeftCell(); x<=block.RightCell(); x++)
        _innerBoard[innerIndex(x, block.Y())] = EMPTY_FIELD;
}
void PushMe::Board::ClearBoard(const BlockV& block)
{
    for(int y=block.TopCell(); y<=block.BottomCell(); y++)
        _innerBoard[innerIndex(block.X(), y)] = EMPTY_FIELD;
}
void PushMe::Board::ClearBoard(const BlockF& block)
{
    if(!InBoundsInner(block.X(), block.Y())) return;
    _innerBoard[innerIndex(block.X(), block.Y())] = EMPTY_FIELD;
}
//questions
int PushMe::Board::DistToLeft(int x, int y, bool allowFinal) const
{
    int dist{0};
    while(FieldOnLeftSide(x--, y) == EMPTY_FIELD) ++dist;
    if(allowFinal && GetField(x, y) == FINAL_FIELD) ++dist;
    return dist;
}
int PushMe::Board::DistToRight(int x, int y, bool allowFinal) const
{
    int dist{0};
    while(FieldOnRightSide(x++, y) == EMPTY_FIELD) ++dist;
    if(allowFinal && GetField(x, y) == FINAL_FIELD) ++dist;
    return dist;
}
int PushMe::Board::DistToTop(int x, int y, bool allowFinal) const
{
    int dist{0};
    while(FieldOnUpSide(x, y--) == EMPTY_FIELD) ++dist;
    if(allowFinal && GetField(x,y) == FINAL_FIELD) ++dist;
    return dist;
}
int PushMe::Board::DistToBottom(int x, int y, bool allowFinal) const
{
    int dist{0};
    while(FieldOnDownSide(x,y++) == EMPTY_FIELD) ++dist;
    if(allowFinal && GetField(x,y) == FINAL_FIELD) ++dist;
    return dist;
}
int PushMe::Board::DistToHoleLeft(int x, int y) const
{
    int dist{0};
    while(!IsFinalOrEmpty(FieldOnDownSide(x--,y)))
    {
        if(GetField(x,y)!=EMPTY_FIELD){dist = std::numeric_limits<int>::max(); break;}//experimental max. original code has error i think
        ++dist;
    }
    return dist;
}
int PushMe::Board::DistToHoleRight(int x, int y) const
{
    int dist{0};
    while(!IsFinalOrEmpty(FieldOnDownSide(x++,y)))
    {
        if(GetField(x,y)!=EMPTY_FIELD){dist = std::numeric_limits<int>::max(); break;}//experimental max. original code has error i think
        ++dist;
    }
    return dist;
}
int PushMe::Board::MaxFinalLeft() const
{
    int toHole{DistToHoleLeft(_fBlock.X(), _fBlock.Y())};
    int toBlock{DistToLeft(_fBlock.X(), _fBlock.Y(), true)};
    return min(toHole, toBlock);
}
int PushMe::Board::MaxFinalRight() const
{
    int toHole = DistToHoleRight(_fBlock.X(), _fBlock.Y());
    int toBlock = DistToRight(_fBlock.X(), _fBlock.Y(), true);
    return min(toHole, toBlock);
}
void PushMe::Board::GetAvailableHMoves(int blockId, std::vector<PushMe::MoveDescription> &container) const
{
    int leftDist = MaxRegularLeft(blockId);
    int rightDist = MaxRegularRight(blockId);
    for(int dist=1; dist<=leftDist; ++dist)
        container.emplace_back(blockId, Direction::Left, dist);
    for(int dist=1; dist<=rightDist; ++dist)
        container.emplace_back(blockId, Direction::Right, dist);
}
void PushMe::Board::GetAvailableVMoves(int blockId, std::vector<PushMe::MoveDescription> &container) const
{
    int topDist = MaxRegularUp(blockId);
    int bottomDist = MaxRegularDown(blockId);
    for(int dist=1; dist<=topDist; ++dist)
        container.emplace_back(blockId, Direction::Up, dist);
    for(int dist=1; dist<=bottomDist; ++dist)
        container.emplace_back(blockId, Direction::Down, dist);
}
