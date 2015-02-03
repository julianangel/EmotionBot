#ifndef _ROS_theatre_bot_TriskarSmallUpper_h
#define _ROS_theatre_bot_TriskarSmallUpper_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatre_bot
{

  class TriskarSmallUpper : public ros::Msg
  {
    public:
      float left;
      bool left_change;
      float center;
      bool center_change;
      float right;
      bool right_change;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_left;
      u_left.real = this->left;
      *(outbuffer + offset + 0) = (u_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left);
      union {
        bool real;
        uint8_t base;
      } u_left_change;
      u_left_change.real = this->left_change;
      *(outbuffer + offset + 0) = (u_left_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_change);
      union {
        float real;
        uint32_t base;
      } u_center;
      u_center.real = this->center;
      *(outbuffer + offset + 0) = (u_center.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_center.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_center.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_center.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->center);
      union {
        bool real;
        uint8_t base;
      } u_center_change;
      u_center_change.real = this->center_change;
      *(outbuffer + offset + 0) = (u_center_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->center_change);
      union {
        float real;
        uint32_t base;
      } u_right;
      u_right.real = this->right;
      *(outbuffer + offset + 0) = (u_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right);
      union {
        bool real;
        uint8_t base;
      } u_right_change;
      u_right_change.real = this->right_change;
      *(outbuffer + offset + 0) = (u_right_change.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_change);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_left;
      u_left.base = 0;
      u_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->left = u_left.real;
      offset += sizeof(this->left);
      union {
        bool real;
        uint8_t base;
      } u_left_change;
      u_left_change.base = 0;
      u_left_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left_change = u_left_change.real;
      offset += sizeof(this->left_change);
      union {
        float real;
        uint32_t base;
      } u_center;
      u_center.base = 0;
      u_center.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_center.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_center.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_center.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->center = u_center.real;
      offset += sizeof(this->center);
      union {
        bool real;
        uint8_t base;
      } u_center_change;
      u_center_change.base = 0;
      u_center_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->center_change = u_center_change.real;
      offset += sizeof(this->center_change);
      union {
        float real;
        uint32_t base;
      } u_right;
      u_right.base = 0;
      u_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->right = u_right.real;
      offset += sizeof(this->right);
      union {
        bool real;
        uint8_t base;
      } u_right_change;
      u_right_change.base = 0;
      u_right_change.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right_change = u_right_change.real;
      offset += sizeof(this->right_change);
     return offset;
    }

    const char * getType(){ return "theatre_bot/TriskarSmallUpper"; };
    const char * getMD5(){ return "1ec3ca261e395eab39b284d5a1f9b8f0"; };

  };

}
#endif