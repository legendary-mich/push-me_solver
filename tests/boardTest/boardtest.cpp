#include "boardtest.h"
#include "board/board.h"
#include "helpers.h"
using namespace PushMe;
using std::vector;
BoardTests::BoardTests()
{
}

void BoardTests::addBlockV()
{
    Board board;
    int blockId = board.AddBlockV(2,3,5);
    QVERIFY2(AreColumnsEmpty(board,0,1), "0");
    QVERIFY2(AreColumnsEmpty(board,3,6), "1");
    QVERIFY2(AreRowsEmpty(board,0,2), "2");
    QVERIFY2(AreRowsEmpty(board, 6, 6), "3");
    for(int y=3; y<=5; ++y)
        QVERIFY2(board.GetField(2, y)==blockId, "4");
}
void BoardTests::addBlockH()
{
    Board board;
    int blockId = board.AddBlockH(2,3,5);
    QVERIFY2(AreRowsEmpty(board,0,1), "0");
    QVERIFY2(AreRowsEmpty(board,3,6), "1");
    QVERIFY2(AreColumnsEmpty(board,0,2), "2");
    QVERIFY2(AreColumnsEmpty(board, 6, 6), "3");
    for(int x=3; x<=5; ++x)
        QVERIFY2(board.GetField(x, 2)==blockId, "4");
}
void BoardTests::setBlockF()
{
    Board board;
    board.SetBlockF(3,4);
    QVERIFY2(board.GetField(3,4)==Board::FINAL_BLOCK, "0");
    board.SetBlockF(4,4);
    QVERIFY2(board.GetField(3,4)==Board::EMPTY_FIELD, "1");
}
void BoardTests::setFField()
{
    Board board;
    board.SetFinalField(5,-1);
    QCOMPARE(board.GetField(5,-1), static_cast<int>(Board::FINAL_FIELD));
}

void BoardTests::Copy()
{
    Board board;
    board.AddBlockV(1,2,3);
    board.AddBlockH(1,2,3);
    board.SetBlockF(4,4);
    board.SetFinalField(7,7);
    Board clone(board);
    QCOMPARE(board.GetFinalField(), clone.GetFinalField());
    QCOMPARE(board.GetBlockF().Position(), clone.GetBlockF().Position());
    QCOMPARE(board.InnerSizeX(), clone.InnerSizeX());
    QCOMPARE(board.InnerSizeY(), clone.InnerSizeY());
    for(int x=0; x<board.InnerSizeX(); ++x)
        for(int y=0; y<board.InnerSizeY(); ++y)
            QCOMPARE(board.GetField(x,y), clone.GetField(x,y));
}
void BoardTests::Equal()
{
    Board board;
    Board clone(board);
    QVERIFY2(board == clone, "0");
    QVERIFY2(!(board != clone), "1");
    board.SetFinalField(7,7);
    board.SetBlockF(1,1);
    board.AddBlockH(2,3,4);
    board.AddBlockV(2,3,4);
    Board clone2(board);
    QVERIFY2(board == clone2, "2");
    QVERIFY2(!(board != clone2), "3");
}
void BoardTests::NotEqualSX()
{
    Board board(4,4);
    Board other(5,4);
    QVERIFY(board != other);
}

void BoardTests::NotEqualSY()
{
    Board board(4,4);
    Board other(4,5);
    QVERIFY(board != other);
}
void BoardTests::NotEqualFB()
{
    Board board;
    board.SetBlockF(1,1);
    Board other(board);
    other.SetBlockF(2,2);
    QVERIFY(board != other);
}
void BoardTests::NotEqualFF()
{
    Board board;
    board.SetFinalField(-1,0);
    Board other(board);
    other.SetFinalField(-1,2);
    QVERIFY(board != other);
}
void BoardTests::NotEqualGetField()
{
    Board board;
    Board other(board);
    other.AddBlockH(1,1,2);
    QVERIFY(board != other);
}
//max down
void BoardTests::maxDownWallBlocks()
{
    Board board;
    int blockId = board.AddBlockV(0,0,4);
    QCOMPARE(board.MaxRegularDown(blockId), 2);
}

