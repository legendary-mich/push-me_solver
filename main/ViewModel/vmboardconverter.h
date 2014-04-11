#ifndef VMBOARDCONVERTER_H
#define VMBOARDCONVERTER_H

#include <QObject>
#include "vmboardbase.h"

class VMBoardConverter : public QObject
{
    Q_OBJECT
public:
    explicit VMBoardConverter(QObject *parent = 0);
    VMBoardBase *fromBoard, *toBoard;
signals:

public slots:
    void copyBoard();

};

#endif // VMBOARDCONVERTER_H
