#ifndef VISITEDNODE_H
#define VISITEDNODE_H

#include "board/board.h"


namespace PushMe{


class VisitedNode
{
private:
    IntVector _position;
    std::vector<VisitedNode> _children;
    std::vector<IntVector> _extractPositions(const Board &board);
    bool HadNodeBeforeCall(int blockId, const std::vector<IntVector> &blockPositions);
public:
    static int expectedChildrenCount;//innerBoard width - 1, positions in which block can be found
    explicit VisitedNode();
    explicit VisitedNode(const IntVector &blockPos);

    inline bool HadNodeBeforeCall(const Board& board){return HadNodeBeforeCall(-1, _extractPositions(board));}

    IntVector Position()const{return _position;}
    const std::vector<VisitedNode> &Children()const{return _children;}
};

}
#endif // VISITEDNODE_H
