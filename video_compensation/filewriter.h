#ifndef FILEWRITER_H
#define FILEWRITER_H


#include "frame.h"

#include <string>
#include <fstream>

class FileWriter
{
public:
    FileWriter(const std::string &fullPath);
    virtual ~FileWriter();

    bool open();
    void close();
    void writeFrame(const Frame &frame);
private:
    std::string filePath_;
    std::ofstream file_;
};

#endif // FILEWRITER_H
