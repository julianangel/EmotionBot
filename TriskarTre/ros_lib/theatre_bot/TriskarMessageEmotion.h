#ifndef _ROS_theatre_bot_TriskarMessageEmotion_h
#define _ROS_theatre_bot_TriskarMessageEmotion_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatre_bot
{

  class TriskarMessageEmotion : public ros::Msg
  {
    public:
      int32_t coming_to;
      bool synch;
      bool stop;
      bool repeat;
      uint8_t distance_length;
      float st_distance;
      float * distance;
      uint8_t velocity_length;
      float st_velocity;
      float * velocity;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_coming_to;
      u_coming_to.real = this->coming_to;
      *(outbuffer + offset + 0) = (u_coming_to.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_coming_to.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_coming_to.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_coming_to.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->coming_to);
      union {
        bool real;
        uint8_t base;
      } u_synch;
      u_synch.real = this->synch;
      *(outbuffer + offset + 0) = (u_synch.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->synch);
      union {
        bool real;
        uint8_t base;
      } u_stop;
      u_stop.real = this->stop;
      *(outbuffer + offset + 0) = (u_stop.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stop);
      union {
        bool real;
        uint8_t base;
      } u_repeat;
      u_repeat.real = this->repeat;
      *(outbuffer + offset + 0) = (u_repeat.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->repeat);
      *(outbuffer + offset++) = distance_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < distance_length; i++){
      union {
        float real;
        uint32_t base;
      } u_distancei;
      u_distancei.real = this->distance[i];
      *(outbuffer + offset + 0) = (u_distancei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distancei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distancei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distancei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance[i]);
      }
      *(outbuffer + offset++) = velocity_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < velocity_length; i++){
      union {
        float real;
        uint32_t base;
      } u_velocityi;
      u_velocityi.real = this->velocity[i];
      *(outbuffer + offset + 0) = (u_velocityi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocityi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocityi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocityi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_coming_to;
      u_coming_to.base = 0;
      u_coming_to.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_coming_to.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_coming_to.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_coming_to.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->coming_to = u_coming_to.real;
      offset += sizeof(this->coming_to);
      union {
        bool real;
        uint8_t base;
      } u_synch;
      u_synch.base = 0;
      u_synch.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->synch = u_synch.real;
      offset += sizeof(this->synch);
      union {
        bool real;
        uint8_t base;
      } u_stop;
      u_stop.base = 0;
      u_stop.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stop = u_stop.real;
      offset += sizeof(this->stop);
      union {
        bool real;
        uint8_t base;
      } u_repeat;
      u_repeat.base = 0;
      u_repeat.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->repeat = u_repeat.real;
      offset += sizeof(this->repeat);
      uint8_t distance_lengthT = *(inbuffer + offset++);
      if(distance_lengthT > distance_length)
        this->distance = (float*)realloc(this->distance, distance_lengthT * sizeof(float));
      offset += 3;
      distance_length = distance_lengthT;
      for( uint8_t i = 0; i < distance_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_distance;
      u_st_distance.base = 0;
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_distance = u_st_distance.real;
      offset += sizeof(this->st_distance);
        memcpy( &(this->distance[i]), &(this->st_distance), sizeof(float));
      }
      uint8_t velocity_lengthT = *(inbuffer + offset++);
      if(velocity_lengthT > velocity_length)
        this->velocity = (float*)realloc(this->velocity, velocity_lengthT * sizeof(float));
      offset += 3;
      velocity_length = velocity_lengthT;
      for( uint8_t i = 0; i < velocity_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_velocity;
      u_st_velocity.base = 0;
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_velocity = u_st_velocity.real;
      offset += sizeof(this->st_velocity);
        memcpy( &(this->velocity[i]), &(this->st_velocity), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "theatre_bot/TriskarMessageEmotion"; };
    const char * getMD5(){ return "e81dcc9131b1cee6d7b9c7514f5310a3"; };

  };

}
#endif