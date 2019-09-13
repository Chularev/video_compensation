#include "videocompensation.h"

#include <frameinfo.h>
#include <stdexcept>
#include <iostream>
#include <thread>


VideoCompensation::VideoCompensation(int searchAreaInBlocks, int threadsCount)
    : searchAreaInBlocks_(searchAreaInBlocks), threadsCount_(threadsCount)
{

}

VideoCompensation::VideoCompensation(const VideoCompensation &videoCompensation)
{
    searchAreaInBlocks_ = videoCompensation.searchAreaInBlocks_;
    threadsCount_ = videoCompensation.threadsCount_;
    result_ = videoCompensation.result_;
}

VideoCompensation &VideoCompensation::operator=(const VideoCompensation &videoCompensation)
{
    searchAreaInBlocks_ = videoCompensation.searchAreaInBlocks_;
    threadsCount_ = videoCompensation.threadsCount_;
    result_ = videoCompensation.result_;
    return *this;
}

MotionVectorsMap VideoCompensation::findMotionVectors(const Frame &currentFrame, const Frame &previousFrame)
{
    if (searchAreaInBlocks_ < 1)
        throw std::invalid_argument("Search area can't be less than 1");

    if (threadsCount_ < 1)
        throw std::invalid_argument("Threads count can't be less than 1");

    size_t threadsCount = static_cast<size_t>(threadsCount_);
    std::vector<std::thread> threads(threadsCount);
    for (size_t i = 0; i < threadsCount; i++)
    {
        threads[i] = std::thread(&VideoCompensation::doVectorSearch, this, std::ref(currentFrame), std::ref(previousFrame),i);
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
