#include "ROSBackgroundH264ReceiverImpl.h"

ROSBackgroundH264ReceiverImpl::ROSBackgroundH264ReceiverImpl(ros_h264_streamer::H264Receiver::Config & conf,
    unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
: ROSBackgroundImpl(wwidth, wheight, iwidth, iheight), receiver(conf, nh), img(new sensor_msgs::Image)
{
}

ROSBackgroundH264ReceiverImpl::ROSBackgroundH264ReceiverImpl(ros::NodeHandle & nh, ros_h264_streamer::H264Receiver::Config & conf,
    unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
: ROSBackgroundImpl(nh, wwidth, wheight, iwidth, iheight), receiver(conf, nh), img(new sensor_msgs::Image)
{
}

void ROSBackgroundH264ReceiverImpl::UpdateLoop()
{
  ros::Rate r(100);
  while(!close && ros::ok())
  {
    ros::spinOnce();
    if(receiver.getLatestImage(img))
    {
      if(img->width != 0 && img->height != 0)
      {
        width = img->width; height = img->height;
      }
      if(init())
      {
        bg->UpdateFromBuffer_BGR8(const_cast<unsigned char *>(&(img->data[0])));
      }
    }
    r.sleep();
  }
}
