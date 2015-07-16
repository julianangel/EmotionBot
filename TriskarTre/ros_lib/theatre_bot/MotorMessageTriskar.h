#ifndef _ROS_theatre_bot_MotorMessageTriskar_h
#define _ROS_theatre_bot_MotorMessageTriskar_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "theatre_bot/Vector32.h"

namespace theatre_bot
{

  class MotorMessageTriskar : public ros::Msg
  {
    public:
      theatre_bot::Vector32 set_motor;
      theatre_bot::Vector32 odometry_motor;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->set_motor.serialize(outbuffer + offset);
      offset += this->odometry_motor.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->set_motor.deserialize(inbuffer + offset);
      offset += this->odometry_motor.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatre_bot/MotorMessageTriskar"; };
    const char * getMD5(){ return "ffb213414c34383ff3d4d924f18d9d9a"; };

  };

}
#endif