#ifndef _ROS_theatrebot_action_modulation_Pose32_h
#define _ROS_theatrebot_action_modulation_Pose32_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point32.h"

namespace theatrebot_action_modulation
{

  class Pose32 : public ros::Msg
  {
    public:
      geometry_msgs::Point32 position;
      float orientation;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->position.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_orientation;
      u_orientation.real = this->orientation;
      *(outbuffer + offset + 0) = (u_orientation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_orientation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_orientation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_orientation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->orientation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->position.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_orientation;
      u_orientation.base = 0;
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->orientation = u_orientation.real;
      offset += sizeof(this->orientation);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/Pose32"; };
    const char * getMD5(){ return "a04191cdcdead104ba8498d948186454"; };

  };

}
#endif