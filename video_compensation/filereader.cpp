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
    file_.close();
}

bool FileReader::open()
{
    file_.open(filePath_, ios::binary | ios::in);
    if (!file_.is_open() || !file_.good())
      return false;
    return true;
}

Frame FileReader::readeFrame(int index)
{
    int64_t frameSize = FrameInfo::getBytesPerFrame();

    unsigned long long int bufferSize = static_cast<unsigned long long int>(frameSize);
    std::vector<char> buffer(bufferSize);

    file_.seekg(frameSize * index);
    file_.read(&buffer[0], frameSize);

    Frame frame(buffer, index);
    return frame;
}


