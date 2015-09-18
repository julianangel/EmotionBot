interfaces goes into /etc/network/, this files configures the wifi


network-monitor.sh goes into /etc/init.d/, this files watch if the wifi is active or not, if is not active it tries to make it active
then update-rc.d network-monitor.sh defaults

To synchronize two different computer it should install chrony
sudo apt-get install chrony

Then in the odroid should be configured in the file
/usr/local/bin/chronyc
//TODO
