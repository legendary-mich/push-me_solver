#ifndef SOLVER_H
#define SOLVER_H
#include "step.h"

namespace PushMe{

class Solver
{
private:
    int _depth;
    Board _board;
    Step _firstStep;
    VisitedNode _visitedNodes;
    std::vector<MoveDescription> _moves;

public:
    explicit Solver(const Board& board);
    void Solve(int maxDepth);
    const std::vector<MoveDescription> GetMoves()const{return _moves;}
};

}
#endif // SOLVER_H
