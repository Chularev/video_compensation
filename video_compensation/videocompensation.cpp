#include "videocompensation.h"

#include <frameinfo.h>
#include <stdexcept>
#include <iostream>

VideoCompensation::VideoCompensation(int searchAreaInBlocks)
    : searchAreaInBlocks_(searchAreaInBlocks)
{

}

MotionVectorsMap VideoCompensation::findMotionVectors(const Frame &currentFrame, const Frame &previousFrame)
{
    if (searchAreaInBlocks_ < 1)
        throw std::invalid_argument("Search area can't be less than 1");

    MotionVectorsMap result;
    for (int i = 0; i < FrameInfo::getWidth() -  Block::side() + 1; i += Block::side())
    {
        for (int j = 0; j < FrameInfo::getHeight() -  Block::side() + 1; j += Block::side())
        {
            Block block = currentFrame.getBlock(i,j);
            result[i][j] = findVector(block, previousFrame);
        }
    }
    return result;
}

Frame VideoCompensation::doCompensation(const Frame &currentFrame, const Frame &previousFrame, MotionVectorsMap &offset) const
{
    Frame result(currentFrame.index());
    for (int i = 0; i < FrameInfo::getWidth() - Block::side() + 1; i += Block::side())
    {
        for (int j = 0; j < FrameInfo::getHeight() - Block::side() + 1; j += Block::side())
        {
            Block current = currentFrame.getBlock(i,j);
            Block previous = previousFrame.getBlock(i + offset[i][j]["x"], j + offset[i][j]["y"]);
            Block resultBlock = current - previous;
            result.setBlock(resultBlock);
        }
    }
    return  result;

}

MotionVector VideoCompensation::findVector(const Block &block, const Frame &previousFrame) const
{

    int sad = SAD(block, previousFrame.getBlock( block.topLeftX(), block.topLeftY()));

    MotionVector result;
    result["x"] = 0;
    result["y"] = 0;

    int posX = block.topLeftX() - block.side() * searchAreaInBlocks_;
    int posY = block.topLeftY() - block.side() * searchAreaInBlocks_;

    for (int i = 0; i < searchAreaInBlocks_ * 2 + 1; i++)
    {
        for (int j = 0; j < searchAreaInBlocks_ * 2 + 1; j++)
        {
            int currentX = posX + block.side() * j;
            if (!isCoordinateValide(currentX, posY, block.side()))
                continue;

            if (currentX == 0 && posY == 0)
                continue;

            int tmpSad = SAD(block, previousFrame.getBlock(currentX, posY));
            if (tmpSad < sad)
            {
                result["x"] = currentX - block.topLeftX();
                result["y"] = posY     - block.topLeftY();
                if (sad == 0)
                    return result;
            }
            posY += i * block.side();
        }
    }

    return result;
}

bool VideoCompensation::isCoordinateValide(int x, int y, int blockSide) const
{
    if (x < 0 || x + blockSide >= FrameInfo::getWidth())
        return false;

    if (y < 0 || y + blockSide >= FrameInfo::getHeight())
        return false;
    return true;
}

int VideoCompensation::SAD(const Block &block1, const Block &block2) const
{
    int result = 0;
    for (int i = 0; i < block1.side(); i++)
        for (int j = 0; j < block1.side(); j++)
            result += std::abs(block2(i,j).getY() - block1(i,j).getY());
    return result;
}
