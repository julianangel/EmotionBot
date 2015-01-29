#ifndef _ROS_theatrebot_action_modulation_TriskarVelocity_h
#define _ROS_theatrebot_action_modulation_TriskarVelocity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatrebot_action_modulation/Vector32.h"

namespace theatrebot_action_modulation
{

  class TriskarVelocity : public ros::Msg
  {
    public:
      theatrebot_action_modulation::Vector32 linear;
      float angular;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->linear.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_angular;
      u_angular.real = this->angular;
      *(outbuffer + offset + 0) = (u_angular.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angular.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angular.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angular.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angular);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->linear.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_angular;
      u_angular.base = 0;
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angular = u_angular.real;
      offset += sizeof(this->angular);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/TriskarVelocity"; };
    const char * getMD5(){ return "1457dfc2d60e835c52793e31724f1e83"; };

  };

}
#endif