#ifndef FILEWRITER_H
#define FILEWRITER_H


#include "frame.h"

#include <string>
#include <fstream>

class FileWriter
{
public:
    FileWriter(const std::string &fullPath, int frameWidth, int frameHeight);
    //virtual ~FileWriter();

    bool open();
    void writeFrame(const Frame &frame);
private:
    std::string filePath_;
    std::ofstream file_;

    int frameWidth_;
    int frameHeight_;
};

#endif // FILEWRITER_H
