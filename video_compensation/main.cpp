#include "filereader.h"
#include "filewriter.h"
#include "frameinfo.h"
#include "videocompensation.h"

#include <iostream>

using namespace std;

void testParams(const std::map<std::string, std::string> &params)
{
    if (params.find("-w") == params.end())
        throw std::invalid_argument("Param -w (frame width) is not existing");


    if (params.find("-h") == params.end())
        throw std::invalid_argument("Param -h (frame height) is not existing");

    if (params.find("-pathInput") == params.end())
        throw std::invalid_argument("Param -pathInput is not existing");

    if (params.find("-pathOutput") == params.end())
        throw std::invalid_argument("Param -pathOutput is not existing");

}

int main(int argc, char *argv[])
{
    // -pathInput D://Qt_Projekts//video_compensation//tmpRamshta.yuv
    //-w 640 -h 360
    //-pathOutput D://Qt_Projekts//video_compensation//progResult.yuv

    try
    {
        if (argc != 9)
            throw std::invalid_argument("Invalid argument count."
                                        " It must be -pathInput, -w, -h, -pathOutput");

        std::map<std::string, std::string> params;

        for (int count = 1; count < argc; count += 2)
            params[argv[count]] = argv[count + 1];

        testParams(params);

        int width  = std::stoi(params["-w"]);
        int height = std::stoi(params["-h"]);
        FrameInfo::init(width, height);

        FileReader reader(params["-pathInput"]);
        reader.open();


        FileWriter writer(params["-pathOutput"]);
        writer.open();


        VideoCompensation handler;

        Frame currentFrame(0);
        if (!reader.eof())
            currentFrame = reader.readeNext();

        while ( !reader.eof()) {
            Frame previousFrame = currentFrame;
            currentFrame = reader.readeNext();

            MotionVectorsMap vectorMap = handler.findMotionVectors(currentFrame,previousFrame);
            Frame result = handler.doCompensation(currentFrame,previousFrame,vectorMap);
            writer.writeFrame(result);
            //cout << "   Frame number = " << result.index();
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
