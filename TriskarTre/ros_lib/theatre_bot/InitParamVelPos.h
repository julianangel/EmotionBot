#ifndef _ROS_theatre_bot_InitParamVelPos_h
#define _ROS_theatre_bot_InitParamVelPos_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatre_bot
{

  class InitParamVelPos : public ros::Msg
  {
    public:
      float initial_x;
      float initial_y;
      float initial_theta;
      float linear_velocity;
      float angular_velocity;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_initial_x;
      u_initial_x.real = this->initial_x;
      *(outbuffer + offset + 0) = (u_initial_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_initial_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_initial_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_initial_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->initial_x);
      union {
        float real;
        uint32_t base;
      } u_initial_y;
      u_initial_y.real = this->initial_y;
      *(outbuffer + offset + 0) = (u_initial_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_initial_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_initial_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_initial_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->initial_y);
      union {
        float real;
        uint32_t base;
      } u_initial_theta;
      u_initial_theta.real = this->initial_theta;
      *(outbuffer + offset + 0) = (u_initial_theta.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_initial_theta.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_initial_theta.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_initial_theta.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->initial_theta);
      union {
        float real;
        uint32_t base;
      } u_linear_velocity;
      u_linear_velocity.real = this->linear_velocity;
      *(outbuffer + offset + 0) = (u_linear_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_linear_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_linear_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_linear_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->linear_velocity);
      union {
        float real;
        uint32_t base;
      } u_angular_velocity;
      u_angular_velocity.real = this->angular_velocity;
      *(outbuffer + offset + 0) = (u_angular_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angular_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angular_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angular_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angular_velocity);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_initial_x;
      u_initial_x.base = 0;
      u_initial_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_initial_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_initial_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_initial_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->initial_x = u_initial_x.real;
      offset += sizeof(this->initial_x);
      union {
        float real;
        uint32_t base;
      } u_initial_y;
      u_initial_y.base = 0;
      u_initial_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_initial_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_initial_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_initial_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->initial_y = u_initial_y.real;
      offset += sizeof(this->initial_y);
      union {
        float real;
        uint32_t base;
      } u_initial_theta;
      u_initial_theta.base = 0;
      u_initial_theta.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_initial_theta.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_initial_theta.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_initial_theta.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->initial_theta = u_initial_theta.real;
      offset += sizeof(this->initial_theta);
      union {
        float real;
        uint32_t base;
      } u_linear_velocity;
      u_linear_velocity.base = 0;
      u_linear_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_linear_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_linear_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_linear_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->linear_velocity = u_linear_velocity.real;
      offset += sizeof(this->linear_velocity);
      union {
        float real;
        uint32_t base;
      } u_angular_velocity;
      u_angular_velocity.base = 0;
      u_angular_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angular_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angular_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angular_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angular_velocity = u_angular_velocity.real;
      offset += sizeof(this->angular_velocity);
     return offset;
    }

    const char * getType(){ return "theatre_bot/InitParamVelPos"; };
    const char * getMD5(){ return "fb804603faafc178dcc4db6063a2b673"; };

  };

}
#endif