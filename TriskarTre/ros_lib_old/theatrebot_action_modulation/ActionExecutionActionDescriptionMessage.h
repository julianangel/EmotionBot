#ifndef _ROS_theatrebot_action_modulation_ActionExecutionActionDescriptionMessage_h
#define _ROS_theatrebot_action_modulation_ActionExecutionActionDescriptionMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "theatrebot_action_modulation/PositionParameterMessage.h"
#include "theatrebot_action_modulation/TrajectoryParameterMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"

namespace theatrebot_action_modulation
{

  class ActionExecutionActionDescriptionMessage : public ros::Msg
  {
    public:
      std_msgs::String action_name;
      std_msgs::String phrase_to_say;
      std_msgs::String action_type;
      std_msgs::Bool action_is_principal;
      theatrebot_action_modulation::PositionParameterMessage desire_position;
      theatrebot_action_modulation::TrajectoryParameterMessage trajectory_characteristic;
      uint8_t emotion_parameters_length;
      theatrebot_action_modulation::EmotionParametersMessage st_emotion_parameters;
      theatrebot_action_modulation::EmotionParametersMessage * emotion_parameters;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_name.serialize(outbuffer + offset);
      offset += this->phrase_to_say.serialize(outbuffer + offset);
      offset += this->action_type.serialize(outbuffer + offset);
      offset += this->action_is_principal.serialize(outbuffer + offset);
      offset += this->desire_position.serialize(outbuffer + offset);
      offset += this->trajectory_characteristic.serialize(outbuffer + offset);
      *(outbuffer + offset++) = emotion_parameters_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < emotion_parameters_length; i++){
      offset += this->emotion_parameters[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_name.deserialize(inbuffer + offset);
      offset += this->phrase_to_say.deserialize(inbuffer + offset);
      offset += this->action_type.deserialize(inbuffer + offset);
      offset += this->action_is_principal.deserialize(inbuffer + offset);
      offset += this->desire_position.deserialize(inbuffer + offset);
      offset += this->trajectory_characteristic.deserialize(inbuffer + offset);
      uint8_t emotion_parameters_lengthT = *(inbuffer + offset++);
      if(emotion_parameters_lengthT > emotion_parameters_length)
        this->emotion_parameters = (theatrebot_action_modulation::EmotionParametersMessage*)realloc(this->emotion_parameters, emotion_parameters_lengthT * sizeof(theatrebot_action_modulation::EmotionParametersMessage));
      offset += 3;
      emotion_parameters_length = emotion_parameters_lengthT;
      for( uint8_t i = 0; i < emotion_parameters_length; i++){
      offset += this->st_emotion_parameters.deserialize(inbuffer + offset);
        memcpy( &(this->emotion_parameters[i]), &(this->st_emotion_parameters), sizeof(theatrebot_action_modulation::EmotionParametersMessage));
      }
     return offset;
    }

    const char * getType(){ return "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage"; };
    const char * getMD5(){ return "dd5f0f855c3f5584493aa7a5fabed7cd"; };

  };

}
#endif