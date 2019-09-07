#include <frameinfo.h>

int FrameInfo::width = 0;
int FrameInfo::height = 0;
int64_t FrameInfo::bytesPerFrame = 0;
int64_t FrameInfo::lumaSise = 0;
int64_t FrameInfo::chromaSise = 0;

void FrameInfo::init(int width, int height)
{
    FrameInfo::width = width;
    FrameInfo::height = height;
    FrameInfo::lumaSise = width * height;
    FrameInfo::chromaSise = (width / 2) * (height / 2);
    FrameInfo::bytesPerFrame = FrameInfo::lumaSise + FrameInfo::chromaSise * 2; // for U and V
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

int64_t FrameInfo::getLumaSise()
{
    return lumaSise;
}

int64_t FrameInfo::getChromaSise()
{
    return chromaSise;
}

