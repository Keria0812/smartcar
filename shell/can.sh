#!/bin/bash
#下方123456是密码，自行修改

ifconfig -a | grep can0 > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "\n\033[32mNo can0 this device\033[0m"
else
 
      ifconfig | grep can0 > /dev/null 2>&1
      if [ $? -ne 0 ]; then
sudo -S ip link  set can0 type can bitrate 500000 <<EOF
123
EOF
        sudo ip link  set up can0
        ifconfig | grep can0 > /dev/null 2>&1
        if [ $? -eq 0 ]; then
          echo -e "\n\033[32msetup can0 done\033[0m"
        else
          echo0 -e "\n\033[31msetup can0 failed\033[0m"
 
        fi
      else
        echo -e "\n\033[32mcan0 is ready\033[0m"
      fi
fi
