#ifndef VIDEOCOMPENSATION_H
#define VIDEOCOMPENSATION_H

#include <frame.h>

class VideoCompensation
{
public:
    VideoCompensation();
    static void findMotionVector(const Frame &frameFrom, const Frame &frameTo);
};

#endif // VIDEOCOMPENSATION_H
