#include "services.h"
#include <memory>

using namespace std;

PushMe::Board *PushMe::CreateFromBase(const PushMe::BoardBase &base)
{
    unique_ptr<Board> board{new Board(base.InnerSizeX(), base.InnerSizeY())};
    board->SetFinalField(base.GetFinalField().x, base.GetFinalField().y);
    board->SetBlockF(base.GetBlockF().X(), base.GetBlockF().Y());
    for(const auto &bh : base.GetHorizontalBlocks())
        board->AddBlockH(bh.Y(), bh.LeftCell(), bh.RightCell());
    for(const auto &bv :base.GetVerticalBlocks())
        board->AddBlockV(bv.X(), bv.TopCell(), bv.BottomCell());
    board->MoveFBlockDown();
    return board.release();
}