void BoardTests::maxDownFinal()
{
    Board board;
    int blockId=board.AddBlockV(0,0,4);
    board.SetFinalField(0,7);
    QCOMPARE(board.MaxRegularDown(blockId), 2);
}
void BoardTests::maxDownHBlocks()
{
    Board board;
    int blockId = board.AddBlockV(1, 0, 2);
    board.AddBlockH(4,0,5);
    QCOMPARE(board.MaxRegularDown(blockId), 1);
}
void BoardTests::maxDownVBlocks()
{
    Board board;
    int blockId = board.AddBlockV(2,0,2);
    board.AddBlockV(2,5,6);
    QCOMPARE(board.MaxRegularDown(blockId), 2);
}
void BoardTests::maxDownFBlocks()
{
    Board board;
    int blockId = board.AddBlockV(3, 1,2);
    board.SetBlockF(3,6);
    QCOMPARE(board.MaxRegularDown(blockId), 3);
}
//max up
void BoardTests::maxUpWall()
{
    Board board;
    int blockId = board.AddBlockV(3,4,5);
    QCOMPARE(board.MaxRegularUp(blockId),4);
}
void BoardTests::maxUpFinal()
{
    Board board;
    int blockId = board.AddBlockV(3,4,5);
    board.SetFinalField(3,-1);
    QCOMPARE(board.MaxRegularUp(blockId),4);
}
void BoardTests::maxUpH()
{
    Board board;
    int blockId = board.AddBlockV(2,4,5);
    board.AddBlockH(0,2,4);
    QCOMPARE(board.MaxRegularUp(blockId), 3);
}
void BoardTests::maxUpV()
{
    Board board;
    int blockId = board.AddBlockV(2,5,6);
    board.AddBlockV(2,0,1);
    QCOMPARE(board.MaxRegularUp(blockId), 3);
}
void BoardTests::maxUpFWall()
{
    Board board;
    int blockId = board.AddBlockV(2,5,6);
    board.SetBlockF(2,4);
    QCOMPARE(board.MaxRegularUp(blockId), 4);
}
void BoardTests::maxUpFFinal()
{
    Board board;
    int blockId = board.AddBlockV(2,5,6);
    board.SetBlockF(2,4);
    board.SetFinalField(2,-1);
    QCOMPARE(board.MaxRegularUp(blockId), 5);
}
void BoardTests::maxUpFH()
{
    Board board;
    int blockId=board.AddBlockV(4,5,6);
    board.SetBlockF(4,4);
    board.AddBlockH(0,4,5);
    QCOMPARE(board.MaxRegularUp(blockId),3);
}
void BoardTests::maxUpFV()
{
    Board board;
    int blockId=board.AddBlockV(4,5,6);
    board.SetBlockF(4,4);
    board.AddBlockV(4,0,1);
    QCOMPARE(board.MaxRegularUp(blockId),2);
}
//max left
void BoardTests::maxLeftWall()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    QCOMPARE(board.MaxRegularLeft(blockId),4);
}
void BoardTests::maxLeftFinal()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.SetFinalField(-1,6);
    QCOMPARE(board.MaxRegularLeft(blockId),4);
}
void BoardTests::maxLeftH()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.AddBlockH(6,1,2);
    QCOMPARE(board.MaxRegularLeft(blockId),1);
}
void BoardTests::maxLeftV()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.AddBlockV(1,1,6);
    QCOMPARE(board.MaxRegularLeft(blockId),2);
}
void BoardTests::maxLeftFWall()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.SetBlockF(3,6);
    QCOMPARE(board.MaxRegularLeft(blockId), 3);
}
void BoardTests::maxLeftFFinal()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.SetBlockF(3,6);
    board.SetFinalField(-1,6);
    QCOMPARE(board.MaxRegularLeft(blockId), 4);
}
void BoardTests::maxLeftFH()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.SetBlockF(3,6);
    board.AddBlockH(6,0,1);
    QCOMPARE(board.MaxRegularLeft(blockId), 1);
}
void BoardTests::maxLeftFV()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.SetBlockF(3,6);
    board.AddBlockV(0,5,6);
    QCOMPARE(board.MaxRegularLeft(blockId), 2);
}
void BoardTests::maxLeftFHole()
{
    Board board;
    int blockId = board.AddBlockH(5,5,6);
    board.AddBlockH(6,3,6);
    board.SetBlockF(4,5);
    QCOMPARE(board.MaxRegularLeft(blockId), 2);
}
void BoardTests::maxLeftFOnH()
{
    Board board;
    int blockId = board.AddBlockH(6,4,6);
    board.SetBlockF(5,5);
    board.AddBlockH(5,2,3);
    QCOMPARE(board.MaxRegularLeft(blockId),3);
}
//max right
void BoardTests::maxRightWall()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    QCOMPARE(board.MaxRegularRight(blockId), 4);
}
void BoardTests::maxRightFinal()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.SetFinalField(7,6);
    QCOMPARE(board.MaxRegularRight(blockId), 4);
}
void BoardTests::maxRightH()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.AddBlockH(6,5,6);
    QCOMPARE(board.MaxRegularRight(blockId), 2);
}
void BoardTests::maxRightV()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.AddBlockV(6, 0, 6);
    QCOMPARE(board.MaxRegularRight(blockId), 3);
}
void BoardTests::maxRightFWall()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.SetBlockF(4,6);
    QCOMPARE(board.MaxRegularRight(blockId), 3);
}
void BoardTests::maxRightFFinal()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.SetBlockF(4,6);
    board.SetFinalField(7,6);
    QCOMPARE(board.MaxRegularRight(blockId), 4);
}
void BoardTests::maxRightFH()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.SetBlockF(4,6);
    board.AddBlockH(6, 5,6);
    QCOMPARE(board.MaxRegularRight(blockId), 1);
}
void BoardTests::maxRightFV()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.SetBlockF(4,6);
    board.AddBlockV(6, 5,6);
    QCOMPARE(board.MaxRegularRight(blockId), 2);
}
void BoardTests::maxRightFHole()
{
    Board board;
    board.AddBlockH(6,0,4);
    int blockId = board.AddBlockH(5,0,1);
    board.SetBlockF(3,5);
    QCOMPARE(board.MaxRegularRight(blockId), 3);
}
void BoardTests::maxRightFOnH()
{
    Board board;
    int blockId = board.AddBlockH(6,0,2);
    board.SetBlockF(1,5);
    board.AddBlockH(5,3,4);
    QCOMPARE(board.MaxRegularRight(blockId), 3);
}
//move up
void BoardTests::moveUp()
{
    Board board;
    int blockId = board.AddBlockV(3,4,5);
    board.SetBlockF(3,3);
    board.MoveUp(blockId, 3);
    QCOMPARE(board.GetField(3,0), static_cast<int>(Board::FINAL_BLOCK));
    QCOMPARE(board.GetField(3,1), blockId);
    QCOMPARE(board.GetField(3,2), blockId);
    QVERIFY2(AreRowsEmpty(board,3,6), "0");
}
void BoardTests::moveUpFField()
{
    Board board;
    int blockId = board.AddBlockV(3,4,5);
    board.SetBlockF(3,3);
    board.SetFinalField(3,-1);
    board.MoveUp(blockId, 4);
    QCOMPARE(board.GetField(3,-1), static_cast<int>(Board::FINAL_BLOCK));
}
//move down
void BoardTests::moveDown()
{
    Board board;
    board.SetBlockF(3,0);
    int blockId = board.AddBlockV(3,1,2);
    board.MoveDown(blockId,4);
    QCOMPARE(board.GetField(3,4), static_cast<int>(Board::FINAL_BLOCK));
    QCOMPARE(board.GetField(3,5), blockId);
    QCOMPARE(board.GetField(3,6), blockId);
    QVERIFY2(AreRowsEmpty(board,0,3), "0");
}
//move left
void BoardTests::moveLeft()
{
    Board board;
    board.SetBlockF(3,6);
    int blockId = board.AddBlockH(6,5,6);
    board.MoveLeft(blockId, 3);
    QCOMPARE(board.GetField(1,6), static_cast<int>(Board::FINAL_BLOCK));
    QCOMPARE(board.GetField(2,6), blockId);
    QCOMPARE(board.GetField(3,6), blockId);
    QVERIFY2(AreColumnsEmpty(board,0,0), "0");
    QVERIFY2(AreColumnsEmpty(board,4,6), "1");
}
void BoardTests::moveLeftFField()
{
    Board board;
    board.SetBlockF(0,6);
    int blockId = board.AddBlockH(6,1,3);
    //TODO set fField if sth changed
    board.MoveLeft(blockId, 1);
    QCOMPARE(board.GetField(-1,6), static_cast<int>(Board::FINAL_BLOCK));
}
//moveRight
void BoardTests::moveRight()
{
    Board board;
    board.SetBlockF(3,6);
    int blockId = board.AddBlockH(6,0,1);
    board.MoveRight(blockId, 4);
    QCOMPARE(board.GetField(6,6), static_cast<int>(Board::FINAL_BLOCK));
    QCOMPARE(board.GetField(4,6), blockId);
    QCOMPARE(board.GetField(5,6), blockId);
    QVERIFY2(AreColumnsEmpty(board, 0, 3),"0");
}
void BoardTests::moveRightFField()
{
    Board board;
    board.SetBlockF(5,6);
    int blockId = board.AddBlockH(6,3,4);
    //TODO set fField if sth changed
    board.MoveRight(blockId, 2);
    QCOMPARE(board.GetField(7,6), static_cast<int>(Board::FINAL_BLOCK));
}
//fDown
void BoardTests::FDownAfterLeft()
{
    Board board;
    int blockId = board.AddBlockH(0,3,4);
    board.SetBlockF(1,1);
    board.MoveLeft(blockId, 1);
    QCOMPARE(board.GetField(1,1), static_cast<int>(Board::EMPTY_FIELD));
    QCOMPARE(board.GetField(1,6), static_cast<int>(Board::FINAL_BLOCK));
}
void BoardTests::FDownAfterRight()
{
    Board board;
    int blockId = board.AddBlockH(0,3,4);
    board.SetBlockF(1,1);
    board.MoveRight(blockId, 1);
    QCOMPARE(board.GetField(1,1), static_cast<int>(Board::EMPTY_FIELD));
    QCOMPARE(board.GetField(1,6), static_cast<int>(Board::FINAL_BLOCK));
}
void BoardTests::FDownFinal()
{
    Board board;
    int blockId = board.AddBlockH(0,0,1);
    board.SetBlockF(0,1);
    board.SetFinalField(0,7);
    board.MoveRight(blockId, 1);
    QCOMPARE(board.GetField(0,7), static_cast<int>(Board::FINAL_BLOCK));
}
void BoardTests::FDownH()
{
    Board board;
    int blockId = board.AddBlockH(6,1,3);
    board.SetBlockF(2,1);
    board.MoveRight(blockId, 1);
    QCOMPARE(board.GetField(2,5), static_cast<int>(Board::FINAL_BLOCK));
}
void BoardTests::FDownV()
{
    Board board;
    int blockId = board.AddBlockV(2,4,5);
    board.SetBlockF(2,1);
    board.MoveDown(blockId, 1);
    QCOMPARE(board.GetField(2,4), static_cast<int>(Board::FINAL_BLOCK));
}

