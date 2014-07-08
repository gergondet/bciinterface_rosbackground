#include "ROSBackgroundImpl.h"

using namespace bciinterface;

ROSBackgroundImpl::ROSBackgroundImpl::ROSBackgroundImpl(unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
: nh(), bg(0), width(0), height(0), wwidth(wwidth), wheight(wheight), iwidth(iwidth), iheight(iheight), close(false)
{
}

ROSBackgroundImpl::ROSBackgroundImpl(ros::NodeHandle & nh, unsigned int wwidth, unsigned int wheight, unsigned int iwidth, unsigned int iheight)
: nh(nh), bg(0), width(0), height(0), wwidth(wwidth), wheight(wheight), iwidth(iwidth), iheight(iheight), close(false)
{
}

ROSBackgroundImpl::~ROSBackgroundImpl()
{
  delete bg;
}

bool ROSBackgroundImpl::init()
{
  if(bg)
  {
      return true;
  }
  if(width != 0 && height != 0)
  {
      bg = new bciinterface::BufferBG(width, height, wwidth, wheight, iwidth, iheight);
      return true;
  }
  return false;
}

void ROSBackgroundImpl::SetSubRect(int left, int top, int width, int height)
{
    if(bg)
    {
        bg->SetSubRect(left,top, width, height);
    }
}

void ROSBackgroundImpl::SetCameraTopic(const std::string & videonode)
{
}

void ROSBackgroundImpl::UpdateLoop()
{
  ros::Rate r(100);
  while(!close && ros::ok())
  {
    ros::spinOnce();
    r.sleep();
  }
}
