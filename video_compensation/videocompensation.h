#ifndef VIDEOCOMPENSATION_H
#define VIDEOCOMPENSATION_H

#include <frame.h>
#include <map>

using MotionVector     = std::map<std::string,int>;
using MotionVectorsMap = std::map<int, std::map<int, MotionVector >>;

class VideoCompensation
{
public:
    VideoCompensation(int threadsCount = 4);
    VideoCompensation(const VideoCompensation &videoCompensation);
    VideoCompensation& operator=(const VideoCompensation &videoCompensation);

    MotionVectorsMap findMotionVectors(const Frame &currentFrame, const Frame &previousFrame);
    Frame doCompensation(const Frame &currentFrame, const Frame &previousFrame, MotionVectorsMap &motionVectorsMap) const;
private:
    void doVectorSearch(const Frame &currentFrame, const Frame &previousFrame, int threadNumber);
    short SAD(const Block &block1, const Block &block2) const;
    MotionVector findVector(const Block &block, const Frame &frame) const;
    bool isCoordinateValide(int x, int y, int blockSide)const;

    int threadsCount_;
    MotionVectorsMap result_;
};

#endif // VIDEOCOMPENSATION_H
