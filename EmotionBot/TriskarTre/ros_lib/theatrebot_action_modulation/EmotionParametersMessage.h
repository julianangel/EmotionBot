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
      int32_t * val_timing = (int32_t *) &(this->timing);
      int32_t exp_timing = (((*val_timing)>>23)&255);
      if(exp_timing != 0)
        exp_timing += 1023-127;
      int32_t sig_timing = *val_timing;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_timing<<5) & 0xff;
      *(outbuffer + offset++) = (sig_timing>>3) & 0xff;
      *(outbuffer + offset++) = (sig_timing>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_timing<<4) & 0xF0) | ((sig_timing>>19)&0x0F);
      *(outbuffer + offset++) = (exp_timing>>4) & 0x7F;
      if(this->timing < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_spacing = (int32_t *) &(this->spacing);
      int32_t exp_spacing = (((*val_spacing)>>23)&255);
      if(exp_spacing != 0)
        exp_spacing += 1023-127;
      int32_t sig_spacing = *val_spacing;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_spacing<<5) & 0xff;
      *(outbuffer + offset++) = (sig_spacing>>3) & 0xff;
      *(outbuffer + offset++) = (sig_spacing>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_spacing<<4) & 0xF0) | ((sig_spacing>>19)&0x0F);
      *(outbuffer + offset++) = (exp_spacing>>4) & 0x7F;
      if(this->spacing < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t * val_timing = (uint32_t*) &(this->timing);
      offset += 3;
      *val_timing = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_timing |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_timing |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_timing |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_timing = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_timing |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_timing !=0)
        *val_timing |= ((exp_timing)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->timing = -this->timing;
      uint32_t * val_spacing = (uint32_t*) &(this->spacing);
      offset += 3;
      *val_spacing = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_spacing |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_spacing |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_spacing |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_spacing = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_spacing |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_spacing !=0)
        *val_spacing |= ((exp_spacing)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->spacing = -this->spacing;
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/EmotionParametersMessage"; };
    const char * getMD5(){ return "50751bc9be5daf002fb22c5c8cc59029"; };

  };

}
#endif