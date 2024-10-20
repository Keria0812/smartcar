# Install script for directory: /home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/xining095/Carmaker/smartcar/miniEV_grad/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/msg" TYPE FILE FILES
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ACCTarget.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ControlCommandStamped.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/CloudCluster.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/CloudClusterArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ColorSet.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ControlCommand.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/DetectedObject.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/DetectedObjectArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ExtractedPosition.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageLaneObjects.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageObjects.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/LaneArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/PointsImage.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ScanImage.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Signals.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/TunedResult.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ValueSet.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Centroids.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/DTLane.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/GeometricRectangle.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ICPStat.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageObj.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageObjRanged.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageObjTracked.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageRect.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ImageRectRanged.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Lane.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/NDTStat.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ObjLabel.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ObjPose.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ProjectionMatrix.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VscanTracked.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VscanTrackedArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Waypoint.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/WaypointState.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleLocation.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleStatus.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/TrafficLightResult.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/TrafficLightResultArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/AccelCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/AdjustXY.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/BrakeCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/IndicatorCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/LampCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/SteerCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/TrafficLight.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/StateCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/State.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/HunterStatus.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/HunterMotorState.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/SyncTimeMonitor.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/SyncTimeDiff.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/RemoteCmd.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Grid.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/My_Trajectory.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/My_Trajectory_Point.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleInfo.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/DimensionInfo.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/LateralData.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/LongitudinalData.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Control.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Augmented_My_Trajectory_Point.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/ObstacleAttr.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Obstacles.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleLightCommand.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleLightState.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/Location.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/My_TrajectoryArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/msg/VehicleChassis.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/cmake" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/smartcar_msgs/catkin_generated/installspace/smartcar_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/include/smartcar_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/share/roseus/ros/smartcar_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/share/common-lisp/ros/smartcar_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/share/gennodejs/ros/smartcar_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/lib/python3/dist-packages/smartcar_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/lib/python3/dist-packages/smartcar_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/smartcar_msgs/catkin_generated/installspace/smartcar_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/cmake" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/smartcar_msgs/catkin_generated/installspace/smartcar_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/cmake" TYPE FILE FILES
    "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/smartcar_msgs/catkin_generated/installspace/smartcar_msgsConfig.cmake"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/smartcar_msgs/catkin_generated/installspace/smartcar_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/smartcar_msgs/package.xml")
endif()

