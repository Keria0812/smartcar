#!/usr/bin/bash
###
 # @Copyright: jinxiaoxin@whut.edu.cn
 # @Author: jinxiaoxin235
 # @Date: 2023-06-27 22:24:02
 # @LastEditors: jinxiaoxin235
 # @LastEditTime: 2023-06-29 20:13:38
 # @FilePath: /miniEV/msg.sh
### 
catkin_make -DCATKIN_WHITELIST_PACKAGES=can_msgs
catkin_make -DCATKIN_WHITELIST_PACKAGES=smartcar_msgs
catkin_make -DCATKIN_WHITELIST_PACKAGES=prius_msgs
catkin_make -DCATKIN_WHITELIST_PACKAGES=object_msgs




