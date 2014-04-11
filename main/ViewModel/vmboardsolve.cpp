#include "vmboardsolve.h"
#include "helpers/services.h"
#include <iostream>

using namespace std;
using namespace PushMe;

VMBoardSolve::VMBoardSolve(QObject *parent) :
    VMBoardBase(parent)
{
}

void VMBoardSolve::SetBoardClone(const BoardBase *board)
{
    if(board == nullptr)return;
    Board *b = CreateFromBase(*board);
    SetBoard(b);
    _solver = unique_ptr<Solver>(new Solver(*b));
    _moves.clear();
    _currentMove = 0;
    EmitAllButtons();
}


void VMBoardSolve::loadBoard(QString fullPath)
{
    Q_UNUSED(fullPath);
}

void VMBoardSolve::solve()
{
    if(_board.get() == nullptr) return;
    if(_moves.size()>0) return;
    _solver->Solve(_depth);
    _moves = _solver->GetMoves();
    EmitAllButtons();
}

void VMBoardSolve::undo()
{
    if(_board.get() == nullptr) return;
    if(_currentMove<=0)return;
    Board &board = static_cast<Board&>(*_board.get());
    board.Undo();
    --_currentMove;
    UpdateBlocks();
    emit finalBlockChanged();
    EmitAllButtons();
}

void VMBoardSolve::forward()
{
    if(_board.get() == nullptr)return;
    if(_currentMove>=(int)_moves.size()) return;
    Board &board = static_cast<Board&>(*_board.get());
    board.Move(_moves[_currentMove++]);
    UpdateBlocks();
    emit finalBlockChanged();
    EmitAllButtons();
}
