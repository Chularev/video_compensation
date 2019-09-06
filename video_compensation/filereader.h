#ifndef FILEREADER_H
#define FILEREADER_H

#include "frame.h"

#include <string>
#include <fstream>


class FileReader
{
public:
    FileReader(const std::string &fullPath);
    virtual ~FileReader();

    bool open();
    Frame readeFrame(int index);
private:
    std::string filePath_;
    std::ifstream file_;
};

#endif // FILEREADER_H
