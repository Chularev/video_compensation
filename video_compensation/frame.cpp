#include "frame.h"

#include <frameinfo.h>
#include <stdexcept>
#include <x86intrin.h>
#include <iostream>

Frame::Frame(const std::vector<char> &dataY, const std::vector<char> &dataU, const std::vector<char> &dataV, int index)
    : dataY_(dataY), dataU_(dataU), dataV_(dataV),  index_(index)
{

}

Frame::Frame(int index)
    : index_(index)
{
    dataY_ = std::vector<char>(FrameInfo::getLumaSise());
    dataU_ = std::vector<char>(FrameInfo::getChromaSise());
    dataV_ = std::vector<char>(FrameInfo::getChromaSise());
}

Frame::Frame(const Frame &frame)
{
    index_ = frame.index_;
    dataY_ = frame.dataY_;
    dataU_ = frame.dataU_;
    dataV_ = frame.dataV_;
}

Frame &Frame::operator=(const Frame &frame)
{
    index_ = frame.index_;
    dataY_ = frame.dataY_;
    dataU_ = frame.dataU_;
    dataV_ = frame.dataV_;
    return *this;
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

Pixel Frame::getPixel(int coordX, int coordY) const
{
    if (coordX < 0 || coordX >= FrameInfo::getWidth())
        throw std::out_of_range("invalid coordinate X");

    if (coordY < 0 || coordY >= FrameInfo::getHeight())
        throw std::out_of_range("invalid coordinate Y");

    Pixel pixel;
    pixel.setCoordX(coordX);
    pixel.setCoordY(coordY);

    size_t lumaIndex = static_cast<size_t>(FrameInfo::getWidth() * coordY + coordX);
    pixel.setY(dataY_[lumaIndex]);
    pixel.setLumaCoord(lumaIndex);

    size_t chromaIndex = static_cast<size_t>((FrameInfo::getWidth() / 2) * (coordY /2) + coordX / 2);
    pixel.setChromaCoord(chromaIndex);

    pixel.setU(dataU_[chromaIndex]);
    pixel.setV(dataV_[chromaIndex]);

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

Block Frame::getBlock(int topLeftX, int topLeftY) const
{
    Block block(topLeftX,topLeftY);
    if (topLeftX < 0 || topLeftX + block.side() > FrameInfo::getWidth())
        throw std::out_of_range("Invalid argument x");

    if (topLeftY < 0 || topLeftY + block.side() > FrameInfo::getHeight())
        throw std::out_of_range("Invalid argument y");

    for (int i = 0; i < block.side(); i++)
        for (int j = 0; j < block.side(); j++)
            block(i,j) = getPixel(i + topLeftX,j + topLeftY);

    return block;
}

void Frame::setBlock(const Block &block)
{
    for (int i = 0; i < block.side(); i++)
        for(int j = 0; j < block.side(); j++)
            setPixel(block(i,j));
}
/*
Block Frame::getBlock(int topLeftX, int topLeftY) const
{
    Block block(topLeftX,topLeftY);

    char tmpBlock[16][16];

    for (int i = 0; i < 16; i++)
    {
        size_t index = static_cast<size_t>(FrameInfo::getWidth() * (i+ topLeftY));
        __m128i *src_cacheline = reinterpret_cast<__m128i *>(const_cast<char*>(&dataY_[index]));
        __asm__ volatile
                (
                    "movntdqa %[src],%%xmm0\n\t"
                    "movdqa %%xmm0, %[a]\n\t"
                    :
                    : [a]"m"(tmpBlock[i]), [src]"m"(*src_cacheline )
                    : "%xmm0"
                    );
    }
    for (int i=0; i <16; i++)
    {
        for (int j=0; j <16; j++)
            if (getPixel(i,j).getY() != tmpBlock[j][i])
                std::cout << "not";
        std::cout <<  std:: endl;
    }
    return block;
}
*/
