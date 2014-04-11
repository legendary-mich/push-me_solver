#include "vmboardbase.h"
#include "Helpers/services.h"
#include <algorithm>
#include <iostream>

using namespace PushMe;
using namespace std;

VMBoardBase::VMBoardBase(QObject *parent) :
    QObject(parent)
{

}

QRectF VMBoardBase::finalField() const
{
    if(_board.get() == nullptr)
        return QRectF();
    return QRectF((_board->GetFinalField().x + 1)*_cellSize, (_board->GetFinalField().y + 1)*_cellSize, _cellSize, _cellSize);
}

QRectF VMBoardBase::finalBlock() const
{
    if(_board.get() == nullptr)
        return QRectF();
    BlockF b = _board->GetBlockF();
    return QRectF((b.Position().x+1)*_cellSize, (b.Position().y+1)*_cellSize, _cellSize, _cellSize);
}
void VMBoardBase::UpdateBlocks()
{
    _blocks.clear();
    if(_board.get() != nullptr){
        for(auto& bh: _board->GetHorizontalBlocks())
            _blocks.push_back(RectFromHBlock(bh));
        for(auto& bv: _board->GetVerticalBlocks())
            _blocks.push_back(RectFromVBlock(bv));
    }
    emit GetBlocksChanged();
}

void VMBoardBase::SetCurrent(float x, float y, float width, float height)
{
    _currentBlock.setX(x); _currentBlock.setY(y);
    _currentBlock.setWidth(width); _currentBlock.setHeight(height);
    emit currentBlockChanged();
}
void VMBoardBase::SetBoard(BoardBase *board)
{
    _board = unique_ptr<BoardBase>(board);
    emit cWidthChanged();
    emit cHeightChanged();
    emit finalFieldChanged();
    emit finalBlockChanged();
    UpdateBlocks();
    SetCurrent();
}


