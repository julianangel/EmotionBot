/*
 * SimpleActionSpeakNode.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: julian
 */
#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "ros/ros.h"
#include "../instances/platform_profiles/PlatformTest1.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"

using std::string;
using std::vector;


void executeAction(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);
//TODO implement file parameters
void loadParameters(string file);
//TODO implement the platform information from file and change the platform description
void loadPlatformAction(string file);

string desire_platform = "triskar_small";
//TODO this should be change to a more advance description to control difference in the platforms
map <string,string> simple_actions;

int main(int argc, char **argv){
	// Set up ROS.
	PlatformTest1 *platform_description = new PlatformTest1;
	//TODO the information load it here should be help to know the constrains of the platform
	simple_actions = platform_description->getPlatformAction(desire_platform);
	ros::init(argc, argv, "simple_action_speak_node");
	ros::NodeHandle n("/action_modulation");
	//Load  information
	if(n.getParam("/action_modulation/platform",desire_platform)){
		simple_actions = platform_description->getPlatformAction(desire_platform);
	}
	ros::Subscriber sub = n.subscribe("simple_action_speak_node", 1000, executeAction);
	ROS_INFO("Ready to execute speak action");
	while(ros::ok()){

		ros::spinOnce();
	}

	return 0;
}

void executeAction(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg)
{
	ROS_INFO("Execute action speak");
}

//TODO implement file parameters
void loadParameters(string file){

}
//TODO implement the platform information from file and change the platform description
void loadPlatformAction(string file){

}
