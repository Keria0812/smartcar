# 安装其他ros包依赖
while true; do
    read -r -p "3. install ros-noetic package?  [Y/n] " input
    case $input in
        [yY][eE][sS] | [yY] | "")
            sudo apt-get update
            sudo apt-get install -y \
                libboost-all-dev \
                libboost-python-dev \
                libeigen3-dev \
                libgeographic-dev \
                libglfw3-dev \
                libglm-dev \
                libgtest-dev \
                libpugixml-dev \
                python3-catkin-tools \
                libpcap-dev \
                ros-noetic-angles \
                ros-noetic-camera-info-manager \
                ros-noetic-ddynamic-reconfigure \
                ros-noetic-diagnostic-updater \
                ros-noetic-geodesy \
                ros-noetic-jsk-recognition-msgs ros-noetic-visualization-msgs \
                ros-noetic-lanelet2 \
                ros-noetic-nav-msgs \
                ros-noetic-nmea-msgs \
                ros-noetic-tf2-sensor-msgs
            # catkin build的python依赖
            sudo apt install python3-pip
            pip3 install osrf-pycommon
            break
            ;;

        [nN][oO] | [nN])
            break
            ;;

        *)
            echo "Invalid input..."
            ;;
    esac
done
