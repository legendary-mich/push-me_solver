#ifndef BOARDBASE_H
#define BOARDBASE_H
#include <string>
#include <vector>
#include <stdexcept>
#include "blocks.h"

namespace PushMe{
class BoardBase
{
public:
    enum{ NOT_A_FIELD =-3, FINAL_FIELD =- 2, FINAL_BLOCK =-1, EMPTY_FIELD=0};
private:
    int _firstFreeHorizontal{lowestHorizontalIndex}, _firstFreeVertical{lowestVerticalIndex};
protected:
    static constexpr int lowestVerticalIndex = 1;
    static constexpr int lowestHorizontalIndex = 10000;
    int FirstFreeHorizontal(){return _firstFreeHorizontal++;}
    int FirstFreeVertical(){return _firstFreeVertical++;}
public:
    static constexpr bool IsHorizontal(int index){return index>=lowestHorizontalIndex;}
    static constexpr bool IsVertical(int index){return index>=lowestVerticalIndex && !IsHorizontal(index);}
    static constexpr bool IsFinalOrEmpty(int i){return i==FINAL_FIELD || i==EMPTY_FIELD;}
    static constexpr bool IsFinalOrEmptyOrFBlock(int i){return IsFinalOrEmpty(i) || i == FINAL_BLOCK;}
    explicit BoardBase(int innerSizeX, int innerSizeY)
        :_innerSizeX{innerSizeX}, _innerSizeY{innerSizeY}, _fField{-1}, _fBlock{FINAL_BLOCK, IntVector{0}}
    {
        if(_innerSizeX < 3 || _innerSizeY <3)
            throw std::logic_error("innerSize of the board must be at least 3");
    }

    int InnerSizeX() const {return _innerSizeX;}
    int InnerSizeY() const {return _innerSizeY;}
    IntVector GetFinalField() const {return _fField;}
    BlockF GetBlockF() const {return _fBlock;}
    const std::vector<BlockH> &GetHorizontalBlocks() const {return _hBlocks;}
    const std::vector<BlockV> &GetVerticalBlocks() const {return _vBlocks;}
    std::string Name() const {return _name;}

    bool InBoundsInner(int x, int y)const{return x>=0 && x<_innerSizeX && y>=0 && y<_innerSizeY;}
    bool InBoundsOuter(int x, int y)const{
        return x>=-1 && x<=_innerSizeX && y>=-1 && y<= _innerSizeY && !InBoundsInner(x,y);
    }

    void SetName(std::string name){_name = std::move(name);}
    virtual int GetField(int x, int y)const = 0;
    virtual int AddBlockH(int y, int leftCell, int rightCell) = 0;
    virtual int AddBlockV(int x, int topCell, int bottomCell) = 0;
    virtual void SetBlockF(int x, int y) = 0;
    virtual void SetFinalField(int x, int y) = 0;

    virtual ~BoardBase(){}
protected:
    int _innerSizeX, _innerSizeY;
    IntVector _fField;
    BlockF _fBlock;
    std::vector<BlockH> _hBlocks;
    std::vector<BlockV> _vBlocks;
    std::string _name;
};

bool operator==(const BoardBase &b1, const BoardBase &b2);
inline bool operator!=(const BoardBase &b1, const BoardBase &b2){return !(b1==b2);}
}
#endif // BOARDBASE_H
