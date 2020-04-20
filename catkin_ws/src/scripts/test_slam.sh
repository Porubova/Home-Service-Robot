#!/bin/sh
export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/src/map/myworld.world
export TURTLEBOT_GAZEBO_MAP_FILE=$(pwd)/src/map/map.yaml
pip install rospkg
sudo apt-get install ros-melodic-teleop-twist-keyboard

catkin_make

xterm -e " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"
