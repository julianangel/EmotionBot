#ifndef _ROS_theatrebot_action_modulation_OdometryTriskar_h
#define _ROS_theatrebot_action_modulation_OdometryTriskar_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatrebot_action_modulation/Pose32.h"
#include "theatrebot_action_modulation/Twist32.h"

namespace theatrebot_action_modulation
{

  class OdometryTriskar : public ros::Msg
  {
    public:
      theatrebot_action_modulation::Pose32 pose;
      theatrebot_action_modulation::Twist32 twist;

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

    const char * getType(){ return "theatrebot_action_modulation/OdometryTriskar"; };
    const char * getMD5(){ return "21a227286d7c9f29cf8e9786a33a9a9a"; };

  };

}
#endif