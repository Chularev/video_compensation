#include "frame.h"

Frame::Frame(const std::vector<char> &data, int index)
    : data_(data), index_(index)
{

}

int Frame::index() const
{
    return index_;
}

std::vector<char> Frame::data() const
{
    return data_;
}
