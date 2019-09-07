#include "pixel.h"

#include <stdexcept>

Pixel::Pixel()
{

}

Pixel::Pixel(const Pixel &pixel)
{
    lumaCoord = pixel.lumaCoord;
    chromaCoord = pixel.chromaCoord;

    xCoord = pixel.xCoord;
    yCoord = pixel.yCoord;
    Y = pixel.Y;
    U = pixel.U;
    V = pixel.V;
}


int Pixel::getCoordX() const
{
    return xCoord;
}

void Pixel::setCoordX(int value)
{
    xCoord = value;
}

int Pixel::getCoordY() const
{
    return yCoord;
}

void Pixel::setCoordY(int value)
{
    yCoord = value;
}

char Pixel::getY() const
{
    return Y;
}

void Pixel::setY(char value)
{
    Y = value;
}

char Pixel::getU() const
{
    return U;
}

void Pixel::setU(char value)
{
    U = value;
}

char Pixel::getV() const
{
    return V;
}

void Pixel::setV(char value)
{
    V = value;
}

size_t Pixel::getChromaCoord() const
{
    return chromaCoord;
}

void Pixel::setChromaCoord(const size_t &value)
{
    chromaCoord = value;
}

size_t Pixel::getLumaCoord() const
{
    return lumaCoord;
}

void Pixel::setLumaCoord(const size_t &value)
{
    lumaCoord = value;
}

Pixel Pixel::operator-(const Pixel &pixel) const
{
    Pixel newPixel(*this);

    newPixel.Y -= pixel.getY();
    newPixel.Y = newPixel.Y < 0 ? 0 : newPixel.Y;

//    newPixel.U -= pixel.getU();
//    newPixel.U = newPixel.U < 0 ? 0 : newPixel.U;

//    newPixel.V -= pixel.getV();
//    newPixel.V = newPixel.V < 0 ? 0 : newPixel.V;

    return newPixel;
}
