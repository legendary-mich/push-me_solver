#ifndef VMBOARDBASE_H
#define VMBOARDBASE_H

#include <QObject>
#include <memory>
#include <vector>
#include <QRect>
#include <QVariant>
#include <QVariantList>
#include <QString>
#include "board/boardbase.h"

class VMBoardBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int cellSize READ cellSize WRITE setcellSize NOTIFY cellSizeChanged)
    Q_PROPERTY(int cWidth READ cWidth NOTIFY cWidthChanged)
    Q_PROPERTY(int cHeight READ cHeight NOTIFY cHeightChanged)
    Q_PROPERTY(QRectF finalField READ finalField NOTIFY finalFieldChanged)
    Q_PROPERTY(QRectF finalBlock READ finalBlock NOTIFY finalBlockChanged)
    Q_PROPERTY(QRectF currentBlock READ currentBlock NOTIFY currentBlockChanged)
    Q_PROPERTY(QVariantList GetBlocks READ GetBlocks NOTIFY GetBlocksChanged)
public:
    explicit VMBoardBase(QObject *parent = 0);
    //virtual ~VMBoardBase(){}
    int cellSize()const{return _cellSize;}
    void setcellSize(int val){if(_cellSize == val)return;_cellSize = val; emit cellSizeChanged();
                              emit GetBlocksChanged(); emit finalFieldChanged(); emit finalBlockChanged();}
    int cWidth()const{return _board.get() == nullptr? 9 : _board->InnerSizeX() + 2;}
    int cHeight()const{return _board.get() == nullptr? 9 : _board->InnerSizeY() + 2;}
    QRectF finalField()const;
    QRectF finalBlock()const;
    QRectF currentBlock()const{return _currentBlock;}
    QVariantList GetBlocks()const{return _blocks;}
    const PushMe::BoardBase *GetBoard()const{return _board.get();}
    virtual void SetBoardClone(const PushMe::BoardBase *board){Q_UNUSED(board);}
signals:
    void cellSizeChanged();
    void cWidthChanged();
    void cHeightChanged();
    void currentBlockChanged();
    void GetBlocksChanged();
    void finalFieldChanged();
    void finalBlockChanged();
public slots:
    virtual void loadBoard(QString fullPath)=0;
    virtual void mousePressed(float mouseX, float mouseY, bool shiftPressed)=0;
    virtual void mouseMoved(float mouseX, float mouseY)=0;
    virtual void mouseReleased()=0;
protected:
    std::unique_ptr<PushMe::BoardBase> _board;
    void UpdateBlocks();
    void SetCurrent(float x = 0, float y = 0, float width = 0, float height = 0);
    void SetBoard(PushMe::BoardBase *board);
private:
    int _cellSize = 12;
    QVariantList _blocks;
    QRectF _currentBlock;

    inline QRectF RectFromHBlock(const PushMe::BlockH &bh, int extendLeft = 0, int extendRight = 0)const{
        return QRectF((bh.LeftCell()+1-extendLeft)*_cellSize, (bh.Y()+1)*_cellSize, (bh.Width()+extendRight+extendLeft)*_cellSize, _cellSize);
    }
    inline QRectF RectFromVBlock(const PushMe::BlockV &bv, int extendUp = 0, int extendDown = 0)const{
        return QRectF((bv.X()+1)*_cellSize, (bv.TopCell()+1-extendUp)*_cellSize, _cellSize, (bv.Height()+extendDown+extendUp)*_cellSize);
    }
};

#endif // VMBOARDBASE_H
