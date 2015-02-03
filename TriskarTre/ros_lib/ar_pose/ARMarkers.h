#ifndef _ROS_ar_pose_ARMarkers_h
#define _ROS_ar_pose_ARMarkers_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "ar_pose/ARMarker.h"

namespace ar_pose
{

  class ARMarkers : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t markers_length;
      ar_pose::ARMarker st_markers;
      ar_pose::ARMarker * markers;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = markers_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < markers_length; i++){
      offset += this->markers[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t markers_lengthT = *(inbuffer + offset++);
      if(markers_lengthT > markers_length)
        this->markers = (ar_pose::ARMarker*)realloc(this->markers, markers_lengthT * sizeof(ar_pose::ARMarker));
      offset += 3;
      markers_length = markers_lengthT;
      for( uint8_t i = 0; i < markers_length; i++){
      offset += this->st_markers.deserialize(inbuffer + offset);
        memcpy( &(this->markers[i]), &(this->st_markers), sizeof(ar_pose::ARMarker));
      }
     return offset;
    }

    const char * getType(){ return "ar_pose/ARMarkers"; };
    const char * getMD5(){ return "b35e1e178a9cd7039dbb63cf2764131a"; };

  };

}
#endif