#include "solvertest.h"
#include "Solver/visitednode.h"
#include "Solver/step.h"

using namespace PushMe;
SolverTest::SolverTest()
{

}
void SolverTest::vNodeAddFinal()
{
    VisitedNode root;
    Board board;
    board.SetBlockF(3,4);
    QVERIFY2(!root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(3,4));
}
void SolverTest::vNodeAddFinalTwoTimes()
{
    VisitedNode root;
    Board board;
    board.SetBlockF(3,4);
    root.HadNodeBeforeCall(board);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(3,4));
}

void SolverTest::vNodeAddH()
{
    VisitedNode root;
    Board board;
    board.AddBlockH(0,2,4);
    board.SetBlockF(3,4);
    QVERIFY2(!root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(2,0));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(3,4));
}
void SolverTest::vNodeAddHTwoTimes()
{
    VisitedNode root;
    Board board;
    board.AddBlockH(0,2,4);
    board.SetBlockF(3,4);
    root.HadNodeBeforeCall(board);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(2,0));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(3,4));
}
void SolverTest::vNodeAddV()
{
    VisitedNode root;
    Board board;
    board.AddBlockV(0,2,4);
    board.SetBlockF(3,4);
    QVERIFY2(!root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(0,2));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(3,4));
}
void SolverTest::vNodeAddVTwoTimes()
{
    VisitedNode root;
    Board board;
    board.AddBlockV(0,2,4);
    board.SetBlockF(3,4);
    root.HadNodeBeforeCall(board);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(0,2));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(3,4));
}

void SolverTest::vNodeAddFinalTwoPos()
{
    VisitedNode root;
    Board board;
    board.SetBlockF(2,3);
    root.HadNodeBeforeCall(board);
    board.SetBlockF(4,5);
    QVERIFY2(!root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 2);
    QCOMPARE((int)root.Children()[0].Children().size(), 0);
    QCOMPARE((int)root.Children()[1].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(2,3));
    QCOMPARE(root.Children()[1].Position(), IntVector(4,5));
}
void SolverTest::vNodeAddFinalTwoPosTwoTimes()
{
    VisitedNode root;
    Board board;
    board.SetBlockF(2,3);
    root.HadNodeBeforeCall(board);
    board.SetBlockF(4,5);
    root.HadNodeBeforeCall(board);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    board.SetBlockF(2,3);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 2);
    QCOMPARE((int)root.Children()[0].Children().size(), 0);
    QCOMPARE((int)root.Children()[1].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(2,3));
    QCOMPARE(root.Children()[1].Position(), IntVector(4,5));
}
void SolverTest::vNodeAddHTwoPos()
{
    VisitedNode root;
    Board board;
    int blockId = board.AddBlockH(0,1,2);
    board.SetBlockF(4,6);
    root.HadNodeBeforeCall(board);
    board.MoveRight(blockId, 1);
    QVERIFY2(!root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 2);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[1].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE((int)root.Children()[1].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(1,0));
    QCOMPARE(root.Children()[1].Position(), IntVector(2,0));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(4,6));
    QCOMPARE(root.Children()[1].Children()[0].Position(), IntVector(4,6));
}
void SolverTest::vNodeAddHTwoPosTwoTimes()
{
    VisitedNode root;
    Board board;
    int blockId = board.AddBlockH(0,1,2);
    board.SetBlockF(4,6);
    root.HadNodeBeforeCall(board);
    board.MoveRight(blockId, 1);
    root.HadNodeBeforeCall(board);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    board.MoveLeft(blockId, 1);
    QVERIFY2(root.HadNodeBeforeCall(board), "1");
    QCOMPARE((int)root.Children().size(), 2);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[1].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE((int)root.Children()[1].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(1,0));
    QCOMPARE(root.Children()[1].Position(), IntVector(2,0));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(4,6));
    QCOMPARE(root.Children()[1].Children()[0].Position(), IntVector(4,6));
}
void SolverTest::vNodeAddVTwoPos()
{
    VisitedNode root;
    Board board;
    int blockId = board.AddBlockV(0,1,2);
    board.SetBlockF(4,6);
    root.HadNodeBeforeCall(board);
    board.MoveDown(blockId, 1);
    QVERIFY2(!root.HadNodeBeforeCall(board), "0");
    QCOMPARE((int)root.Children().size(), 2);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[1].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE((int)root.Children()[1].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(0,1));
    QCOMPARE(root.Children()[1].Position(), IntVector(0,2));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(4,6));
    QCOMPARE(root.Children()[1].Children()[0].Position(), IntVector(4,6));
}
void SolverTest::vNodeAddVTwoPosTwoTimes()
{
    VisitedNode root;
    Board board;
    int blockId = board.AddBlockV(0,1,2);
    board.SetBlockF(4,6);
    root.HadNodeBeforeCall(board);
    board.MoveDown(blockId, 1);
    root.HadNodeBeforeCall(board);
    QVERIFY2(root.HadNodeBeforeCall(board), "0");
    board.MoveUp(blockId, 1);
    QVERIFY2(root.HadNodeBeforeCall(board), "1");
    QCOMPARE((int)root.Children().size(), 2);
    QCOMPARE((int)root.Children()[0].Children().size(), 1);
    QCOMPARE((int)root.Children()[1].Children().size(), 1);
    QCOMPARE((int)root.Children()[0].Children()[0].Children().size(), 0);
    QCOMPARE((int)root.Children()[1].Children()[0].Children().size(), 0);
    QCOMPARE(root.Children()[0].Position(), IntVector(0,1));
    QCOMPARE(root.Children()[1].Position(), IntVector(0,2));
    QCOMPARE(root.Children()[0].Children()[0].Position(), IntVector(4,6));
    QCOMPARE(root.Children()[1].Children()[0].Position(), IntVector(4,6));
}

