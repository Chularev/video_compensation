#include "frame.h"

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