void BoardTests::Move()
{
    Board board;
    int hId = board.AddBlockH(0,2,3);
    int vId = board.AddBlockV(0,3,4);
    board.Move(MoveDescription(hId, Direction::Left, 1));
    board.Move(MoveDescription(vId, Direction::Up, 1));
    QCOMPARE(board.GetBlockH(hId).LeftCell(), 1);
    QCOMPARE(board.GetBlockV(vId).TopCell(), 2);
    board.Move(MoveDescription(hId, Direction::Right, 1));
    board.Move(MoveDescription(vId, Direction::Down, 1));
    QCOMPARE(board.GetBlockH(hId).LeftCell(), 2);
    QCOMPARE(board.GetBlockV(vId).TopCell(), 3);
}
//undo
void BoardTests::UndoUp()
{
    Board board;
    int blockId = board.AddBlockV(0,4,5);
    board.SetBlockF(0,3);
    Board before(board);
    board.MoveUp(blockId, 2);
    board.Undo();
    QCOMPARE(board, before);
}
void BoardTests::UndoDown()
{
    Board board;
    int blockId = board.AddBlockV(0,3,4);
    board.SetBlockF(0,2);
    Board before{board};
    board.MoveDown(blockId, 2);
    board.Undo();
    QCOMPARE(board, before);
}
void BoardTests::UndoLeft()
{
    Board board;
    int blockId = board.AddBlockH(1,2,3);
    board.SetBlockF(2,4);
    Board before{board};
    board.MoveLeft(blockId, 1);
    board.Undo();
    QCOMPARE(board, before);
}
void BoardTests::UndoRight()
{
    Board board;
    int blockId = board.AddBlockH(1,2,3);
    board.SetBlockF(2,4);
    Board before{board};
    board.MoveRight(blockId, 1);
    board.Undo();
    QCOMPARE(board, before);
}
void BoardTests::UndoTwoMoves()
{
    Board board;
    int blockId = board.AddBlockH(1,2,3);
    board.SetBlockF(2,4);
    Board before{board};
    board.MoveRight(blockId, 1);
    board.MoveRight(blockId, 2);
    board.Undo();
    board.Undo();
    QCOMPARE(board, before);
}

