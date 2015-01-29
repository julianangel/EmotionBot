#ifndef _ROS_theatrebot_action_modulation_TriskarLinearVelocity_h
#define _ROS_theatrebot_action_modulation_TriskarLinearVelocity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatrebot_action_modulation/Vector32.h"

namespace theatrebot_action_modulation
{

  class TriskarLinearVelocity : public ros::Msg
  {
    public:
      theatrebot_action_modulation::Vector32 linear;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->linear.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->linear.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/TriskarLinearVelocity"; };
    const char * getMD5(){ return "1fe92384436e21e4f9a2fd5847225eca"; };

  };

}
#endif