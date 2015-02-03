#ifndef _ROS_theatre_bot_KeeponMessage_h
#define _ROS_theatre_bot_KeeponMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Float64.h"

namespace theatre_bot
{

  class KeeponMessage : public ros::Msg
  {
    public:
      std_msgs::Float64 tilt;
      bool tilt_change;
      std_msgs::Float64 pan;
      bool pan_change;
      std_msgs::Float64 side;
      bool side_change;
      std_msgs::Float64 pon;
      bool pon_change;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->tilt.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_tilt_change;
      u_tilt_change.real = this->tilt_change;
      *(outbuffer + offset + 0) = (u_tilt_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->tilt_change);
      offset += this->pan.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_pan_change;
      u_pan_change.real = this->pan_change;
      *(outbuffer + offset + 0) = (u_pan_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pan_change);
      offset += this->side.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_side_change;
      u_side_change.real = this->side_change;
      *(outbuffer + offset + 0) = (u_side_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->side_change);
      offset += this->pon.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_pon_change;
      u_pon_change.real = this->pon_change;
      *(outbuffer + offset + 0) = (u_pon_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pon_change);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->tilt.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_tilt_change;
      u_tilt_change.base = 0;
      u_tilt_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->tilt_change = u_tilt_change.real;
      offset += sizeof(this->tilt_change);
      offset += this->pan.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_pan_change;
      u_pan_change.base = 0;
      u_pan_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pan_change = u_pan_change.real;
      offset += sizeof(this->pan_change);
      offset += this->side.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_side_change;
      u_side_change.base = 0;
      u_side_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->side_change = u_side_change.real;
      offset += sizeof(this->side_change);
      offset += this->pon.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_pon_change;
      u_pon_change.base = 0;
      u_pon_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pon_change = u_pon_change.real;
      offset += sizeof(this->pon_change);
     return offset;
    }

    const char * getType(){ return "theatre_bot/KeeponMessage"; };
    const char * getMD5(){ return "3aa66b3dd9617d201cba2ad75a3177e4"; };

  };

}
#endif