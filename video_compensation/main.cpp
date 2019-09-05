#include <iostream>

using namespace std;

#include <filereader.h>
#include <filewriter.h>


int main()
{
    cout << "Hello World!" << endl;

    //std::string path("D://Qt_Projekts//video_compensation//");
    std::string path("/home/alex/video_compensation/");
    //640x360

    // bytes += (frameSize.width() / 2) * frameSize.height() * bytesPerSample * 2; // U/V planes, half the width

    int width = 640;
    int height = 360;
    int bytesPerFrame = (width / 2) * height * 2; // U/V planes, half the width


    FileReader reader(path + "tmpRamshta.yuv",width,height + bytesPerFrame);
    reader.open();
    FileWriter writer(path + "progResult.yuv",width,height + bytesPerFrame);
    writer.open();
    for (int i = 0; i < 1; i++) {
       Frame frame = reader.readeFrame(i);
       writer.writeFrame(frame);
    }

    std::ifstream infile (path + "progResult.yuv",std::ifstream::binary);

      // get size of file
      infile.seekg (0,infile.end);
      double size = infile.tellg();
      infile.seekg (0);
      std::cout << "Frame size = " << 640*360 << endl;
      std::cout << "Frame count = " << size /(640*360) << endl;
    return 0;
}
