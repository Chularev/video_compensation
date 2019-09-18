#include "videocompensation.h"

#include <frameinfo.h>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <cmath>

VideoCompensation::VideoCompensation(int threadsCount)
    : threadsCount_(threadsCount)
{

}

VideoCompensation::VideoCompensation(const VideoCompensation &videoCompensation)
{
    threadsCount_ = videoCompensation.threadsCount_;
    result_ = videoCompensation.result_;
}

VideoCompensation &VideoCompensation::operator=(const VideoCompensation &videoCompensation)
{
    threadsCount_ = videoCompensation.threadsCount_;
    result_ = videoCompensation.result_;
    return *this;
}

MotionVectorsMap VideoCompensation::findMotionVectors(const Frame &currentFrame, const Frame &previousFrame)
{
    if (threadsCount_ < 1)
        throw std::invalid_argument("Threads count can't be less than 1");

    size_t threadsCount = static_cast<size_t>(threadsCount_);
    std::vector<std::thread> threads(threadsCount);
    for (size_t i = 0; i < threadsCount; i++)
        threads[i] = std::thread(&VideoCompensation::doVectorSearch, this, std::ref(currentFrame), std::ref(previousFrame),i);
    for (size_t i = 0; i < threadsCount; i++)
    {
         if (threads[i].joinable())
            threads[i].join();
    }

    return result_;
}

void VideoCompensation::doVectorSearch(const Frame &currentFrame, const Frame &previousFrame, int threadNumber)
{
    for (int y = Block::side() * threadNumber; y < FrameInfo::getHeight() -  Block::side() + 1; y += Block::side() * threadsCount_)
    {
        for (int x = 0; x < FrameInfo::getWidth() -  Block::side() + 1; x += Block::side())
        {
            Block block = currentFrame.getBlock(x,y);
            result_[x][y] = findVector(block, previousFrame);
        }
    }
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

    short sad = SAD(block, previousFrame.getBlock( block.topLeftX(), block.topLeftY()));

    short sadStart = sad;
    std::vector<short> sadVector(8, static_cast<short>(pow(2,16) - 1));
    size_t sadIndex = 0;

    MotionVector result;
    result["x"] = 0;
    result["y"] = 0;


    int offsetY = block.side() * -1;
    for (int i = 0; i < 3; i++, offsetY += block.side())
    {
        int currentY = block.topLeftY() + offsetY;
        for (int j = 0, offsetX = block.side() * -1; j < 3; j++, offsetX +=  block.side())
        {
            int currentX = block.topLeftX() + offsetX;

            if (!isCoordinateValide(currentX, currentY, block.side()))
            {
                ++sadIndex;
                continue;
            }
            if (offsetX == 0 && offsetY == 0)
                continue;

            sadVector[sadIndex++] = SAD(block, previousFrame.getBlock(currentX, currentY));
        }
    }

    short minSad[8];

    __asm__ volatile
            (
                "movdqa %[sadVector],%%xmm0\n\t"
                "PHMINPOSUW %%xmm0, %%xmm0\n\t"
                "movdqa %%xmm0, %[minSad]\n\t"
                :
                : [sadVector]"m"(sadVector[0]),[minSad]"m"(minSad)
                : "%xmm0","%xmm1"
                );
    if (sadStart <= minSad[0])
        return result;

    if (minSad[1] < 3)
        result["y"] = Block::side() * -1;
    else if (minSad[1] > 4)
        result["y"] = Block::side();

    if (minSad[1] == 0 || minSad[1] == 3 || minSad[1] == 5)
        result["x"] = Block::side() * -1;

    if (minSad[1] == 2 || minSad[1] == 4 || minSad[1] == 7)
        result["x"] = Block::side();

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

short VideoCompensation::SAD(const Block &block1, const Block &block2) const
{
    short result = 0;
    for (int i = 0; i < block1.side(); i++)
        for (int j = 0; j < block1.side(); j++)
            result += std::abs(block2(i,j).getY() - block1(i,j).getY());
    return result;
}
