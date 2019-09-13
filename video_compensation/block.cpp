#include "block.h"

#include <stdexcept>

using namespace std;

int Block::side_ = 8;

Block::Block(int topLeftX, int topLeftY)
    : topLeftX_(topLeftX),topLeftY_(topLeftY)
{
    size_t size = static_cast<size_t>(side_);
    matrix_ = vector<vector<Pixel>>(size, vector<Pixel>(size, Pixel()));
}

Block::Block(const Block &block)
{
    topLeftX_ = block.topLeftX();
    topLeftY_ = block.topLeftY();
    side_ = block.side();
    matrix_ = block.matrix_;
}

Block &Block::operator=(const Block &block)
{
    topLeftX_ = block.topLeftX();
    topLeftY_ = block.topLeftY();
    side_ = block.side();
    matrix_ = block.matrix_;
    return *this;
}

int Block::side()
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

Pixel Block::operator()(int row, int col) const
{

    if (row < 0 || row >= side_)
        throw out_of_range("row more or less the block width");

    if (col < 0 || col >= side_)
        throw out_of_range("col more or less the block height");

    return matrix_[static_cast<size_t>(row)][static_cast<size_t>(col)];
}

Block operator-(const Block &block1, const Block &block2)
{
    Block result(block1.topLeftX(),block1.topLeftY());
    for (int i = 0; i < result.side(); i++)
        for (int j = 0; j < result.side(); j++)
            result(i,j) = block1(i,j) - block2(i,j);

    return result;
}
