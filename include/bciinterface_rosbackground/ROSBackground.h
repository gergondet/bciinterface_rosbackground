#include <bci-interface/Background.h>
#include <boost/shared_ptr.hpp>
#include <string>

#include <ros/ros.h>
#include <ros_h264_streamer/h264_receiver.h>

#ifndef _H_ROSBACKGROUND_H_
#define _H_ROSBACKGROUND_H_

namespace sf
{
    class RenderWindow;
}

namespace bciinterface
{

struct ROSBackgroundImpl;

class ROSBackground : public Background
{
public:
    ROSBackground(const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

    ROSBackground(ros::NodeHandle & nh, const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

    ROSBackground(ros_h264_streamer::H264Receiver::Config & conf, unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

    ROSBackground(ros::NodeHandle & nh, ros_h264_streamer::H264Receiver::Config & conf, unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

    virtual ~ROSBackground();

    /* Loop for background update will be launched in its own thread */
    virtual void UpdateLoop();

    /* Close the update loop properly */
    virtual void Close();

    /* Returns the current sprite of background */
    virtual void Draw(sf::RenderTarget * app);

    /* "Zoom" */
    void SetSubRect(int left, int top, int width, int height);

    /* Change/Set camera topic */
    void SetCameraTopic(const std::string & camera_topic);

    /* Overrider if you wish to implement Draw with OpenGL */
    virtual bool DrawWithGL() { return false; }
private:
    ROSBackgroundImpl * m_impl;
};

} // namespace bciinterface

#endif

