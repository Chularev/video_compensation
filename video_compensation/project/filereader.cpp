#include "filereader.h"

#include <frameinfo.h>

#include <vector>
#include <cstring>

using namespace std;

FileReader::FileReader(const std::string &fullPath)
    : filePath_(fullPath), index_(0)
{
    open();
}

FileReader::~FileReader()
{
    if (file_.is_open())
      file_.close();
}

void FileReader::open()
{
    file_.open(filePath_, ios::binary | ios::in);
    if (!file_.is_open() || !file_.good())
        throw ios_base::failure("Fail open  file \"" + filePath_ +
                                "\" : '" + strerror(errno) + "'");
}

void FileReader::close()
{
    if (file_.is_open())
        file_.close();
}

bool FileReader::eof() const
{
    return file_.eof();
}


Frame FileReader::readeNext()
{
    std::vector<char> bufferY(FrameInfo::getLumaSise());
    int64_t lumaSize = static_cast<int64_t>(FrameInfo::getLumaSise());
    file_.read(&bufferY[0], lumaSize);

    std::vector<char> bufferU(FrameInfo::getChromaSise());
    int64_t chromaSize = static_cast<int64_t>(FrameInfo::getChromaSise());
    file_.read(&bufferU[0], chromaSize);

    std::vector<char> bufferV(FrameInfo::getChromaSise());
    file_.read(&bufferV[0], chromaSize);

    return Frame(bufferY, bufferU, bufferV, index_++);
}


