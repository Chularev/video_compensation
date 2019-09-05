#include "filereader.h"

#include <vector>

using namespace std;

FileReader::FileReader(const std::string &fullPath, int frameWidth, int frameHeight)
    : filePath_(fullPath), frameWidth_(frameWidth), frameHeight_(frameHeight)
{

}

bool FileReader::open()
{
    infile_.open(filePath_, ios::binary | ios::in);
    return false;
}

Frame FileReader::readeFrame(int index)
{
    int64_t frameSize = frameWidth_ * frameHeight_;

    uint64_t buffSize = static_cast<uint64_t>(frameSize);
    std::vector<char> buffer(buffSize);

    infile_.seekg(frameSize * index);
    infile_.read(&buffer[0], frameSize);

    Frame frame(buffer);
    return frame;
}
