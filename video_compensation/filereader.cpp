#include "filereader.h"

#include <vector>

using namespace std;

FileReader::FileReader(const std::string &fullPath, int frameWidth, int frameHeight)
    : filePath_(fullPath), frameWidth_(frameWidth), frameHeight_(frameHeight)
{

}

FileReader::~FileReader()
{
    file_.close();
}

bool FileReader::open()
{
    file_.open(filePath_, ios::binary | ios::in);
    return false;
}

Frame FileReader::readeFrame(int index)
{
    int64_t frameSize = frameWidth_ * frameHeight_;

    uint64_t buffSize = static_cast<uint64_t>(frameSize);
    std::vector<char> buffer(buffSize);

    file_.seekg(frameSize * index);
    file_.read(&buffer[0], frameSize);

    Frame frame(buffer, frameWidth_, frameHeight_, index);
    return frame;
}


