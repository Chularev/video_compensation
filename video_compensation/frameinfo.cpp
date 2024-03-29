#include <frameinfo.h>

int FrameInfo::width = 0;
int FrameInfo::height = 0;
size_t FrameInfo::bytesPerFrame = 0;
size_t FrameInfo::lumaSise = 0;
size_t FrameInfo::chromaSise = 0;

void FrameInfo::init(int width, int height)
{
    FrameInfo::width = width;
    FrameInfo::height = height;
    FrameInfo::lumaSise = static_cast<size_t>(width * height);
    FrameInfo::chromaSise = static_cast<size_t>((width / 2) * (height / 2));
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

size_t FrameInfo::getBytesPerFrame()
{
    return bytesPerFrame;
}

size_t FrameInfo::getLumaSise()
{
    return lumaSise;
}

size_t FrameInfo::getChromaSise()
{
    return chromaSise;
}

