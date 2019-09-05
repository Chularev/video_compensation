#include "filewriter.h"

using namespace std;

FileWriter::FileWriter(const std::string &fullPath, int frameWidth, int frameHeight)
 : filePath_(fullPath), frameWidth_(frameWidth), frameHeight_(frameHeight)
{

}

//FileWriter::~FileWriter()
//{
//    file_.close();

//}

bool FileWriter::open()
{

    file_.open(filePath_, ios::binary | ios::out);
    return false;

}

void FileWriter::writeFrame(const Frame &frame)
{
    int64_t frameSize = frameWidth_ * frameHeight_;
//    file_.seekg(frameSize * frame.index() );

    file_.write(frame.data().data(),frameSize);
}
