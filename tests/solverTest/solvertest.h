#ifndef SOLVERTESTS_H
#define SOLVERTESTS_H

#include <QTest>
#include <QObject>

class SolverTest : public QObject
{
    Q_OBJECT

public:
    SolverTest();

private Q_SLOTS:
    void vNodeAddFinal();
    void vNodeAddFinalTwoTimes();
    void vNodeAddH();
    void vNodeAddHTwoTimes();
    void vNodeAddV();
    void vNodeAddVTwoTimes();

    void vNodeAddFinalTwoPos();
    void vNodeAddFinalTwoPosTwoTimes();
    void vNodeAddHTwoPos();
    void vNodeAddHTwoPosTwoTimes();
    void vNodeAddVTwoPos();
    void vNodeAddVTwoPosTwoTimes();

    void StepLeft();
    void StepRight();
    void StepUp();
    void StepDown();
};

#endif // SOLVERTESTS_H
