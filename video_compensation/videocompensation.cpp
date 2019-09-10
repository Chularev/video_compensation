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
            Block from = currentFrame.getBlock(i,j);
        }

    }
}

MotionVector VideoCompensation::findVector(const Block &block, const Frame &frame1)
{

    int sad = SAD(block, frame1.getBlock(block.topLeftX(), block.topLeftY()));
    MotionVector resunt;
    for (int i = 0; i < 9; i++)
    {

    }

}

int VideoCompensation::SAD(const Block &block1, const Block &block2) const
{
    int result = 0;
    for (int i = 0; i < block1.side(); i++)
        for (int j = 0; j < block1.side(); j++)
            result += std::abs(block2(i,j).getY() - block1(i,j).getY());
    return result;
}
