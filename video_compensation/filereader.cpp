#include "filereader.h"

#include <frameinfo.h>

#include <vector>

using namespace std;

FileReader::FileReader(const std::string &fullPath)
    : filePath_(fullPath)
{

}

FileReader::~FileReader()
{
    if (file_.is_open())
      file_.close();
}

bool FileReader::open()
{
    file_.open(filePath_, ios::binary | ios::in);
    if (!file_.is_open() || !file_.good())
      return false;
    return true;
}

void FileReader::close()
{
    if (file_.is_open())
      file_.close();
}

Frame FileReader::readeFrame(int index)
{
    int64_t frameSize = FrameInfo::getBytesPerFrame();
    file_.seekg(frameSize * index);

    unsigned long long int lumaSize = static_cast<unsigned long long int>(FrameInfo::getLumaSise());
    std::vector<char> bufferY(lumaSize);
    file_.read(&bufferY[0], FrameInfo::getLumaSise());

    unsigned long long int chromaSize = static_cast<unsigned long long int>(FrameInfo::getChromaSise());
    std::vector<char> bufferU(chromaSize);
    file_.read(&bufferU[0], FrameInfo::getChromaSise());

    std::vector<char> bufferV(chromaSize);
    file_.read(&bufferV[0], FrameInfo::getChromaSise());

    return Frame(bufferY, bufferU, bufferV, index);
}


