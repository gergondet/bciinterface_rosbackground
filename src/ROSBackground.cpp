#include <bciinterface_rosbackground/ROSBackground.h>

#include <bci-interface/Background/BufferBG.h>

#include <SFML/Graphics.hpp>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <boost/thread.hpp>
#include <string>

namespace bciinterface
{

struct ROSBackgroundImpl
{
    ROSBackgroundImpl(const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0)
    : nh(), it(nh), bg(0), wwidth(wwidth), wheight(wheight), iwidth(iwidth), iheight(iheight), close(false)
    {
        sub = it.subscribe(videonode, 1, &ROSBackgroundImpl::imageCallback, this);
    }

    ROSBackgroundImpl(ros::NodeHandle & nh, const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0)
    : nh(nh), it(nh), bg(0), wwidth(wwidth), wheight(wheight), iwidth(iwidth), iheight(iheight), close(false)
    {
        sub = it.subscribe(videonode, 1, &ROSBackgroundImpl::imageCallback, this);
    }

    ~ROSBackgroundImpl()
    {
        delete bg;
    }

    void imageCallback(const sensor_msgs::ImageConstPtr & img)
    {
        if(!bg)
        {
            bg = new BufferBG(img->width, img->height, wwidth, wheight, iwidth, iheight);
        }
        bg->UpdateFromBuffer_BGR8(const_cast<unsigned char *>(&(img->data[0])));
    }

    void SetSubRect(int left, int top, int width, int height)
    {
        if(bg)
        {
            bg->SetSubRect(left,top, width, height);
        }
    }

    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Subscriber sub;

    BufferBG * bg;
    unsigned char * buffer;
    unsigned int wwidth;
    unsigned int wheight;
    unsigned iwidth;
    unsigned iheight;
    bool close;
};

ROSBackground::ROSBackground(const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
{
    int argc = 0;
    char * argv[] = {};
    ros::init(argc, argv, "bci_interface_rosbg");
    m_impl = new ROSBackgroundImpl(videonode, wwidth, wheight, iwidth, iheight);
}

ROSBackground::ROSBackground(ros::NodeHandle & nh, const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
{
    m_impl = new ROSBackgroundImpl(nh, videonode, wwidth, wheight, iwidth, iheight);
}

ROSBackground::~ROSBackground()
{
    delete m_impl;
}

void ROSBackground::UpdateLoop()
{
    ros::Rate r(100);
    while(!m_impl->close && ros::ok())
    {
        ros::spinOnce();
        r.sleep();
    }
}

void ROSBackground::Close()
{
    m_impl->close = true;
}

void ROSBackground::Draw(sf::RenderTarget * app)
{
    if(m_impl->bg)
    {
        m_impl->bg->Draw(app);
    }
}

void ROSBackground::SetSubRect(int left, int top, int width, int height)
{
    m_impl->SetSubRect(left, top, width, height);
}

} //namespace bciinterface

