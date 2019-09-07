#ifndef PIXEL_H
#define PIXEL_H

#include <string>

class Pixel
{
public:
    Pixel();
    Pixel(const Pixel &pixel);

    int getCoordX() const;
    void setCoordX(int value);

    int getCoordY() const;
    void setCoordY(int value);

    char getY() const;
    void setY(char value);

    char getU() const;
    void setU(char value);

    char getV() const;
    void setV(char value);

    size_t getChromaCoord() const;
    void setChromaCoord(const size_t &value);

    size_t getLumaCoord() const;
    void setLumaCoord(const size_t &value);

    Pixel operator-(const Pixel& pixel) const;

private:
    size_t lumaCoord;
    size_t chromaCoord;

    int xCoord;
    int yCoord;
    char Y;
    char U;
    char V;
};

#endif // PIXEL_H