void SolverTest::StepLeft()
{
    Board board;
    int blockId = board.AddBlockH(0,2,6);
    VisitedNode visitedNodes;
    Step step;
    auto res = step.Solve(1, board, visitedNodes);
    QCOMPARE((int)res.size(), 0);
    QCOMPARE((int)visitedNodes.Children().size(), 2);
    QCOMPARE((int)step.Children().size(), 2);
    QCOMPARE(step.Children()[0].MoveDesc(), MoveDescription(blockId, Direction::Left, 1));
    QCOMPARE(step.Children()[1].MoveDesc(), MoveDescription(blockId, Direction::Left, 2));
}
void SolverTest::StepRight()
{
    Board board;
    int blockId = board.AddBlockH(0,0,4);
    VisitedNode visitedNodes;
    Step step;
    auto res = step.Solve(1, board, visitedNodes);
    QCOMPARE((int)res.size(), 0);
    QCOMPARE((int)visitedNodes.Children().size(), 2);
    QCOMPARE((int)step.Children().size(), 2);
    QCOMPARE(step.Children()[0].MoveDesc(), MoveDescription(blockId, Direction::Right, 1));
    QCOMPARE(step.Children()[1].MoveDesc(), MoveDescription(blockId, Direction::Right, 2));
}
void SolverTest::StepUp()
{
    Board board;
    int blockId = board.AddBlockV(0,2,6);
    VisitedNode visitedNodes;
    Step step;
    auto res = step.Solve(1, board, visitedNodes);
    QCOMPARE((int)res.size(), 0);
    QCOMPARE((int)visitedNodes.Children().size(), 2);
    QCOMPARE((int)step.Children().size(), 2);
    QCOMPARE(step.Children()[0].MoveDesc(), MoveDescription(blockId, Direction::Up, 1));
    QCOMPARE(step.Children()[1].MoveDesc(), MoveDescription(blockId, Direction::Up, 2));
}
void SolverTest::StepDown()
{
    Board board;
    int blockId = board.AddBlockV(0,0,4);
    VisitedNode visitedNodes;
    Step step;
    auto res = step.Solve(1, board, visitedNodes);
    QCOMPARE((int)res.size(), 0);
    QCOMPARE((int)visitedNodes.Children().size(), 2);
    QCOMPARE((int)step.Children().size(), 2);
    QCOMPARE(step.Children()[0].MoveDesc(), MoveDescription(blockId, Direction::Down, 1));
    QCOMPARE(step.Children()[1].MoveDesc(), MoveDescription(blockId, Direction::Down, 2));
}

