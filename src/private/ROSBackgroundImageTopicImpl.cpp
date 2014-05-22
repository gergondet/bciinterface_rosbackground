#include "ROSBackgroundImageTopicImpl.h"

ROSBackgroundImageTopicImpl::ROSBackgroundImageTopicImpl(
  const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
: ROSBackgroundImpl(wwidth, wheight, iwidth, iheight), it(nh)
{
  sub = it.subscribe(videonode, 1, &ROSBackgroundImageTopicImpl::imageCallback, this);
}

ROSBackgroundImageTopicImpl::ROSBackgroundImageTopicImpl(
  ros::NodeHandle & nh, const std::string & videonode, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
: ROSBackgroundImpl(nh, wwidth, wheight, iwidth, iheight), it(nh)
{
  sub = it.subscribe(videonode, 1, &ROSBackgroundImageTopicImpl::imageCallback, this);
}

void ROSBackgroundImageTopicImpl::imageCallback(const sensor_msgs::ImageConstPtr & img)
{
  if(!bg)
  {
    width = img->width; height = img->height;
  }
  else
  {
    if(img->encoding == "bgr8")
    {
      bg->UpdateFromBuffer_BGR8(const_cast<unsigned char *>(&(img->data[0])));
    }
    else
    {
      bg->UpdateFromBuffer_RGB8(const_cast<unsigned char *>(&(img->data[0])));
    }
  }
}

void ROSBackgroundImageTopicImpl::SetCameraTopic(const std::string & videonode)
{
  sub.shutdown();
  sub = it.subscribe(videonode, 1, &ROSBackgroundImageTopicImpl::imageCallback, this);
}
