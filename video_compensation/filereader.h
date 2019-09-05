#ifndef FILEREADER_H
#define FILEREADER_H

#include "frame.h"

#include <string>
#include <fstream>


class FileReader
{
public:
    FileReader(const std::string &fullPath, int frameWidth, int frameHeight);
    bool open();
    Frame readeFrame(int index);
private:
    std::string filePath_;
    std::ifstream infile_;

    int frameWidth_;
    int frameHeight_;
};

#endif // FILEREADER_H
