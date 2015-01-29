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
      int32_t * val_intensity = (int32_t *) &(this->intensity);
      int32_t exp_intensity = (((*val_intensity)>>23)&255);
      if(exp_intensity != 0)
        exp_intensity += 1023-127;
      int32_t sig_intensity = *val_intensity;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_intensity<<5) & 0xff;
      *(outbuffer + offset++) = (sig_intensity>>3) & 0xff;
      *(outbuffer + offset++) = (sig_intensity>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_intensity<<4) & 0xF0) | ((sig_intensity>>19)&0x0F);
      *(outbuffer + offset++) = (exp_intensity>>4) & 0x7F;
      if(this->intensity < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->emotion.deserialize(inbuffer + offset);
      uint32_t * val_intensity = (uint32_t*) &(this->intensity);
      offset += 3;
      *val_intensity = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_intensity |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_intensity |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_intensity |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_intensity = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_intensity |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_intensity !=0)
        *val_intensity |= ((exp_intensity)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->intensity = -this->intensity;
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/EmotionModulationMessage"; };
    const char * getMD5(){ return "49d9347b2f62d46def7b41f7e9bf49a1"; };

  };

}
#endif