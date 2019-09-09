#ifndef FRAME_H
#define FRAME_H

#include "block.h"
#include "pixel.h"

#include<vector>

class Frame
{
public:
    Frame(const std::vector<char> &dataY, const std::vector<char> &dataU, const std::vector<char> &dataV, int index);
    int index() const;

    std::vector<char> dataY() const;

    std::vector<char> dataV() const;

    std::vector<char> dataU() const;

    Pixel getPixel(int coordX, int coordY) const;
    void setPixel(const Pixel &pixel);

    Block getBlock(int topLeftX, int topLeftY) const;

private:
    std::vector<char> dataY_;
    std::vector<char> dataU_;
    std::vector<char> dataV_;
    int index_;
};

#endif // FRAME_H
