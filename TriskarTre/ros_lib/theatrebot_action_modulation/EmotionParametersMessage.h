#ifndef _ROS_theatrebot_action_modulation_EmotionParametersMessage_h
#define _ROS_theatrebot_action_modulation_EmotionParametersMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace theatrebot_action_modulation
{

  class EmotionParametersMessage : public ros::Msg
  {
    public:
      float timing;
      float spacing;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->timing);
      offset += serializeAvrFloat64(outbuffer + offset, this->spacing);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->timing));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->spacing));
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/EmotionParametersMessage"; };
    const char * getMD5(){ return "50751bc9be5daf002fb22c5c8cc59029"; };

  };

}
#endif