void BoardTests::GetAvailableMovesHLeft()
{
    Board board;
    int blockId = board.AddBlockH(4,2,6);
    vector<MoveDescription> avMoves = board.GetAvailableMoves();
    QCOMPARE((int)avMoves.size(), 2);
    for(int x=0; x<(int)avMoves.size(); ++x){
        QCOMPARE(avMoves[x].BlockId(), blockId);
        QCOMPARE(avMoves[x].Dir(), Direction::Left);
        QCOMPARE(avMoves[x].Distance(), x+1);
    }
}
void BoardTests::GetAvailableMovesHRight()
{
    Board board;
    int blockId = board.AddBlockH(3,0,4);
    vector<MoveDescription> avMoves = board.GetAvailableMoves();
    QCOMPARE((int)avMoves.size(), 2);
    for(int x=0; x<(int)avMoves.size(); ++x){
        QCOMPARE(avMoves[x].BlockId(), blockId);
        QCOMPARE(avMoves[x].Dir(), Direction::Right);
        QCOMPARE(avMoves[x].Distance(), x+1);
    }
}
void BoardTests::GetAvailableMovesVUp()
{
    Board board;
    int blockId = board.AddBlockV(2, 2, 6);
    vector<MoveDescription> avMoves = board.GetAvailableMoves();
    QCOMPARE((int)avMoves.size(), 2);
    for(int y=0; y<(int)avMoves.size(); ++y){
        QCOMPARE(avMoves[y].BlockId(), blockId);
        QCOMPARE(avMoves[y].Dir(), Direction::Up);
        QCOMPARE(avMoves[y].Distance(), y+1);
    }
}
void BoardTests::GetAvailableMovesVDown()
{
    Board board;
    int blockId = board.AddBlockV(6, 0, 4);
    vector<MoveDescription> avMoves = board.GetAvailableMoves();
    QCOMPARE((int)avMoves.size(), 2);
    for(int y=0; y<(int)avMoves.size(); ++y){
        QCOMPARE(avMoves[y].BlockId(), blockId);
        QCOMPARE(avMoves[y].Dir(), Direction::Down);
        QCOMPARE(avMoves[y].Distance(), y+1);
    }
}

