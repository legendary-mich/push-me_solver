#ifndef BLOCKS_H
#define BLOCKS_H

#include "helpers/intVector.h"

namespace PushMe{

class BlockH{
private:
    int _id, _y, _leftCell, _rightCell;
public:
    explicit BlockH(int id, int y, int leftCell, int rightCell)
        :_id{id}, _y{y}, _leftCell{leftCell}, _rightCell{rightCell}{}

    int Id()const{return _id;}
    int Y()const{return _y;}
    int LeftCell()const{return _leftCell;}
    int RightCell()const{return _rightCell;}
    int Width()const{return _rightCell - _leftCell + 1;}

    void MoveLeft(int distance){_leftCell-=distance; _rightCell-=distance;}
    void MoveRight(int distance){_leftCell+=distance; _rightCell+=distance;}
};

class BlockV{
private:
    int _id, _x, _topCell, _bottomCell;
public:
    explicit BlockV(int id, int x, int topCell, int bottomCell)
        :_id{id}, _x{x}, _topCell{topCell}, _bottomCell{bottomCell}{}

    int Id()const{return _id;}
    int X()const{return _x;}
    int TopCell()const{return _topCell;}
    int BottomCell()const{return _bottomCell;}
    int Height()const{return _bottomCell - _topCell + 1;}

    void MoveUp(int distance){_topCell-=distance; _bottomCell-=distance;}
    void MoveDown(int distance){_topCell+=distance; _bottomCell+=distance;}
};

class BlockF{
private:
    int _id, _x, _y;
public:
    explicit BlockF(int id, int x, int y):_id{id}, _x{x}, _y{y}{}
    explicit BlockF(int id, const IntVector& pos):BlockF(id, pos.x, pos.y){}
    int Id()const{return _id;}
    int X()const{return _x;}
    int Y()const{return _y;}
    IntVector Position()const{return IntVector(_x, _y);}

    void X(int val){_x = val;}
    void Y(int val){_y = val;}
    void Position(IntVector val){_x = val.x; _y = val.y;}
    void MoveLeft(int dist){_x-=dist;}
    void MoveRight(int dist){_x+=dist;}
    void MoveUp(int dist){_y-=dist;}
    void MoveDown(int dist){_y+=dist;}
};

inline bool Intersects(const BlockH &bh1, const BlockH &bh2){ return bh1.Y() == bh2.Y() &&
            bh1.LeftCell() <= bh2.RightCell() && bh1.RightCell() >= bh2.LeftCell();}
inline bool Intersects(const BlockV &bv1, const BlockV &bv2){return bv1.X() == bv2.X() &&
            bv1.TopCell() <= bv2.BottomCell() && bv1.BottomCell() >= bv2.TopCell();}

inline bool Intersects(const BlockH &bh, const BlockF &bf){return bh.Y() == bf.Y() &&
            bh.LeftCell() <= bf.X() && bh.RightCell() >= bf.X();}
inline bool Intersects(const BlockF &bf, const BlockH &bh){return Intersects(bh, bf);}

inline bool Intersects(const BlockV &bv, const BlockF &bf){return bv.X() == bf.X() &&
            bv.TopCell() <= bf.Y() && bv.BottomCell() >= bf.Y();}
inline bool Intersects(const BlockF &bf, const BlockV &bv){return Intersects(bv, bf);}

inline bool Intersects(const BlockH &bh, const BlockV &bv){
    return bh.Y() >= bv.TopCell() && bh.Y() <= bv.BottomCell() &&
            bv.X() >= bh.LeftCell() && bv.X() <= bh.RightCell();
}
inline bool Intersects(const BlockV &bv, const BlockH &bh){return Intersects(bh, bv);}
}

#endif // BLOCKS_H
