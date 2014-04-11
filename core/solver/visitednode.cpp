#include "visitednode.h"
#include <iostream>

int PushMe::VisitedNode::expectedChildrenCount = 6;

std::vector<PushMe::IntVector> PushMe::VisitedNode::_extractPositions(const PushMe::Board &board)
{
    std::vector<PushMe::IntVector> blockPositions;
    blockPositions.reserve(board.GetHorizontalBlocks().size()+board.GetVerticalBlocks().size()+1);
    for(auto &bh:board.GetHorizontalBlocks())
        blockPositions.emplace_back(bh.LeftCell(),bh.Y());
    for(auto &bv:board.GetVerticalBlocks())
        blockPositions.emplace_back(bv.X(),bv.TopCell());
    blockPositions.emplace_back(board.GetBlockF().Position());
    return blockPositions;
}

PushMe::VisitedNode::VisitedNode()
{
    _children.reserve(expectedChildrenCount);
}

PushMe::VisitedNode::VisitedNode(const IntVector &blockPos)
    :_position{blockPos}
{
    _children.reserve(expectedChildrenCount);
}
/*blockPositions() has allBlockPositions at the current board state,
 *so if blockId equals size, we are at an end of a recursion.
 *_children has all positions of the next block in line*/
bool PushMe::VisitedNode::HadNodeBeforeCall(int blockId, const std::vector<IntVector> &blockPositions)
{
    ++blockId;
    if((int)blockPositions.size()==blockId)return true;
    for(auto& node:_children)
        if(node._position==blockPositions[blockId])
            return(node.HadNodeBeforeCall(blockId, blockPositions));

    _children.emplace_back(blockPositions[blockId]);
    _children.back().HadNodeBeforeCall(blockId, blockPositions);
    return false;
}

