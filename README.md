# Home Service robot

The final project for Udacity's Robotic Software Enginerer Nanodegree Program. The 

# Overview
- Design robot's environment with the Building Editor in Gazebo.
  -  Create a functional 2D map of the environment using simultaneous localization and mapping (SLAM) technique, which would be used for localization and navigation tasks. 
  - Write a pick_objects node that commands the robot to move to the desired pickup and drop off zones.
  - Write an add_markers node that subscribes to the robot odometry and publishes pick-up and drop-off markers to rviz.
  - Create home_serice shell script which runs pick_objects and  add_markers nodes, employs amcl, probabilistic localization system to localize and navigate robot in a 2D environment. 
  - Employ ROS Visualization tool to view the simulated robot model, read its sensors and visualize performing tasks.

# Prerequisites

  - ROS Kinetic
  - Gazebo >= 7.0
  - Ubuntu 16.04


Besides for this project I used official ROS Packages
 - [gmapping:](http://wiki.ros.org/gmapping) gmapping_demo.launch easily performs SLAM and builds a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.
 - [turtlebot_teleop:](http://wiki.ros.org/turtlebot_teleop) keyboard_teleop.launch  manually controls a robot using keyboard commands.
- [turtlebot_rviz_launchers:](http://wiki.ros.org/turtlebot_rviz_launchers) view_navigation.launch file loads a preconfigured rviz workspace.
- [turtlebot_gazebo:](http://wiki.ros.org/turtlebot_gazebo) turtlebot_world.launch can deploy a turtlebot in a gazebo environment by linking the world file to it.

### Directory Tree and contents

```sh
.
|-- add_markers
|   |-- include
|   `-- src
|-- map
|-- my_robot
|   |-- config
|   |-- launch
|   |-- meshes
|   |-- urdf
|   `-- worlds
|-- pick_objects
|   `-- src
|-- rvizConfig
|-- scripts
|-- slam_gmapping
|   |-- gmapping
|   `-- slam_gmapping
|-- teleop_twist_keyboard
|-- turtlebot
|   |-- turtlebot
|   |-- turtlebot_bringup
|   |-- turtlebot_capabilities
|   |-- turtlebot_description
|   `-- turtlebot_teleop
|-- turtlebot_interactions
|   |-- turtlebot_dashboard
|   |-- turtlebot_interactions
|   |-- turtlebot_interactive_markers
|   `-- turtlebot_rviz_launchers
|-- turtlebot_simulator
|   |-- turtlebot_gazebo
|   |-- turtlebot_simulator
|   |-- turtlebot_stage
|   `-- turtlebot_stdr
`-- wall_follower
    |-- scr
    `-- srv

```
## Packages and Directories
1. map: Inside this directory, you will store your gazebo world file and the map generated from SLAM.
2. scripts: Inside this directory, you’ll store your shell scripts.
3. rvizConfig:  customized rviz configuration file.
4. pick_objects: With a node that commands a robot to drive to the pickup and drop off zones.
5. add_markers: contains the script for add_markers node that model the object with a marker in rviz.
6. map : contains maps and gazebo world files, screenshots 
7. scripts - shell scripts
    - add_marker.sh - script for testing add_marker concept with add_markers_test.cpp
     - home_service.sh - main script for the home-service-robot
    - pick_objects.sh - script for testing pick_objects concept with pick_objects_test
    - test_navigation.sh - script for testing navigation
    - test_slam.sh - script for performing SLAM and preparing map
    - mapsing.sh - script to perform AMCL SLAM to generate 2 and 3D maps
    - gmapping.sh - custom gmaping script for 2D map
    - wall_follower - wall_follower script
8. add_markers: add_marker C++ node
9. pick_objects: pick-objects C++ node
10. my_robot: contains models of custom robot and world models, 2 and 3D AMSL(implementing Adaptive Monte Carlo Localization algorithm) launch files.
11. wall_follower: wall_follower C++ script. [credits to](https://github.com/udacity/RoboND-PathPlanning)



### Installation


To run the project you need to install xterminal:

```sh
sudo apt-get install xterm
```

Clone git repository
```sh
git clone https://github.com/Porubova/Home-Service-Robot.git
```

Navigate to clonned project workspace
```sh
cd Home-Service-Robot/catkin_cw
```

Install  ROS packages
```sh
cd /src
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git
git clone https://github.com/ros-teleop/teleop_twist_keyboard
cd ..
```
Update and install dependencies for ROS packages
```sh
sudo apt-get update
rosdep -i install gmapping -y
rosdep -i install turtlebot_teleop -y
rosdep -i install turtlebot_rviz_launchers -y
rosdep -i install turtlebot_gazebo -y
catkin_make
```

Chanage acces priveleges to shell scripts 
```sh
chmod +x ./src/scripts/home_service.sh
chmod +x ./src/scripts/wall_follower.sh
chmod +x ./src/scripts/gmapping.sh
chmod +x ./src/scripts/mapping.sh
chmod +x ./src/scripts/test_slam.sh
chmod +x ./src/scripts/test_navigation.sh
chmod +x ./src/scripts/add_markers.sh
chmod +x ./src/scripts/pick_objects.sh
```
### Run demo
Path plan and navigate the robot to the goal based on a 2D generated map of my world.

The first goal is displayed as a green marker on the map after the robot successfully reaches the pickup location the first marker disappears and the second marker is displayed. Again, the robot builds the second navigation path to it and moves to the dropoff location.

```sh
./src/scripts/home_service.sh
```

#### Home Service Robot

Result [Youtube](https://youtube.com)

