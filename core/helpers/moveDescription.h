#ifndef MOVEDESCRIPTION_H
#define MOVEDESCRIPTION_H
#include "intVector.h"

namespace PushMe{

enum class Direction{ Left, Right, Up, Down};

class MoveDescription{
public:
    MoveDescription(int blockId, Direction dir, int distance)
        :_blockId{blockId}, _direction{dir}, _distance{distance}{}
    int BlockId()const{return _blockId;}
    Direction Dir()const{return _direction;}
    int Distance()const{return _distance;}
private:
    int _blockId;
    Direction _direction;
    int _distance;
};

class MoveDescriptionInner : public MoveDescription{
public:
    MoveDescriptionInner(int blockId, Direction dir, int distance, IntVector lastFBlockPos)
        :MoveDescription{blockId, dir, distance}, _lastFBlockPos{lastFBlockPos}{}
    IntVector LastFBlockPos()const{return _lastFBlockPos;}
private:
    IntVector _lastFBlockPos;
};

inline bool operator==(const MoveDescription& md1, const MoveDescription &md2){
    return md1.BlockId() == md2.BlockId() && md1.Dir() == md2.Dir() && md1.Distance() == md2.Distance();
}
}//namespace PushMe
#endif // MOVEDESCRIPTION_H
