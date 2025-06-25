#include "filewriter.h"

#include <frameinfo.h>
#include <cstring>

using namespace std;

FileWriter::FileWriter(const std::string &fullPath)
 : filePath_(fullPath)
{

}

FileWriter::~FileWriter()
{
    if (file_.is_open())
      file_.close();
}

void FileWriter::open()
{

    file_.open(filePath_, ios::binary | ios::out);
    if (!file_.is_open() || !file_.good())
        throw ios_base::failure("Failed open file \"" + filePath_ +
                                "\" : '" + strerror(errno) + "'");
}

void FileWriter::close()
{
    if (file_.is_open())
        file_.close();
}

void FileWriter::writeFrame(const Frame &frame)
{ 
    int64_t lumaSise = static_cast<int64_t>(FrameInfo::getLumaSise());
    file_.write(frame.dataY().data(), lumaSise);

    int64_t chromaSise = static_cast<int64_t>(FrameInfo::getChromaSise());
    file_.write(frame.dataU().data(), chromaSise);
    file_.write(frame.dataV().data(), chromaSise);
}
