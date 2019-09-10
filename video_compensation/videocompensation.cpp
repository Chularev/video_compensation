#include "videocompensation.h"

#include <frameinfo.h>

VideoCompensation::VideoCompensation()
{

}

void VideoCompensation::findMotionVector(const Frame &currentFrame, const Frame &previousFrame)
{

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

    int sad = SAD(block, previousFrame.getBlock(block.topLeftX(), block.topLeftY()));

    int areaX = 1;
    int areaY = 1;

    int offsetX = 0;
    int offsetY = 0;

    int posX = block.topLeftX() - block.side() * areaX;
    int posY = block.topLeftY() - block.side() * areaY;

    for (int i = 0; i < areaX * 2 + 1; i++)
    {
        posY += i * block.side();
        for (int j = 0; j < areaY  * 2 + 1; j++)
        {
            int posXInBlock = posX + block.side() * j;
            int tmpSad = SAD(block, previousFrame.getBlock(posXInBlock, posY));
            if (tmpSad < sad)
            {
                offsetX = posXInBlock;
                offsetY = posY;
            }
        }
    }

    return MotionVector();
}

int VideoCompensation::SAD(const Block &block1, const Block &block2) const
{
    int result = 0;
    for (int i = 0; i < block1.side(); i++)
        for (int j = 0; j < block1.side(); j++)
            result += std::abs(block2(i,j).getY() - block1(i,j).getY());
    return result;
}
