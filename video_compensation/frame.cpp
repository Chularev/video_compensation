#include "frame.h"

Frame::Frame(const std::vector<char> &data, int width, int height, int index)
    : data_(data), width_(width), height_(height), index_(index)
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
