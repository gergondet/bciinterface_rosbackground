#ifndef _H_ROSBACKGROUNDH264RECEIVERIMPL_H_
#define _H_ROSBACKGROUNDH264RECEIVERIMPL_H_

#include "ROSBackgroundImpl.h"
#include <ros_h264_streamer/h264_receiver.h>

struct ROSBackgroundH264ReceiverImpl : public bciinterface::ROSBackgroundImpl
{
  ROSBackgroundH264ReceiverImpl(ros_h264_streamer::H264Receiver::Config & conf,
    unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

  ROSBackgroundH264ReceiverImpl(ros::NodeHandle & nh, ros_h264_streamer::H264Receiver::Config & conf,
    unsigned int wwidth, unsigned int wheight, unsigned int iwidth = 0, unsigned int iheight = 0);

  virtual void UpdateLoop();

  ros_h264_streamer::H264Receiver receiver;
  sensor_msgs::ImagePtr img;
};

#endif
