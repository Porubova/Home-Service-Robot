#!/bin/sh


pip install rospkg
sudo apt-get install ros-melodic-teleop-twist-keyboard
catkin_make

xterm -e " source devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch my_robot gmapping.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch my_robot teleop.launch"
sleep 5
#after you finish exploring press enter in the last terminal to save map
xterm -e " source devel/setup.bash; rosrun map_server map_saver -f /home/workspace/catkin_ws/src/map/gmap>" &
