#ifndef PIXEL_H
#define PIXEL_H

#include <string>

class Pixel
{
public:
    Pixel();
    Pixel(const Pixel &pixel);
    Pixel& operator=(const Pixel &pixel);

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

    friend Pixel operator-(const Pixel& p1, const Pixel& p2);

private:
    size_t lumaCoord_;
    size_t chromaCoord_;

    int coordX_;
    int coordY_;
    char Y_;
    char U_;
    char V_;
};

#endif // PIXEL_H
