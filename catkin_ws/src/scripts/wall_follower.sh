#!/bin/sh
export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/src/map/myworld.world
export TURTLEBOT_GAZEBO_MAP_FILE=$(pwd)/src/map/map.yaml
pip install rospkg
sudo apt-get install ros-melodic-teleop-twist-keyboard
catkin_make

xterm -e " source devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch my_robot gmapping.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " source devel/setup.bash; rosrun wall_follower wall_follower"
sleep 5
#after you finish exploring press enter in the last terminal to save map
#xterm -e " source devel/setup.bash; rosrun map_server map_saver -f /home/workspace/catkin_ws/src/map/gmap>" &
