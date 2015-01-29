#ifndef _ROS_theatrebot_action_modulation_ActionExecutionMessage_h
#define _ROS_theatrebot_action_modulation_ActionExecutionMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"

namespace theatrebot_action_modulation
{

  class ActionExecutionMessage : public ros::Msg
  {
    public:
      uint8_t actions_message_length;
      theatrebot_action_modulation::ActionExecutionActionDescriptionMessage st_actions_message;
      theatrebot_action_modulation::ActionExecutionActionDescriptionMessage * actions_message;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = actions_message_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < actions_message_length; i++){
      offset += this->actions_message[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t actions_message_lengthT = *(inbuffer + offset++);
      if(actions_message_lengthT > actions_message_length)
        this->actions_message = (theatrebot_action_modulation::ActionExecutionActionDescriptionMessage*)realloc(this->actions_message, actions_message_lengthT * sizeof(theatrebot_action_modulation::ActionExecutionActionDescriptionMessage));
      offset += 3;
      actions_message_length = actions_message_lengthT;
      for( uint8_t i = 0; i < actions_message_length; i++){
      offset += this->st_actions_message.deserialize(inbuffer + offset);
        memcpy( &(this->actions_message[i]), &(this->st_actions_message), sizeof(theatrebot_action_modulation::ActionExecutionActionDescriptionMessage));
      }
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/ActionExecutionMessage"; };
    const char * getMD5(){ return "b777816394966f9996af376533a8b0f5"; };

  };

}
#endif