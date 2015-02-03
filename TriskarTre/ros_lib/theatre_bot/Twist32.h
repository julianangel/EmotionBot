#ifndef _ROS_theatre_bot_Twist32_h
#define _ROS_theatre_bot_Twist32_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatre_bot/Vector32.h"

namespace theatre_bot
{

  class Twist32 : public ros::Msg
  {
    public:
      theatre_bot::Vector32 linear;
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

    const char * getType(){ return "theatre_bot/Twist32"; };
    const char * getMD5(){ return "1457dfc2d60e835c52793e31724f1e83"; };

  };

}
#endif