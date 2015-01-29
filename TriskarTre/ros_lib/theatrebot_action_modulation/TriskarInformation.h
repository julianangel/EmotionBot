#ifndef _ROS_theatrebot_action_modulation_TriskarInformation_h
#define _ROS_theatrebot_action_modulation_TriskarInformation_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Range.h"
#include "theatrebot_action_modulation/OdometryTriskar.h"

namespace theatrebot_action_modulation
{

  class TriskarInformation : public ros::Msg
  {
    public:
      sensor_msgs::Range laser;
      theatrebot_action_modulation::OdometryTriskar odometry;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->laser.serialize(outbuffer + offset);
      offset += this->odometry.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->laser.deserialize(inbuffer + offset);
      offset += this->odometry.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/TriskarInformation"; };
    const char * getMD5(){ return "a93b0bb82a6a8f811f67348c5dc8cdd2"; };

  };

}
#endif