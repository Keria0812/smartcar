#!/usr/bin/bash
#catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3


rm -rf devel build
./shell/msg.sh
catkin_make -DCATKIN_WHITELIST_PACKAGES=""
