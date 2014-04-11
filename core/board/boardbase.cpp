#include "boardbase.h"

bool PushMe::operator==(const BoardBase &b1, const BoardBase &b2)
{
    if(b1.InnerSizeX()!=b2.InnerSizeX())return false;
    if(b1.InnerSizeY()!=b2.InnerSizeY())return false;
    if(b1.GetFinalField()!= b2.GetFinalField()) return false;
    if(b1.GetBlockF().Position() != b2.GetBlockF().Position()) return false;
    for(int x=0; x<b1.InnerSizeX(); ++x)
        for(int y=0; y<b1.InnerSizeY(); y++)
            if(b1.GetField(x,y)!=b2.GetField(x,y))
                return false;
    return true;
}
