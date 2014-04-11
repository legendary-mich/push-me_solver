#include "solver.h"
#include <algorithm>
using namespace std;

PushMe::Solver::Solver(const Board &board):_depth(1), _board(board)
{
    _visitedNodes.HadNodeBeforeCall(board);
}
void PushMe::Solver::Solve(int maxDepth)
{
    if(_moves.size() > 0) return;

    while(_depth<=maxDepth)
    {
        _moves = _firstStep.Solve(_depth++, _board, _visitedNodes);
        if(_moves.size()>0){
            std::reverse(_moves.begin(), _moves.end());
            break;
        }
    }
}
