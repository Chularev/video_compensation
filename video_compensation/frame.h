#ifndef FRAME_H
#define FRAME_H

#include<vector>

class Frame
{
public:
    Frame(const std::vector<char> &data, int index);
    int index() const;

    std::vector<char> data() const;

private:
    std::vector<char> data_;
    int index_;
};

#endif // FRAME_H
