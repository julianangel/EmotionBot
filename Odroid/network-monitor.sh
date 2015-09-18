#!/bin/bash

echo "odroid" | sudo chmod 777 /dev/ttyACM0
echo "odroid" | sudo chmod 777 /dev/video0
echo "odroid" | sudo ifdown wlan0
sleep 30
echo "odroid" | sudo ifup wlan0
while true ; do
   if ifconfig wlan0 | grep -q "inet addr:" ; then
      sleep 60
   else
      echo "Network connection down! Attempting reconnection."
      ifup --force wlan0
      sleep 10
   fi
done

