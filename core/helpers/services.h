#ifndef SERVICES_H
#define SERVICES_H
#include "board/boardbase.h"
#include "board/board.h"

#include<memory>
#include<fstream>

namespace PushMe{
PushMe::Board *CreateFromBase(const BoardBase &base);
}

#endif // SERVICES_H
