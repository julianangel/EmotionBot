cmake_minimum_required(VERSION 2.8.3)
project(theatrebot_action_modulation)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  sensor_msgs
  message_generation
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
###############################catkin_package(

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
  add_message_files(
    FILES
    EmotionModulationMessage.msg
    EmotionParametersMessage.msg
    PositionParameterMessage.msg
    TrajectoryParameterMessage.msg
    ActionDesireMessage.msg
    ActionExecutionActionDescriptionMessage.msg
    ActionExecutionMessage.msg
    OdometryTriskar.msg
    SyncActionMessage.msg
    Twist32.msg
    Vector32.msg
    Pose32.msg
    TriskarAngularVelocity.msg
    TriskarLinearVelocity.msg
    Quaternion32.msg
    TriskarInformation.msg
    TriskarVelocity.msg
  )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
    DEPENDENCIES
    std_msgs
    geometry_msgs
    sensor_msgs
  )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
# INCLUDE_DIRS include
#  LIBRARIES theatrebot_action_modulation
  CATKIN_DEPENDS message_runtime std_msgs roscpp rospy 
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_NAME}/src
)



## Declare a cpp library
# add_library(theatrebot_action_modulation
#   src/${PROJECT_NAME}/theatrebot_action_modulation.cpp
# )

## message("hola " ${catkin_INCLUDE_DIRS})
## Declare a cpp executable
# add_executable(theatrebot_action_modulation_node src/theatrebot_action_modulation_node.cpp)

 add_executable(action_modulation src/ActionModulation.cpp
src/json/jsoncpp.cpp
src/general_description/platform_description/PlatformDescription.cpp
src/general_description/action_description/SequenceAbstractActionDescription.cpp
src/general_description/action_description/SimpleActionDescription.cpp
src/general_description/action_description/instance_compound_action_description/WalkAndSpeakCompoundAction.cpp
src/general_description/action_description/instance_compound_action_description/WalkCompoundAction.cpp
src/general_description/action_description/AbstractActionDescription.cpp
src/general_description/action_description/instance_simple_action_description/OscillateBodyActionDescription.cpp
src/general_description/action_description/instance_simple_action_description/MoveShoulderSimpleActionDescription.cpp
src/general_description/action_description/instance_simple_action_description/OscillateShoulderDescription.cpp
src/general_description/action_description/instance_simple_action_description/SpeakSimpleAction.cpp
src/general_description/action_description/instance_simple_action_description/MoveBodySimpleActionDescription.cpp
src/general_description/action_description/instance_simple_action_description/NotDoAnythingSimpleAction.cpp
src/general_description/action_description/instance_simple_action_description/MoveTorsoSimpleAction.cpp
src/general_description/action_description/instance_simple_action_description/OscillateTorsoSimpleAction.cpp
src/general_description/parameters_description/Parameter.cpp
src/general_description/parameters_description/ParameterValue.cpp
src/general_description/parameters_description/ActionParameter.cpp
src/general_description/parameters_description/parameters_instances/LandmarkPositionParameter.cpp
src/general_description/parameters_description/parameters_instances/ParameterVelocity.cpp
src/general_description/parameters_description/parameters_instances/ParameterPosition.cpp
src/general_description/parameters_description/parameters_instances/ParameterTranslation.cpp
src/general_description/parameters_description/parameters_instances/ParameterTime.cpp
src/general_description/parameters_description/parameters_instances/PointPositionParameter.cpp
src/general_description/parameters_description/parameters_instances/AreaPositionParameter.cpp
src/general_description/parameters_description/parameters_instances/ParameterAcceleration.cpp
src/general_description/parameters_description/parameters_instances/EmotionParameter.cpp
src/general_description/emotion_description/EmotionProfile.cpp
src/general_description/emotion_description/ActionChanges.cpp
src/action_modulation/ActionAddition.cpp
src/action_modulation/ActionModification.cpp
src/general_execution/SimpleActionExecution.cpp
src/general_execution/SimpleActionTrajectoryExecution.cpp
src/general_execution/action_execution/MoveBodyExecution.cpp
src/general_execution/action_execution/MoveShoulderExecution.cpp
src/general_execution/action_execution/OscillateShoulderExecution.cpp
src/general_execution/action_execution/SpeakExecution.cpp
src/general_execution/action_execution/OscillateBodyExecution.cpp
src/general_execution/action_execution/NotDoAnythingExecution.cpp
src/general_execution/action_execution/MoveTorsoExecution.cpp
src/general_execution/action_execution/OscillateTorsoExecution.cpp
src/DecryptAction.cpp
src/instances/platform_profiles/PlatformTest1.cpp
src/instances/emotion_profiles/EmotionTest1.cpp
src/instances/actions/ActionTest1.cpp
 )
 
 add_executable(action_execution src/ActionGenerator.cpp
src/general_description/platform_description/PlatformDescription.cpp
src/instances/platform_profiles/PlatformTest1.cpp
 )
 
  
 add_executable(simple_action_speak_execution src/simple_action_nodes/SimpleActionSpeakNode.cpp
src/general_description/platform_description/PlatformDescription.cpp
src/instances/platform_profiles/PlatformTest1.cpp
 )
 
  add_executable(simple_action_oscillate_shoulder_execution src/simple_action_nodes/SimpleActionOscillateShoulderNode.cpp
src/general_description/platform_description/PlatformDescription.cpp
src/instances/platform_profiles/PlatformTest1.cpp
 )
 
  add_executable(simple_action_body_execution src/simple_action_nodes/SimpleActionBodyNode.cpp
src/triskar_small/Planning.cpp
 )
 
 add_executable(joy_pad_triskar src/TestNodes/JoyPadTriskar.cpp)
 
 target_link_libraries(simple_action_body_execution ${catkin_LIBRARIES})       
 target_link_libraries(simple_action_oscillate_shoulder_execution ${catkin_LIBRARIES})
 target_link_libraries(simple_action_speak_execution ${catkin_LIBRARIES})
 target_link_libraries(action_execution ${catkin_LIBRARIES})
 target_link_libraries(action_modulation ${catkin_LIBRARIES})
 target_link_libraries(joy_pad_triskar ${catkin_LIBRARIES})
 
 add_executable(action_test src/TestNode.cpp
 )  
 
 target_link_libraries(action_test ${catkin_LIBRARIES})
 
 add_executable(action_test_position src/TestNodes/TestPositionNode.cpp
 )  
 
 target_link_libraries(action_test_position ${catkin_LIBRARIES})
 
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
add_dependencies(action_modulation theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(action_execution theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(simple_action_speak_execution theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(simple_action_oscillate_shoulder_execution theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(simple_action_body_execution theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(action_test theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(action_test_position theatrebot_action_modulation_generate_messages_cpp)
add_dependencies(joy_pad_triskar theatrebot_action_modulation_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(theatrebot_action_modulation_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS theatrebot_action_modulation theatrebot_action_modulation_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_theatrebot_action_modulation.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
catkin_package()
