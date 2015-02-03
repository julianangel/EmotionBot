#ifndef _ROS_theatrebot_action_modulation_EmotionModulationMessage_h
#define _ROS_theatrebot_action_modulation_EmotionModulationMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"

namespace theatrebot_action_modulation
{

  class EmotionModulationMessage : public ros::Msg
  {
    public:
      std_msgs::String emotion;
      float intensity;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->emotion.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->intensity);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->emotion.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->intensity));
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/EmotionModulationMessage"; };
    const char * getMD5(){ return "49d9347b2f62d46def7b41f7e9bf49a1"; };

  };

}
#endif