#ifndef FILEREADER_H
#define FILEREADER_H

#include "frame.h"

#include <string>
#include <fstream>


class FileReader
{
public:
    explicit FileReader(const std::string &fullPath);
    virtual ~FileReader();

    bool eof() const;
    Frame readeNext();
private:
    void open();
    void close();

    std::string filePath_;
    std::ifstream file_;
    int index_;
};

#endif // FILEREADER_H
