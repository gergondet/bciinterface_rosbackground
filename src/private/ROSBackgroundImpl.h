#ifndef _H_ROSBACKGROUNDIMPL_H_
#define _H_ROSBACKGROUNDIMPL_H_

#include <bci-interface/Background/BufferBG.h>
#include <SFML/Graphics.hpp>

#include <ros/ros.h>
#include <boost/thread.hpp>
#include <string>

namespace bciinterface
{

struct ROSBackgroundImpl
{
    ROSBackgroundImpl(unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

    ROSBackgroundImpl(ros::NodeHandle & nh,
      unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

    ~ROSBackgroundImpl();

    bool init();

    void SetSubRect(int left, int top, int width, int height);

    virtual void SetCameraTopic(const std::string & videonode);

    virtual void UpdateLoop();

    ros::NodeHandle nh;

    bciinterface::BufferBG * bg;
    unsigned char * buffer;
    unsigned int width;
    unsigned int height;
    unsigned int wwidth;
    unsigned int wheight;
    unsigned iwidth;
    unsigned iheight;
    bool close;
};

}
#endif
