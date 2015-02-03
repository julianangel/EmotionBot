#ifndef _ROS_theatre_bot_ActionExecutionMessage_h
#define _ROS_theatre_bot_ActionExecutionMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatre_bot
{

  class ActionExecutionMessage : public ros::Msg
  {
    public:
      const char* coming_from;
      const char* coming_to;
      const char* message;
      bool stop_action;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_coming_from = strlen(this->coming_from);
      memcpy(outbuffer + offset, &length_coming_from, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->coming_from, length_coming_from);
      offset += length_coming_from;
      uint32_t length_coming_to = strlen(this->coming_to);
      memcpy(outbuffer + offset, &length_coming_to, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->coming_to, length_coming_to);
      offset += length_coming_to;
      uint32_t length_message = strlen(this->message);
      memcpy(outbuffer + offset, &length_message, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      union {
        bool real;
        uint8_t base;
      } u_stop_action;
      u_stop_action.real = this->stop_action;
      *(outbuffer + offset + 0) = (u_stop_action.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stop_action);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_coming_from;
      memcpy(&length_coming_from, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_coming_from; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_coming_from-1]=0;
      this->coming_from = (char *)(inbuffer + offset-1);
      offset += length_coming_from;
      uint32_t length_coming_to;
      memcpy(&length_coming_to, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_coming_to; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_coming_to-1]=0;
      this->coming_to = (char *)(inbuffer + offset-1);
      offset += length_coming_to;
      uint32_t length_message;
      memcpy(&length_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      union {
        bool real;
        uint8_t base;
      } u_stop_action;
      u_stop_action.base = 0;
      u_stop_action.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stop_action = u_stop_action.real;
      offset += sizeof(this->stop_action);
     return offset;
    }

    const char * getType(){ return "theatre_bot/ActionExecutionMessage"; };
    const char * getMD5(){ return "33462ea7a5d8687d7eaa6c5c66d45d41"; };

  };

}
#endif