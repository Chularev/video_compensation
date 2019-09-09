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

    size_t dst[8];
     __m128i* dst_ptr = reinterpret_cast<__m128i*>(dst) ;

     int a[8];
     int b[8] = { 2, 2, 3, 4,5,6,7,8 };

      __asm__ volatile
      (
       "vmovups %[a], %%ymm0\n\t"	// поместить 4 переменные с плавающей точкой из a в регистр xmm0
       "vmovups %[b], %%ymm1\n\t"	// поместить 4 переменные с плавающей точкой из b в регистр xmm1
       "VMOVDQA %%ymm1,%%ymm0\n\t"
       "vmovups %%ymm0, %[a]\n\t"	// выгрузить результаты из регистра xmm0 по адресам a
       :
       : [a]"m"(*a), [b]"m"(*b)
       : "%ymm0", "%ymm1"
      );

     for (int i=0; i <8; i++)
        std::cout << a[i] << std:: endl;

    return block;
}
