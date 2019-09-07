#ifndef FRAME_H
#define FRAME_H

#include<vector>

class Frame
{
public:
    Frame(const std::vector<char> &dataY, const std::vector<char> &dataU, const std::vector<char> &dataV, int index);
    int index() const;

    std::vector<char> dataY() const;

    std::vector<char> dataV() const;

    std::vector<char> dataU() const;

private:
    std::vector<char> dataY_;
    std::vector<char> dataU_;
    std::vector<char> dataV_;
    int index_;
};

#endif // FRAME_H
