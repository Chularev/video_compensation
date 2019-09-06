#include <filereader.h>
#include <filewriter.h>
#include <frameinfo.h>

#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    std::string path("D://Qt_Projekts//video_compensation//");
    //std::string path("/home/alex/video_compensation/");
    //640x360


    int width = 640;
    int height = 360;
    FrameInfo::init(width,height);

    std::string inFileName = path + "tmpRamshta.yuv";
    FileReader reader(inFileName);
    if (!reader.open())
    {
        const char * errorStr = strerror(errno);
        cerr << "Failed to open file \""+ inFileName +"\": '" + string(errorStr) + "'";
        return 1;
    }


    FileWriter writer(path + "progResult.yuv",width,height + bytesPerFrame);
    writer.open();

    for (int i = 0; i < 1; i++) {
       Frame frame = reader.readeFrame(i);
       writer.writeFrame(frame);
    }


    return 0;
}
