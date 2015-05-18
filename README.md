EmotionBot
==========
This resposotires stores the TheatreBot project (http://airwiki.ws.dei.polimi.it/index.php/TheatreBot). 
There are two version of the system:
#theatrebot_action_modulation
This is the first implementation done, 2014. Altough it was design and then implemented, due to the limitations in ROS to create messages based on abstract classes, the ROS implementation was created using specific messages for each type of message. This creates the necessity to have different topic as messages to communicate among nodes. Also the code has a high cohession with the ROS part. 
This implementation does not use JSON format for the information messages.
#theatre_bot
This implementation was done based on the first and improved from the pitfalls detected during the case of study. This implementation uses a JSON messages to send the whole infomartion, thus the topics necessary to send information are reduce, but the necesity to interpret the messages are added. The core and the ROS implementation are separated, now it is possible to do debug of the core independently of the use of ROS.
##Communication with the platform
The communication with the platform is done through ROS-Serial
#ID Markers
The package ar_track_alvar (http://wiki.ros.org/ar_track_alvar) is used
