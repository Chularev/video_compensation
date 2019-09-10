#include "videocompensation.h"

#include <frameinfo.h>
#include  <stdexcept>

VideoCompensation::VideoCompensation(int searchAreaInBlocks)
    : searchAreaInBlocks_(searchAreaInBlocks)
{

}

void VideoCompensation::findMotionVector(const Frame &currentFrame, const Frame &previousFrame)
{
    if (searchAreaInBlocks_ < 1)
        throw std::invalid_argument("Search area can't be less than 1");

    for (int i = 0; i < FrameInfo::getWidth(); i += Block::side())
    {
        for (int j = 0; j < FrameInfo::getHeight(); j += Block::side())
        {
            Block block = currentFrame.getBlock(i,j);
        }

    }
}

MotionVector VideoCompensation::findVector(const Block &block, const Frame &previousFrame)
{

    int sad = SAD(block, previousFrame.getBlock( block.topLeftX(), block.topLeftY()));

    int offsetX = 0;
    int offsetY = 0;

    int posX = block.topLeftX() - block.side() * searchAreaInBlocks_;
    int posY = block.topLeftY() - block.side() * searchAreaInBlocks_;

    for (int i = 0; i < searchAreaInBlocks_ * 2 + 1; i++)
    {
        posY += i * block.side();
        for (int j = 0; j < searchAreaInBlocks_ * 2 + 1; j++)
        {
            int currentX = posX + block.side() * j;
            if (!isCoordinateValide(currentX,posY))
                continue;

            if (currentX == 0 && posY == 0)
                continue;

            int tmpSad = SAD(block, previousFrame.getBlock(currentX, posY));
            if (tmpSad < sad)
            {
                offsetX = currentX;
                offsetY = posY;
            }
        }
    }

    return MotionVector();
}

bool VideoCompensation::isCoordinateValide(int x, int y) const
{
    return x < FrameInfo::getWidth() && y < FrameInfo::getHeight();
}

int VideoCompensation::SAD(const Block &block1, const Block &block2) const
{
    int result = 0;
    for (int i = 0; i < block1.side(); i++)
        for (int j = 0; j < block1.side(); j++)
            result += std::abs(block2(i,j).getY() - block1(i,j).getY());
    return result;
}
