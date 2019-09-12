#include "filereader.h"
#include "filewriter.h"
#include "frameinfo.h"
#include "videocompensation.h"

#include <iostream>

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

    try
    {
        std::string inFileName = path + "tmpRamshta.yuv";
        FileReader reader(inFileName);
        reader.open();


        std::string outFileName = path + "progResult.yuv";
        FileWriter writer(outFileName);
        writer.open();


        VideoCompensation handler(1);
        for (int count = 0; count < 151; count++)
        {
            Frame previousFrame = reader.readeFrame(count);
            Frame currentFrame = reader.readeFrame(count + 1);
            MotionVectorsMap vectorMap = handler.findMotionVectors(currentFrame,previousFrame);
            Frame result = handler.doCompensation(currentFrame,previousFrame,vectorMap);
            writer.writeFrame(result);

            cout << "   Frame number = " << result.index();
        }

        reader.close();
        writer.close();

        cout << "All done" << endl;
    }
    catch (exception &exp) {
        cerr << string(exp.what());
        exit(1);
    }
    return 0;
}
