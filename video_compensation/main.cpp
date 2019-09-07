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


    std::string outFileName = path + "progResult.yuv";
    FileWriter writer(outFileName);
    if (!writer.open())
    {
        const char * errorStr = strerror(errno);
        cerr << "Failed to open file \""+ outFileName +"\": '" + string(errorStr) + "'";
        return 1;
    }

    for (int count = 0; count < 1000; count++) {

        Frame frame = reader.readeFrame(count);
        Frame result = reader.readeFrame(count + 1);
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j ++) {
              result.setPixel(result.getPixel(i,j) - frame.getPixel(i,j));
            }
        }
        writer.writeFrame(result);
    }

    reader.close();
    writer.close();

    cout << "All done" << endl;
    return 0;
}
