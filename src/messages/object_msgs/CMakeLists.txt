cmake_minimum_required(VERSION 3.1.0)
project(object_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
  geometry_msgs
  sensor_msgs
  uuid_msgs
)

## Generate messages in the 'msg' folder
add_message_files(
  DIRECTORY msg/object_recognition
  FILES
    DynamicObject.msg
    DynamicObjectArray.msg
    Shape.msg
    Semantic.msg
    State.msg
    Feature.msg
    PredictedPath.msg
    DynamicObjectWithFeature.msg
    DynamicObjectWithFeatureArray.msg
    PredictedPath.msg
)
add_message_files(
  DIRECTORY msg/traffic_light_recognition
  FILES
    LampState.msg
    TrafficLightRoi.msg
    TrafficLightRoiArray.msg
    TrafficLightState.msg
    TrafficLightStateArray.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
    std_msgs
    geometry_msgs
    sensor_msgs
    uuid_msgs
)

catkin_package(
  CATKIN_DEPENDS
    message_runtime
    std_msgs
    geometry_msgs
    sensor_msgs
    uuid_msgs
)
