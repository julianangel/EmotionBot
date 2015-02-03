#ifndef _ROS_theatre_bot_OdometryTriskar_h
#define _ROS_theatre_bot_OdometryTriskar_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatre_bot/Pose32.h"
#include "theatre_bot/Twist32.h"

namespace theatre_bot
{

  class OdometryTriskar : public ros::Msg
  {
    public:
      theatre_bot::Pose32 pose;
      theatre_bot::Twist32 twist;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->twist.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->twist.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatre_bot/OdometryTriskar"; };
    const char * getMD5(){ return "21a227286d7c9f29cf8e9786a33a9a9a"; };

  };

}
#endif