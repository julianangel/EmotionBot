#ifndef _ROS_theatrebot_action_modulation_TrajectoryParameterMessage_h
#define _ROS_theatrebot_action_modulation_TrajectoryParameterMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

namespace theatrebot_action_modulation
{

  class TrajectoryParameterMessage : public ros::Msg
  {
    public:
      std_msgs::String type_parameter;
      geometry_msgs::Twist trajectory_characteristic;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->type_parameter.serialize(outbuffer + offset);
      offset += this->trajectory_characteristic.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->type_parameter.deserialize(inbuffer + offset);
      offset += this->trajectory_characteristic.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/TrajectoryParameterMessage"; };
    const char * getMD5(){ return "b93adef537641cb9c7a82c09da52bd54"; };

  };

}
#endif