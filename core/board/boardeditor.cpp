#include "boardeditor.h"
#include <stdexcept>

int PushMe::BoardEditor::GetField(int x, int y) const
{
    (void)x; (void)y;
    throw std::runtime_error("method is not implemented");
}

int PushMe::BoardEditor::AddBlockH(int y, int leftCell, int rightCell)
{
    if(!InBoundsInner(leftCell, y)) return NOT_A_FIELD;
    if(!InBoundsInner(rightCell, y)) return NOT_A_FIELD;
    BlockH newBlock(FirstFreeHorizontal(), y, leftCell, rightCell);
    if(Intersects(newBlock, _fBlock)) return NOT_A_FIELD;
    EraseHorizontals([&](const BlockH &bh){return Intersects(newBlock, bh);});
    EraseVerticals([&](const BlockV &bv){return Intersects(newBlock, bv);});
    if(rightCell - leftCell < 1) return NOT_A_FIELD;
    _hBlocks.push_back(newBlock);
    return newBlock.Id();
}
int PushMe::BoardEditor::AddBlockV(int x, int topCell, int bottomCell)
{
    if(!InBoundsInner(x, topCell)) return NOT_A_FIELD;
    if(!InBoundsInner(x, bottomCell)) return NOT_A_FIELD;
    BlockV newBlock(FirstFreeVertical(), x, topCell, bottomCell);
    if(Intersects(newBlock, _fBlock)) return NOT_A_FIELD;
    EraseHorizontals([&](const BlockH &bh){return Intersects(newBlock, bh);});
    EraseVerticals([&](const BlockV &bv){return Intersects(newBlock, bv);});
    if(bottomCell - topCell < 1) return NOT_A_FIELD;
    _vBlocks.push_back(newBlock);
    return newBlock.Id();
}
void PushMe::BoardEditor::SetBlockF(int x, int y)
{
    if(!InBoundsInner(x, y)) return;
    _fBlock.Position(IntVector{x,y});
    EraseHorizontals([&](const BlockH &bh){return Intersects(_fBlock, bh);});
    EraseVerticals([&](const BlockV &bv){return Intersects(_fBlock, bv);});
}
void PushMe::BoardEditor::SetFinalField(int x, int y)
{
    if(!InBoundsOuter(x, y)) return;
    _fField = IntVector{x, y};
}
void PushMe::BoardEditor::EraseHorizontals(std::function<bool(const BlockH &)> func)
{
    for(auto it=_hBlocks.begin(); it!=_hBlocks.end();){
        if(func(*it))
            it=_hBlocks.erase(it);
        else ++it;
    }
}
void PushMe::BoardEditor::EraseVerticals(std::function<bool(const BlockV &)> func)
{
    for(auto it=_vBlocks.begin(); it!=_vBlocks.end();){
        if(func(*it))
            it=_vBlocks.erase(it);
        else ++it;
    }
}
