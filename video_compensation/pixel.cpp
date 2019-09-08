#include "pixel.h"

#include <stdexcept>

Pixel::Pixel()
{
    lumaCoord_ = chromaCoord_ = coordX_
               = coordY_ = Y_ = U_ = V_ = 0;

}

Pixel::Pixel(const Pixel &pixel)
{
    lumaCoord_   = pixel.lumaCoord_;
    chromaCoord_ = pixel.chromaCoord_;

    coordX_ = pixel.coordX_;
    coordY_ = pixel.coordY_;
    Y_ = pixel.Y_;
    U_ = pixel.U_;
    V_ = pixel.V_;
}


int Pixel::getCoordX() const
{
    return coordX_;
}

void Pixel::setCoordX(int value)
{
    coordX_ = value;
}

int Pixel::getCoordY() const
{
    return coordY_;
}

void Pixel::setCoordY(int value)
{
    coordY_ = value;
}

char Pixel::getY() const
{
    return Y_;
}

void Pixel::setY(char value)
{
    Y_ = value;
}

char Pixel::getU() const
{
    return U_;
}

void Pixel::setU(char value)
{
    U_ = value;
}

char Pixel::getV() const
{
    return V_;
}

void Pixel::setV(char value)
{
    V_ = value;
}

size_t Pixel::getChromaCoord() const
{
    return chromaCoord_;
}

void Pixel::setChromaCoord(const size_t &value)
{
    chromaCoord_ = value;
}

size_t Pixel::getLumaCoord() const
{
    return lumaCoord_;
}

void Pixel::setLumaCoord(const size_t &value)
{
    lumaCoord_ = value;
}

Pixel operator-(const Pixel& p1, const Pixel& p2)
{
    Pixel newPixel(p1);

    newPixel.Y_ -= p2.getY();

    if (newPixel.Y_ < 0)
        newPixel.Y_ = 0;

    //    newPixel.U -= pixel.getU();
    //    newPixel.U = newPixel.U < 0 ? 0 : newPixel.U;

    //    newPixel.V -= pixel.getV();
    //    newPixel.V = newPixel.V < 0 ? 0 : newPixel.V;

    return newPixel;
}
