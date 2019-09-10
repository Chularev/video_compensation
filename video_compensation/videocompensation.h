#ifndef VIDEOCOMPENSATION_H
#define VIDEOCOMPENSATION_H

#include "motionvector.h"

#include <frame.h>

class VideoCompensation
{
public:
    VideoCompensation();
    void findMotionVector(const Frame &currentFrame, const Frame &previousFrame);
private:
    int SAD(const Block &block1, const Block &block2) const;
    MotionVector findVector(const Block &block, const Frame &frame);
};

#endif // VIDEOCOMPENSATION_H
