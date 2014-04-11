#ifndef BOARD_H
#define BOARD_H

#include "boardbase.h"
#include "helpers/moveDescription.h"
#include <stack>

namespace PushMe{

class Board : public BoardBase
{
public:
    explicit Board(int innerSizeX = 7, int innerSizeY = 7);
    Board(const Board &other);

    int GetField(int x, int y)const override;

    int AddBlockH(int y, int leftCell, int rightCell) override;
    int AddBlockV(int x, int topCell, int bottomCell) override;
    void SetBlockF(int x, int y) override;
    void SetFinalField(int x, int y) override;

    BlockH GetBlockH(int blockId)const{return _hBlocks[blockId - lowestHorizontalIndex];}
    BlockV GetBlockV(int blockId)const{return _vBlocks[blockId - lowestVerticalIndex];}

    std::vector<MoveDescription> GetAvailableMoves()const;

    //public questions
    int MaxRegularLeft(int hBlockId)const;
    int MaxRegularRight(int hBlockId)const;
    int MaxRegularUp(int vBlockId)const;
    int MaxRegularDown(int vBlockId)const;
    inline bool IsSolved()const{return _fField == _fBlock.Position();}

    //moves
    void Move(const MoveDescription &moveDesc);
    void MoveLeft(int hBlockId, int distance);
    void MoveRight(int hBlockId, int distance);
    void MoveUp(int vBlockId, int distance);
    void MoveDown(int vBlockId, int distance);
    void Undo();

    void MoveFBlockDown();
private:
    std::vector<int> _innerBoard;
    std::stack<MoveDescriptionInner> _lastMove;

    //board helpers
    void FillBoard(const BlockH& block);
    void FillBoard(const BlockV& block);
    void FillBoard(const BlockF& block);
    void ClearBoard(const BlockH& block);
    void ClearBoard(const BlockV& block);
    void ClearBoard(const BlockF& block);
        //inline
    int innerIndex(int x, int y)const{return x + y*_innerSizeX;}

    int FieldOnLeftSide(int x,int y)const{return GetField(--x, y);}
    int FieldOnRightSide(int x,int y)const{return GetField(++x,y);}
    int FieldOnUpSide(int x,int y)const{return GetField(x,--y);}
    int FieldOnDownSide(int x,int y)const{return GetField(x,++y);}
        //
    //questions
    int DistToLeft(int x, int y, bool allowFinal)const;
    int DistToRight(int x, int y, bool allowFinal)const;
    int DistToTop(int x, int y, bool allowFinal)const;
    int DistToBottom(int x, int y, bool allowFinal)const;
    int DistToHoleLeft(int x, int y)const;
    int DistToHoleRight(int x, int y)const;
    inline bool FinalSitsOnHorizontal(const BlockH& block)const{return _fBlock.Y()==block.Y()-1 &&
                _fBlock.X()>=block.LeftCell() && _fBlock.X()<=block.RightCell();}
    int MaxFinalLeft()const;
    int MaxFinalRight()const;
    inline int MaxFinalUp()const{return DistToTop(_fBlock.X(), _fBlock.Y(), true);}
    inline int MaxFinalDown()const{return DistToBottom(_fBlock.X(), _fBlock.Y(), true);}
    inline void GetAvailableHMoves(int blockId, std::vector<MoveDescription> &container)const;
    inline void GetAvailableVMoves(int blockId, std::vector<MoveDescription> &container)const;

};

}
#endif // BOARD_H
