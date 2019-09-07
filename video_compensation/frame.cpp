#include "frame.h"

#include <frameinfo.h>
#include <stdexcept>

Frame::Frame(const std::vector<char> &dataY, const std::vector<char> &dataU, const std::vector<char> &dataV, int index)
    : dataY_(dataY), dataU_(dataU), dataV_(dataV),  index_(index)
{

}

int Frame::index() const
{
    return index_;
}

std::vector<char> Frame::dataY() const
{
    return dataY_;
}

std::vector<char> Frame::dataV() const
{
    return dataV_;
}

std::vector<char> Frame::dataU() const
{
    return dataU_;
}

Pixel Frame::getPixel(int Xcoord, int Ycoord) const
{
    if (Xcoord < 0 || Xcoord >= FrameInfo::getWidth())
        throw std::out_of_range("invalid coordinate X");

    if (Ycoord < 0 || Ycoord >= FrameInfo::getHeight())
      throw std::out_of_range("invalid coordinate Y");

    Pixel pixel;
    pixel.setCoordX(Xcoord);
    pixel.setCoordY(Ycoord);

    size_t index = 0;

    index = static_cast<size_t>(FrameInfo::getWidth() * Ycoord + Xcoord);
    pixel.setY(dataY_[index]);
    pixel.setLumaCoord(index);

    index = static_cast<size_t>((FrameInfo::getWidth() / 2) * (Ycoord /2) + Xcoord / 2);
    pixel.setChromaCoord(index);

    pixel.setU(dataU_[index]);
    pixel.setV(dataV_[index]);

    pixel.setCoordX(Xcoord);
    pixel.setCoordY(Ycoord);

    return pixel;
}

void Frame::setPixel(const Pixel &pixel)
{

    if (pixel.getCoordX() < 0 || pixel.getCoordX() >= FrameInfo::getWidth())
        throw std::out_of_range("invalid coordinate X");

    if (pixel.getCoordY() < 0 || pixel.getCoordY() >= FrameInfo::getHeight())
      throw std::out_of_range("invalid coordinate Y");

    dataY_[pixel.getLumaCoord()] = pixel.getY();
    dataU_[pixel.getChromaCoord()] = pixel.getU();
    dataV_[pixel.getChromaCoord()] = pixel.getV();
}
