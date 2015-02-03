#ifndef _ROS_theatre_bot_EmotionMessage_h
#define _ROS_theatre_bot_EmotionMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"

namespace theatre_bot
{

  class EmotionMessage : public ros::Msg
  {
    public:
      std_msgs::String emotion;
      std_msgs::Float32 intensity;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->emotion.serialize(outbuffer + offset);
      offset += this->intensity.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->emotion.deserialize(inbuffer + offset);
      offset += this->intensity.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatre_bot/EmotionMessage"; };
    const char * getMD5(){ return "496cce3fca65818db623c45979399626"; };

  };

}
#endif