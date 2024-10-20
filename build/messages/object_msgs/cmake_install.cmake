# Install script for directory: /home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_msgs/msg/object_recognition" TYPE FILE FILES
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_msgs/msg/traffic_light_recognition" TYPE FILE FILES
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_msgs/cmake" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/object_msgs/catkin_generated/installspace/object_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/include/object_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/share/roseus/ros/object_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/share/common-lisp/ros/object_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/share/gennodejs/ros/object_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/lib/python3/dist-packages/object_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/devel/lib/python3/dist-packages/object_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/object_msgs/catkin_generated/installspace/object_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_msgs/cmake" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/object_msgs/catkin_generated/installspace/object_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_msgs/cmake" TYPE FILE FILES
    "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/object_msgs/catkin_generated/installspace/object_msgsConfig.cmake"
    "/home/xining095/Carmaker/smartcar/miniEV_grad/build/messages/object_msgs/catkin_generated/installspace/object_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_msgs" TYPE FILE FILES "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/package.xml")
endif()

