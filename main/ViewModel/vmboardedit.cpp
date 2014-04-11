#include "vmboardedit.h"

#include "Helpers/services.h"
#include <stdexcept>

using namespace PushMe;
using namespace std;

VMBoardEdit::VMBoardEdit(QObject *parent)
    :VMBoardBase(parent)
{
    //loadBoard("");
}
void VMBoardEdit::AdjustCurrent()
{
    int x = min(_startingPos.x, _endingPos.x);
    int y = min(_startingPos.y, _endingPos.y);
    int right = max(_startingPos.x, _endingPos.x);
    int bottom = max(_startingPos.y, _endingPos.y);
    SetCurrent((x+1)*cellSize(), (y+1)*cellSize(), (right-x+1)*cellSize(), (bottom-y+1)*cellSize());
}

void VMBoardEdit::mousePressed(float mouseX, float mouseY, bool shiftPressed)
{
    if(_board.get() == nullptr) return;
    BoardEditor &be = static_cast<BoardEditor&>(*_board.get());
    int x = (int)mouseX/cellSize()-1;
    int y = (int)mouseY/cellSize()-1;
    if(be.InBoundsOuter(x,y)){
        be.SetFinalField(x,y);
        emit finalFieldChanged();
    }
    else if(shiftPressed){
        be.SetBlockF(x, y);
        emit finalBlockChanged();
        UpdateBlocks();
    }
    else if(be.GetBlockF().Position() != IntVector(x, y)){
        _startingPos = IntVector(x,y);
        _endingPos = IntVector(x,y);
        AdjustCurrent();
        _isCurrentSelected = true;
    }
}

void VMBoardEdit::mouseMoved(float mouseX, float mouseY)
{
    if(_isCurrentSelected){
        int x = (int)mouseX/cellSize()-1;
        int y = (int)mouseY/cellSize()-1;
        int hDif = abs(x - _startingPos.x)+1;
        int vDif = abs(y - _startingPos.y)+1;
        if(hDif>vDif){
            y = _startingPos.y;
            vDif = 1;
        }
        else{
            x = _startingPos.x;
            hDif = 1;
        }
        IntVector temp{x,y};
        if(temp == _endingPos) return;
        if(_board->GetBlockF().Position() == temp)return;
        if(!_board->InBoundsInner(temp.x, temp.y)) return;
        if(abs(temp.x - _endingPos.x)>1 || abs(temp.y - _endingPos.y)>1) return;//to not jumb above the fBlock
        _endingPos = IntVector(x,y);
        AdjustCurrent();
    }
}

void VMBoardEdit::mouseReleased()
{
    if(_isCurrentSelected && _board.get() != nullptr){
        _isCurrentSelected = false;
        BoardEditor &be = static_cast<BoardEditor&>(*_board.get());
        int hDif = abs(_startingPos.x - _endingPos.x);
        int vDif = abs(_startingPos.y - _endingPos.y);
        if(hDif>vDif)
            be.AddBlockH(_startingPos.y, min(_endingPos.x, _startingPos.x), max(_endingPos.x, _startingPos.x));
        else
            be.AddBlockV(_startingPos.x, min(_endingPos.y, _startingPos.y), max(_endingPos.y, _startingPos.y));
        SetCurrent();
        UpdateBlocks();
    }
}

void VMBoardEdit::newBoard()
{
    unique_ptr<BoardEditor> board(new BoardEditor());
    board->SetName("newBoard");
    SetBoard(board.release());
}

void VMBoardEdit::saveBoard(QString fullPath)
{
    Q_UNUSED(fullPath);
}
void VMBoardEdit::loadBoard(QString fullPath)
{
    Q_UNUSED(fullPath);
}


