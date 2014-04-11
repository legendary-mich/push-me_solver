#ifndef VMBOARDEDIT_H
#define VMBOARDEDIT_H

#include <iostream>
#include "vmboardbase.h"
#include "board/boardeditor.h"

class VMBoardEdit : public VMBoardBase
{
    Q_OBJECT
public:
    explicit VMBoardEdit(QObject *parent = 0);

private:
    void AdjustCurrent();
    PushMe::IntVector _startingPos, _endingPos;
    bool _isCurrentSelected{false};
public slots:
    void newBoard();
    void saveBoard(QString fullPath);
    void loadBoard(QString fullPath)override;
    void mousePressed(float mouseX, float mouseY, bool shiftPressed) override;
    void mouseMoved(float mouseX, float mouseY) override;
    void mouseReleased() override;
};

#endif // VMBOARDEDIT_H
