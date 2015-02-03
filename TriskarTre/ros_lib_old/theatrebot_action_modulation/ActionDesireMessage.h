#ifndef _ROS_theatrebot_action_modulation_ActionDesireMessage_h
#define _ROS_theatrebot_action_modulation_ActionDesireMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "theatrebot_action_modulation/PositionParameterMessage.h"
#include "theatrebot_action_modulation/TrajectoryParameterMessage.h"

namespace theatrebot_action_modulation
{

  class ActionDesireMessage : public ros::Msg
  {
    public:
      std_msgs::String action_name;
      std_msgs::String phrase_to_say;
      theatrebot_action_modulation::PositionParameterMessage desire_position;
      theatrebot_action_modulation::TrajectoryParameterMessage trajectory_characteristic;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_name.serialize(outbuffer + offset);
      offset += this->phrase_to_say.serialize(outbuffer + offset);
      offset += this->desire_position.serialize(outbuffer + offset);
      offset += this->trajectory_characteristic.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_name.deserialize(inbuffer + offset);
      offset += this->phrase_to_say.deserialize(inbuffer + offset);
      offset += this->desire_position.deserialize(inbuffer + offset);
      offset += this->trajectory_characteristic.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/ActionDesireMessage"; };
    const char * getMD5(){ return "12c7da38f4a0d08d798726ec6ce9497c"; };

  };

}
#endif