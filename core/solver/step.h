#ifndef STEP_H
#define STEP_H

#include "board/board.h"
#include "visitednode.h"

namespace PushMe{

class Step
{
private:    
    const MoveDescription _moveDesc;
    const bool _isRootNode;
    std::vector<Step> _children;

public:
    Step():_moveDesc{MoveDescription(-1, Direction::Down, -1)}, _isRootNode{true}{}
    explicit Step(const MoveDescription &moveDesc):_moveDesc{moveDesc}, _isRootNode{false}{}
    std::vector<MoveDescription> Solve(int depth, Board& board, VisitedNode& visitedNodes);

    const MoveDescription &MoveDesc()const{return _moveDesc;}
    const std::vector<Step> &Children()const{return _children;}
};

}
#endif // STEP_H
