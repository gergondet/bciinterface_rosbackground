#include <bciinterface_rosbackground/ROSBackground.h>

#include <bci-interface/BCIInterface.h>
#include <bci-interface/EventHandler.h>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

#include <ros_h264_streamer/h264_streamer.h>

#ifdef WIN32
#include <Windows.h>
void sleep(DWORD t)
{
    Sleep(1000*t);
}
#include <stdint.h>

std::string dirname(char * path)
{
    return ".";
}

#else
#include <inttypes.h>
#include <libgen.h>
#endif

using namespace bciinterface;

int main(int argc, char * argv[])
{
    bool fullscreen = false;
    if(argc > 1)
    {
        std::stringstream ss;
        ss << argv[1];
        ss >> fullscreen;
    }
    unsigned int width = 1680;
    unsigned int height = 1050;
    unsigned int iwidth = 1024;
    unsigned int iheight = 768;
    if(!fullscreen)
    {
        width = 640;
        height = 480;
        iwidth = 640;
        iheight = 480;
    }

    ros::init(argc, argv, "testROSBackgroundNetwork");
    ros::NodeHandle nh;

    ros_h264_streamer::H264Streamer::Config streamerconfig;
    streamerconfig.udp = false; streamerconfig.server = true;
    ros_h264_streamer::H264Streamer streamer(streamerconfig, nh);

    ros_h264_streamer::H264Receiver::Config receiverconfig;
    receiverconfig.udp = false; receiverconfig.server = false;
    receiverconfig.width = 640; receiverconfig.height = 480;
    receiverconfig.publish = false;

    BCIInterface * bciinterface = new BCIInterface(width, height);
    ROSBackground * bg = new ROSBackground(nh, receiverconfig, width, height, iwidth, iheight);
    bciinterface->SetBackground(bg);

    bciinterface->DisplayLoop(fullscreen);

    delete bciinterface;

    ros::shutdown();

    return 0;
}
