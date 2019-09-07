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

    static int64_t getLumaSise();

    static int64_t getChromaSise();

private:
    static int width;
    static int height;
    static int64_t lumaSise;
    static int64_t chromaSise;
    static int64_t bytesPerFrame;
};

#endif // FRAMEINFO_H

