#include "helpers.h"
using namespace PushMe;
bool IsRowEmpty(PushMe::Board &board, int rowId)
{
    for(int x=0; x<board.InnerSizeX(); ++x)
        if(board.GetField(x, rowId) != Board::EMPTY_FIELD)
            return false;
    return true;
}
bool IsColumnEmpty(PushMe::Board &board, int columnId)
{
    for(int y=0; y<board.InnerSizeY(); ++y)
        if(board.GetField(columnId, y)!= Board::EMPTY_FIELD)
            return false;
    return true;
}
bool AreRowsEmpty(Board &board, int from, int to)
{
    for(;from<=to;++from)
        if(!IsRowEmpty(board, from))
            return false;
    return true;
}
bool AreColumnsEmpty(Board &board, int from, int to)
{
    for(;from<=to;++from)
        if(!IsColumnEmpty(board, from))
            return false;
    return true;
}
