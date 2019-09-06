#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <cstdint>

class FrameInfo
{

public:
    static void init(int width, int height);

    static int getWidth();

    static int getHeight();

    static int64_t getBytesPerFrame();

private:
    static int width;
    static int height;
    static int64_t bytesPerFrame;
};

int FrameInfo::width = 0;
int FrameInfo::height = 0;
int64_t FrameInfo::bytesPerFrame = 0;
#endif // FRAMEINFO_H

void FrameInfo::init(int width, int height)
{
    FrameInfo::width = width;
    FrameInfo::height = height;
    FrameInfo::bytesPerFrame = width * height; // Luma plane
    FrameInfo::bytesPerFrame += (width / 2) * (height / 2) * 2; // U/V planes, half the width and height
}

int FrameInfo::getWidth()
{
    return width;
}

int FrameInfo::getHeight()
{
    return height;
}

int64_t FrameInfo::getBytesPerFrame()
{
    return bytesPerFrame;
}
