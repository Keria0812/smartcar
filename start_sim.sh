#!/bin/bash

#ps aux | grep ros |  awk '{print $2}' | xargs kill -9; ps aux | grep rviz |  awk '{print $2}' | xargs kill -9
#sleep 1

# roscore
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roscore;exec bash"'& 
sleep 1

# sim
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch simulator simulator_node.launch arg1:=1;exec bash"' 
sleep 1

# map
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch map map.launch;exec bash"' &
sleep 1

# plan
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch planning planning.launch debug_pathfollow:=true;exec bash"' &
sleep 1

# follow
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch pathfollower pathfollower_node.launch FollowMethod:=Stanely VehicleConfig:=Tesla
;exec bash"' &
sleep 1

# visualization
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch show_trajectory show_trajectory.launch;exec bash"' &
sleep 1

# visualization
# gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch naive_motion_predict naive_motion_predict.launch;exec bash"' &
# sleep 1

# visualization
# gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;rosparam set /reference_line_id 0;exec bash"' &
# sleep 1

# 0 
# roscore
# sudo apt-get install ros-noetic-jsk-recognition-msgs ros-noetic-jsk-rviz-plugins ros-noetic-lanelet2* ros-noetic-nmea* ros-noetic-grid-map* ros-noetic-automotive-* ros-noetic-velodyne* ros-noetic-gps-common ros-noetic-qpoases-vendor 

# sudo apt-get install ros-noetic-autoware-lanelet2-msgs
# sudo apt-get install ros-noetic-uuid-msgs
# 1
# catkin_make -DCATKIN_WHITELIST_PACKAGES=simulator
# sudo ln -s /usr/include/eigen3/Eigen /usr/include/Eigen

# source devel/setup.sh
# roslaunch simulator simulator_node.launch
# 2
# source devel/setup.sh
# roslaunch map map.launch 
# 3
# source devel/setup.sh
# roslaunch naive_motion_predict  naive_motion_predict.launch 
# 4
# source devel/setup.sh
# roslaunch planning planning.launch debug_pathfollow:=True
# 5
# source devel/setup.sh
# roslaunch show_trajectory show_trajectory.launch 
# 6
# source devel/setup.sh
# roslaunch pathfollower pathfollower_node.launch FollowMethod:=Manual
# # roslaunch pathfollower pathfollower_node.launch FollowMethod:=Stanely
# 7
# source devel/setup.sh
# rqt_plot
# manural 模式的三个实验
# 记得每个启动之前都要source devel/setup.sh