#ifndef BOARDTEST_H
#define BOARDTEST_H
#include <QTest>
#include <QObject>

class BoardTests : public QObject
{
    Q_OBJECT

public:
    BoardTests();

private Q_SLOTS:
    void addBlockV();
    void addBlockH();
    void setBlockF();
    void setFField();

    void Copy();
    void Equal();
    void NotEqualSX();
    void NotEqualSY();
    void NotEqualFB();
    void NotEqualFF();
    void NotEqualGetField();

    void maxDownWallBlocks();
    void maxDownFinal();//finalField
    void maxDownHBlocks();
    void maxDownVBlocks();
    void maxDownFBlocks();

    void maxUpWall();
    void maxUpFinal();//finalField
    void maxUpH();
    void maxUpV();
    void maxUpFWall();
    void maxUpFFinal();
    void maxUpFH();
    void maxUpFV();

    void maxLeftWall();
    void maxLeftFinal();//finalField
    void maxLeftH();
    void maxLeftV();
    void maxLeftFWall();
    void maxLeftFFinal();
    void maxLeftFH();
    void maxLeftFV();
    void maxLeftFHole();
    void maxLeftFOnH();

    void maxRightWall();
    void maxRightFinal();//finalField
    void maxRightH();
    void maxRightV();
    void maxRightFWall();
    void maxRightFFinal();
    void maxRightFH();
    void maxRightFV();
    void maxRightFHole();
    void maxRightFOnH();

    void moveUp();
    void moveUpFField();
    void moveDown();
    void moveLeft();
    void moveLeftFField();
    void moveRight();
    void moveRightFField();

    void FDownAfterLeft();
    void FDownAfterRight();

    void FDownFinal();
    void FDownH();
    void FDownV();

    void Move();

    void UndoUp();
    void UndoDown();
    void UndoLeft();
    void UndoRight();
    void UndoTwoMoves();

    void GetAvailableMovesHLeft();
    void GetAvailableMovesHRight();
    void GetAvailableMovesVUp();
    void GetAvailableMovesVDown();
};

#endif // BOARDTEST_H

