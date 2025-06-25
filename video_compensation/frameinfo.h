#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <cstdint>
#include <cstddef>  

class FrameInfo
{

public:
    static void init(int width, int height);

    static int getWidth();

    static int getHeight();

    static size_t getBytesPerFrame();

    static size_t getLumaSise();

    static size_t getChromaSise();

private:
    static int width;
    static int height;
    static size_t lumaSise;
    static size_t chromaSise;
    static size_t bytesPerFrame;
};

#endif // FRAMEINFO_H

