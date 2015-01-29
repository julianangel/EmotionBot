#ifndef _ROS_theatrebot_action_modulation_PositionParameterMessage_h
#define _ROS_theatrebot_action_modulation_PositionParameterMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"

namespace theatrebot_action_modulation
{

  class PositionParameterMessage : public ros::Msg
  {
    public:
      std_msgs::String type_parameter;
      geometry_msgs::Pose desire_position;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->type_parameter.serialize(outbuffer + offset);
      offset += this->desire_position.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->type_parameter.deserialize(inbuffer + offset);
      offset += this->desire_position.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/PositionParameterMessage"; };
    const char * getMD5(){ return "203c7f131c9c8003b539784c1fddac1b"; };

  };

}
#endif