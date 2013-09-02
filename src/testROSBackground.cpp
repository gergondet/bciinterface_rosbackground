#include "ROSBackground.h"

#include <bci-interface/BCIInterface.h>
#include <bci-interface/DisplayObject/SSVEPStimulus.h>
#include <bci-interface/CommandReceiver/UDPReceiver.h>
#include <bci-interface/CommandInterpreter/SimpleInterpreter.h>
#include <bci-interface/CommandOverrider.h>

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
//    UDPReceiver * receiver = new UDPReceiver(1111);
//    SimpleInterpreter * interpreter = new SimpleInterpreter();
//    bciinterface->SetCommandReceiver(receiver);
//    bciinterface->SetCommandInterpreter(interpreter);

//    CommandOverrider overrider;
//    overrider.AddOverrideCommand(sf::Keyboard::Up, 1);
//    overrider.AddOverrideCommand(sf::Keyboard::Right, 2);
//    overrider.AddOverrideCommand(sf::Keyboard::Down, 3);
//    overrider.AddOverrideCommand(sf::Keyboard::Left, 4);
//    bciinterface->SetCommandOverrider(&overrider);

//    ROSBackground * bg = new ROSBackground("vscore/image", width, height, iwidth, iheight); 
    ROSBackground * bg = new ROSBackground("camera/rgb/image_color", width, height, iwidth, iheight); 
    bciinterface->SetBackground(bg);

    std::string dir = dirname(argv[0]);
    dir += "/";
    bciinterface->AddObject(new SSVEPStimulus(6, 60, width/2, 100, 200,200, dir + "UP.png", dir + "UP_HL.png"));
    bciinterface->AddObject(new SSVEPStimulus(8, 60, width-100, height/2, 200, 200, dir + "RIGHT.png", dir + "RIGHT_HL.png"));
    bciinterface->AddObject(new SSVEPStimulus(10, 60, width/2, height-100, 200, 200, dir + "DOWN.png", dir + "DOWN_HL.png"));
    bciinterface->AddObject(new SSVEPStimulus(9, 60, 100, height/2,200, 200, dir + "LEFT.png", dir + "LEFT_HL.png"));
    bciinterface->AddObject(new SSVEPStimulus(14, 60, 100, height/2,200, 200, "LEFT.png", "LEFT_HL.png"));

    bciinterface->DisplayLoop(fullscreen);

    delete bciinterface;
//    delete interpreter;
//    delete receiver;
    delete bg;
    

    return 0;
}
