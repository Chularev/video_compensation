#include "filewriter.h"

#include <frameinfo.h>

using namespace std;

FileWriter::FileWriter(const std::string &fullPath)
 : filePath_(fullPath)
{

}

FileWriter::~FileWriter()
{
    file_.close();

}

bool FileWriter::open()
{

    file_.open(filePath_, ios::binary | ios::out);
    if (!file_.is_open() || !file_.good())
      return false;
    return true;
}

void FileWriter::close()
{
    if (file_.is_open())
        file_.close();
}

void FileWriter::writeFrame(const Frame &frame)
{ 
    file_.write(frame.dataY().data(), FrameInfo::getLumaSise());
    file_.write(frame.dataU().data(), FrameInfo::getChromaSise());
    file_.write(frame.dataV().data(), FrameInfo::getChromaSise());
}
