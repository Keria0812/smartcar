#ps aux | grep ros |  awk '{print $2}' | xargs kill -9; ps aux | grep rviz |  awk '{print $2}' | xargs kill -9
###
 # @Copyright: jinxiaoxin@whut.edu.cn
 # @Author: jinxiaoxin235
 # @Date: 2023-07-24 19:29:03
 # @LastEditors: xining095
 # @LastEditTime: 20250428
 # @FilePath: /miniEV/miniEV_start.sh
### 
#sleep 1

# roscore*
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roscore;exec bash"'& 
sleep 1

#zlgcanbus
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;rosrun zlgcanbus sub_driving;exec bash"' &
sleep 1

#chassiscontrol
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch vehicle_controlEV vehicle_control.launch control_mode:=1;exec bash"' &
sleep 1

#gps_bridge
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;rosrun gps_bridge gps_bridge_node;exec bash"' &
sleep 1

# sim
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch simulator simulator_node.launch arg1:=1;exec bash"' &
sleep 1

# map
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch map map.launch;exec bash"' &
sleep 1

# plan
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch planning planning.launch debug_pathfollow:=true;exec bash"' &
sleep 1

# follow
gnome-terminal  --tab -e 'bash -ic "source devel/setup.bash;roslaunch pathfollower pathfollower_node.launch FollowMethod:=Stanely VehicleConfig:=miniEV;exec bash"' &
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
