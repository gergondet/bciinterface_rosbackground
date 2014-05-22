#include <bciinterface_rosbackground/ROSBackground.h>

#include "private/ROSBackgroundImageTopicImpl.h"
#include "private/ROSBackgroundH264ReceiverImpl.h"

namespace bciinterface
{

ROSBackground::ROSBackground(const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
{
  int argc = 0;
  char * argv[] = {};
  ros::init(argc, argv, "bci_interface_rosbg");
  m_impl = new ROSBackgroundImageTopicImpl(videonode, wwidth, wheight, iwidth, iheight);
}

ROSBackground::ROSBackground(ros::NodeHandle & nh, const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
{
  m_impl = new ROSBackgroundImageTopicImpl(nh, videonode, wwidth, wheight, iwidth, iheight);
}

ROSBackground::ROSBackground(ros_h264_streamer::H264Receiver::Config & conf, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
{
  m_impl = new ROSBackgroundH264ReceiverImpl(conf, wwidth, wheight, iwidth, iheight);
}

ROSBackground::ROSBackground(ros::NodeHandle & nh, ros_h264_streamer::H264Receiver::Config & conf, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
{
  m_impl = new ROSBackgroundH264ReceiverImpl(nh, conf, wwidth, wheight, iwidth, iheight);
}

ROSBackground::~ROSBackground()
{
  delete m_impl;
}

void ROSBackground::UpdateLoop()
{
  m_impl->UpdateLoop();
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
  else
  {
    if(m_impl->init())
    {
      m_impl->bg->Draw(app);
    }
  }
}

void ROSBackground::SetSubRect(int left, int top, int width, int height)
{
  m_impl->SetSubRect(left, top, width, height);
}

void ROSBackground::SetCameraTopic(const std::string & camera_topic)
{
  m_impl->SetCameraTopic(camera_topic);
}

} //namespace bciinterface

