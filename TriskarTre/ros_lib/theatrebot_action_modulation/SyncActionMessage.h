#ifndef _ROS_theatrebot_action_modulation_SyncActionMessage_h
#define _ROS_theatrebot_action_modulation_SyncActionMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

namespace theatrebot_action_modulation
{

  class SyncActionMessage : public ros::Msg
  {
    public:
      std_msgs::String action_name;
      std_msgs::String type_message;
      std_msgs::Bool action_success;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_name.serialize(outbuffer + offset);
      offset += this->type_message.serialize(outbuffer + offset);
      offset += this->action_success.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_name.deserialize(inbuffer + offset);
      offset += this->type_message.deserialize(inbuffer + offset);
      offset += this->action_success.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/SyncActionMessage"; };
    const char * getMD5(){ return "d9dee8f4b51788439bc5e5de9bad73a9"; };

  };

}
#endif