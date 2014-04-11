#ifndef BOARDEDITOR_H
#define BOARDEDITOR_H
#include "boardbase.h"
#include <functional>

namespace PushMe{
class BoardEditor : public BoardBase
{
public:
    explicit BoardEditor(int innerSizeX = 7, int innerSizeY = 7)
        :BoardBase(innerSizeX, innerSizeY)
    {}
    int GetField(int x, int y) const override;
    int AddBlockH(int y, int leftCell, int rightCell) override;
    int AddBlockV(int x, int topCell, int bottomCell) override;
    void SetBlockF(int x, int y) override;
    void SetFinalField(int x, int y) override;

    ~BoardEditor()override{}
private:
    void EraseHorizontals(std::function<bool(const BlockH &bh)> func);
    void EraseVerticals(std::function<bool(const BlockV &bv)> func);
};
}
#endif // BOARDEDITOR_H
