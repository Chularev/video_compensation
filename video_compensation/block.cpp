#include "block.h"

#include <stdexcept>

using namespace std;

Block::Block(int topLeftX, int topLeftY)
    : topLeftX_(topLeftX),topLeftY_(topLeftY), side_(8)
{
    size_t size = static_cast<size_t>(side_);
    matrix_ = vector<vector<Pixel>>(size, vector<Pixel>(size, Pixel()));
}

int Block::side() const
{
    return side_;
}

int Block::topLeftX() const
{
    return topLeftX_;
}

int Block::topLeftY() const
{
    return topLeftY_;
}

Pixel &Block::operator()(int row, int col)
{
    if (row < 0 || row >= side_)
        throw out_of_range("row more or less the block width");

    if (col < 0 || col >= side_)
        throw out_of_range("col more or less the block height");

    return matrix_[static_cast<size_t>(row)][static_cast<size_t>(col)];
}

const Pixel &Block::operator()(int row, int col) const
{

    if (row < 0 || row >= side_)
        throw out_of_range("row more or less the block width");

    if (col < 0 || col >= side_)
        throw out_of_range("col more or less the block height");

    return matrix_[static_cast<size_t>(row)][static_cast<size_t>(col)];
}
