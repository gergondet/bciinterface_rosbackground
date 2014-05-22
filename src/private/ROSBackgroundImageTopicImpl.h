#ifndef _H_ROSBACKGROUNDIMAGETOPICIMPL_H_
#define _H_ROSBACKGROUNDIMAGETOPICIMPL_H_

#include "ROSBackgroundImpl.h"
#include <image_transport/image_transport.h>

struct ROSBackgroundImageTopicImpl : public bciinterface::ROSBackgroundImpl
{
  ROSBackgroundImageTopicImpl(const std::string & videonode,
    unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

  ROSBackgroundImageTopicImpl(ros::NodeHandle & nh, const std::string & videonode,
    unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

  void imageCallback(const sensor_msgs::ImageConstPtr & img);

  void SetCameraTopic(const std::string & vn);

  image_transport::ImageTransport it;
  image_transport::Subscriber sub;
};

#endif
