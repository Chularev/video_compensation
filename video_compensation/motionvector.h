#ifndef MOTIONVECTOR_H
#define MOTIONVECTOR_H


class MotionVector
{
public:
    MotionVector();
private:
    int frameIndex_;
    int blockPositionX_;
    int blockPositionY_;
    int offsetX_;
    int offsetY_;
};

#endif // MOTIONVECTOR_H
