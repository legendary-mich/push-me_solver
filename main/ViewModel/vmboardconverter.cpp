#include "vmboardconverter.h"

VMBoardConverter::VMBoardConverter(QObject *parent) :
    QObject(parent)
{
}

void VMBoardConverter::copyBoard()
{
    toBoard->SetBoardClone(fromBoard->GetBoard());
}
