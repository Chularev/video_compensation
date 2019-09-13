#include "filereader.h"
#include "filewriter.h"
#include "frameinfo.h"
#include "videocompensation.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // -pathInput D://Qt_Projekts//video_compensation//tmpRamshta.yuv
    //-w 640 -h 360
    //-pathOutput D://Qt_Projekts//video_compensation//progResult.yuv


    std::string path("D://Qt_Projekts//video_compensation//");
    //std::string path("/home/alex/video_compensation/");
    //640x360


    try
    {
        if (argc != 9)
            throw std::invalid_argument("Invalid argument count."
                                        " It must be -pathInput, -w, -h, -pathOutput");

        std::map<std::string, std::string> params;

        for (int count = 1; count < argc; count += 2)
            params[argv[count]] = argv[count + 1];

        if (params.find("-w") == params.end())
            throw std::invalid_argument("Param -w (frame width) is not existing");


        if (params.find("-h") == params.end())
            throw std::invalid_argument("Param -h (frame height) is not existing");


        int width  = std::stoi(params["-w"]);
        int height = std::stoi(params["-h"]);
        FrameInfo::init(width, height);

        if (params.find("-pathInput") == params.end())
            throw std::invalid_argument("Param -pathInput is not existing");

        FileReader reader(params["-pathInput"]);
        reader.open();


        if (params.find("-pathOutput") == params.end())
            throw std::invalid_argument("Param -pathOutput is not existing");

        FileWriter writer(params["-pathOutput"]);
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
    catch (exception &exp)
    {
        cerr << string(exp.what());
        return 1;
    }
    catch(...)
    {
        cerr << "Unknown exception";
        return 1;
    }

    return 0;
}
