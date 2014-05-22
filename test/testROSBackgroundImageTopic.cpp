#include <bciinterface_rosbackground/ROSBackground.h>

#include <bci-interface/BCIInterface.h>
#include <bci-interface/DisplayObject/SSVEPStimulus.h>
#include <bci-interface/CommandReceiver/UDPReceiver.h>
#include <bci-interface/CommandInterpreter/SimpleInterpreter.h>
#include <bci-interface/CommandOverrider.h>
#include <bci-interface/EventHandler.h>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

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

struct TestCameraSwitch : public bciinterface::EventHandler
{
    TestCameraSwitch(bciinterface::ROSBackground & bg) : bg(bg), current_video_node("camera/rgb/image_raw")
    {
    }

    virtual void Process(sf::Event & event)
    {
        if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space )
        {
            if(current_video_node == "camera/rgb/image_raw")
            {
                current_video_node = "vscore/image";
            }
            else
            {
                current_video_node = "camera/rgb/image_raw";
            }
            bg.SetCameraTopic(current_video_node);
        }
    }

    bciinterface::ROSBackground & bg;
    std::string current_video_node;
};

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

    BCIInterface * bciinterface = new BCIInterface(width, height);
    ROSBackground * bg = new ROSBackground("camera/rgb/image_raw", width, height, iwidth, iheight);
    TestCameraSwitch tcs(*bg);
    bciinterface->SetBackground(bg);
    bciinterface->AddEventHandler(&tcs);

    bciinterface->DisplayLoop(fullscreen);

    delete bciinterface;
    delete bg;


    return 0;
}
