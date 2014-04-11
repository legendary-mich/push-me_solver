#include "step.h"
#include <iostream>
using namespace std;

std::vector<PushMe::MoveDescription> PushMe::Step::Solve(int depth, PushMe::Board &board, VisitedNode &visitedNodes)
{
    if(!_isRootNode)
        board.Move(_moveDesc);
    --depth;
    if(depth<=0)
    {
        const vector<MoveDescription> &moves = board.GetAvailableMoves();
        for(const auto& md : moves)
        {
            board.Move(md);
            if(board.IsSolved())
            {
                vector<MoveDescription> ret{md};
                if(!_isRootNode) ret.emplace_back(_moveDesc);
                board.Undo();
                return ret;
            }
            if(!visitedNodes.HadNodeBeforeCall(board))
                _children.emplace_back(md);
            board.Undo();
        }
    }
    else
    {
        vector<MoveDescription> ret;
        for(auto& step : _children)
        {
            ret = step.Solve(depth, board, visitedNodes);
            if(ret.size()>0)
            {
                if(!_isRootNode)
                    ret.emplace_back(_moveDesc);
                board.Undo();
                return ret;
            }
        }
    }
    board.Undo();//if root, than does nothing
    return vector<MoveDescription>();
}

