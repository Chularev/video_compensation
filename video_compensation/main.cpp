#include <filereader.h>
#include <filewriter.h>
#include <frameinfo.h>

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
    }
    catch (exception &exp) {
        cerr << string(exp.what());
        return 1;
    }
    return 0;
}
