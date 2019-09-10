#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <pixel.h>

class Block
{
public:
    Block(int topLeftX, int topLeftY);
    static int side();

    int topLeftX() const;

    int topLeftY() const;

    Pixel& operator()(int row, int col);
    const Pixel& operator()(int row, int col) const;
private:
    int topLeftX_;
    int topLeftY_;
    static int side_;
    std::vector<std::vector<Pixel>> matrix_;
};

#endif // BLOCK_H
