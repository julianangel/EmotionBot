#ifndef _ROS_SERVICE_ActionService_h
#define _ROS_SERVICE_ActionService_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatre_bot
{

static const char ACTIONSERVICE[] = "theatre_bot/ActionService";

  class ActionServiceRequest : public ros::Msg
  {
    public:
      const char* action;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_action = strlen(this->action);
      memcpy(outbuffer + offset, &length_action, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->action, length_action);
      offset += length_action;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_action;
      memcpy(&length_action, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_action; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_action-1]=0;
      this->action = (char *)(inbuffer + offset-1);
      offset += length_action;
     return offset;
    }

    const char * getType(){ return ACTIONSERVICE; };
    const char * getMD5(){ return "7757aad79fa343e61bc69ed7f1b7666d"; };

  };

  class ActionServiceResponse : public ros::Msg
  {
    public:
      const char* response;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_response = strlen(this->response);
      memcpy(outbuffer + offset, &length_response, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->response, length_response);
      offset += length_response;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_response;
      memcpy(&length_response, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_response; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_response-1]=0;
      this->response = (char *)(inbuffer + offset-1);
      offset += length_response;
     return offset;
    }

    const char * getType(){ return ACTIONSERVICE; };
    const char * getMD5(){ return "6de314e2dc76fbff2b6244a6ad70b68d"; };

  };

  class ActionService {
    public:
    typedef ActionServiceRequest Request;
    typedef ActionServiceResponse Response;
  };

}
#endif
