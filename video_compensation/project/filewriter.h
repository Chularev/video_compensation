#ifndef FILEWRITER_H
#define FILEWRITER_H


#include "frame.h"

#include <string>
#include <fstream>

class FileWriter
{
public:
    explicit FileWriter(const std::string &fullPath);
    virtual ~FileWriter();

    void writeFrame(const Frame &frame);
private:
    void open();
    void close();

    std::string filePath_;
    std::ofstream file_;
};

#endif // FILEWRITER_H
