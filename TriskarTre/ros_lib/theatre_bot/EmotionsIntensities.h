#ifndef _ROS_theatre_bot_EmotionsIntensities_h
#define _ROS_theatre_bot_EmotionsIntensities_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatre_bot
{

  class EmotionsIntensities : public ros::Msg
  {
    public:
      float fear;
      float surprise;
      float interest;
      float relief;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_fear;
      u_fear.real = this->fear;
      *(outbuffer + offset + 0) = (u_fear.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fear.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fear.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fear.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->fear);
      union {
        float real;
        uint32_t base;
      } u_surprise;
      u_surprise.real = this->surprise;
      *(outbuffer + offset + 0) = (u_surprise.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_surprise.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_surprise.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_surprise.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->surprise);
      union {
        float real;
        uint32_t base;
      } u_interest;
      u_interest.real = this->interest;
      *(outbuffer + offset + 0) = (u_interest.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_interest.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_interest.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_interest.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->interest);
      union {
        float real;
        uint32_t base;
      } u_relief;
      u_relief.real = this->relief;
      *(outbuffer + offset + 0) = (u_relief.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_relief.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_relief.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_relief.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->relief);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_fear;
      u_fear.base = 0;
      u_fear.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fear.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fear.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fear.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->fear = u_fear.real;
      offset += sizeof(this->fear);
      union {
        float real;
        uint32_t base;
      } u_surprise;
      u_surprise.base = 0;
      u_surprise.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_surprise.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_surprise.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_surprise.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->surprise = u_surprise.real;
      offset += sizeof(this->surprise);
      union {
        float real;
        uint32_t base;
      } u_interest;
      u_interest.base = 0;
      u_interest.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_interest.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_interest.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_interest.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->interest = u_interest.real;
      offset += sizeof(this->interest);
      union {
        float real;
        uint32_t base;
      } u_relief;
      u_relief.base = 0;
      u_relief.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_relief.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_relief.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_relief.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->relief = u_relief.real;
      offset += sizeof(this->relief);
     return offset;
    }

    const char * getType(){ return "theatre_bot/EmotionsIntensities"; };
    const char * getMD5(){ return "5739ef3c19be6604b5aeb5e39bf7ea97"; };

  };

}
#endif