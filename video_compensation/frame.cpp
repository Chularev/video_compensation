#include "frame.h"

#include <frameinfo.h>
#include <stdexcept>
#include <x86intrin.h>

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

#include <iostream>

Block Frame::getBlock(int topLeftX, int topLeftY, int side) const
{
    Block block(topLeftX,topLeftY,side);

    size_t dst[4];
     __m128i* dst_ptr = reinterpret_cast<__m128i*>(dst) ;

     //short jjj = static_cast<short>(FrameInfo::getWidth());
     __m128i width = _mm_set1_epi32 (FrameInfo::getWidth());
     __m128i tmp = _mm_set1_epi32 (2);
     __m128i res = _mm_mul_epu32(width, tmp);
       __m128i res2 = _mm_mul_epu32(_mm_srli_si128(width,4), _mm_srli_si128(tmp,4));
     //__m128i res = _mm_add_epi16(width, tmp);
     _mm_store_si128(dst_ptr, res);
     dst_ptr ++;
     _mm_store_si128(dst_ptr , res2);

     for (int i = 0; i < 4; i++)
        std::cout << dst[i] << std::endl;

    //FrameInfo::getWidth() * coordY + coordX

    return block;
}
