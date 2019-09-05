#ifndef FRAME_H
#define FRAME_H

#include<vector>

class Frame
{
public:
    Frame(const std::vector<char> &data);
private:
    std::vector<char> data_;
};

#endif // FRAME_H
