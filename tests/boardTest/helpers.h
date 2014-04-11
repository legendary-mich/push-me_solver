#ifndef HELPERS_H
#define HELPERS_H
#include "board/board.h"

bool IsRowEmpty(PushMe::Board &board, int rowId);
bool IsColumnEmpty(PushMe::Board &board, int columnId);
bool AreRowsEmpty(PushMe::Board &board, int from, int to);
bool AreColumnsEmpty(PushMe::Board &board, int from, int to);
#endif // HELPERS_H
