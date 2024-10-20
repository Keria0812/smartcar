# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "object_msgs: 15 messages, 0 services")

set(MSG_I_FLAGS "-Iobject_msgs:/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition;-Iobject_msgs:/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(object_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" "geometry_msgs/Polygon:geometry_msgs/TwistWithCovariance:geometry_msgs/Point:geometry_msgs/Vector3:geometry_msgs/PoseWithCovarianceStamped:object_msgs/Shape:geometry_msgs/Pose:std_msgs/Header:object_msgs/State:geometry_msgs/Accel:geometry_msgs/Point32:geometry_msgs/Quaternion:object_msgs/PredictedPath:geometry_msgs/Twist:geometry_msgs/PoseWithCovariance:geometry_msgs/AccelWithCovariance:object_msgs/Semantic"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" "geometry_msgs/Polygon:geometry_msgs/TwistWithCovariance:geometry_msgs/Point:geometry_msgs/Vector3:geometry_msgs/PoseWithCovarianceStamped:object_msgs/Shape:geometry_msgs/Pose:std_msgs/Header:object_msgs/State:geometry_msgs/Accel:geometry_msgs/Point32:geometry_msgs/Quaternion:object_msgs/PredictedPath:object_msgs/DynamicObject:geometry_msgs/Twist:geometry_msgs/PoseWithCovariance:geometry_msgs/AccelWithCovariance:object_msgs/Semantic"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" "geometry_msgs/Polygon:geometry_msgs/Point32:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" ""
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" "geometry_msgs/TwistWithCovariance:geometry_msgs/Point:geometry_msgs/Vector3:geometry_msgs/PoseWithCovarianceStamped:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Accel:geometry_msgs/Quaternion:object_msgs/PredictedPath:geometry_msgs/Twist:geometry_msgs/PoseWithCovariance:geometry_msgs/AccelWithCovariance"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" "sensor_msgs/PointCloud2:sensor_msgs/RegionOfInterest:std_msgs/Header:sensor_msgs/PointField"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" "geometry_msgs/Point:geometry_msgs/PoseWithCovarianceStamped:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/PoseWithCovariance"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" "geometry_msgs/Vector3:geometry_msgs/PoseWithCovarianceStamped:object_msgs/Feature:geometry_msgs/PoseWithCovariance:geometry_msgs/Point:sensor_msgs/RegionOfInterest:sensor_msgs/PointField:object_msgs/State:geometry_msgs/Accel:object_msgs/PredictedPath:object_msgs/DynamicObject:geometry_msgs/Polygon:sensor_msgs/PointCloud2:object_msgs/Shape:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Point32:geometry_msgs/Quaternion:object_msgs/Semantic:geometry_msgs/TwistWithCovariance:geometry_msgs/Twist:geometry_msgs/AccelWithCovariance"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" "geometry_msgs/Vector3:geometry_msgs/PoseWithCovarianceStamped:object_msgs/Feature:geometry_msgs/PoseWithCovariance:geometry_msgs/Point:sensor_msgs/RegionOfInterest:sensor_msgs/PointField:object_msgs/State:geometry_msgs/Accel:object_msgs/PredictedPath:object_msgs/DynamicObject:geometry_msgs/Polygon:sensor_msgs/PointCloud2:object_msgs/DynamicObjectWithFeature:object_msgs/Shape:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Point32:geometry_msgs/Quaternion:object_msgs/Semantic:geometry_msgs/TwistWithCovariance:geometry_msgs/Twist:geometry_msgs/AccelWithCovariance"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" ""
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" "sensor_msgs/RegionOfInterest"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" "sensor_msgs/RegionOfInterest:object_msgs/TrafficLightRoi:std_msgs/Header"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" "object_msgs/LampState"
)

get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" NAME_WE)
add_custom_target(_object_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "object_msgs" "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" "object_msgs/TrafficLightState:object_msgs/LampState:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)
_generate_msg_cpp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(object_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(object_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(object_msgs_generate_messages object_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_cpp _object_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(object_msgs_gencpp)
add_dependencies(object_msgs_gencpp object_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS object_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)
_generate_msg_eus(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(object_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(object_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(object_msgs_generate_messages object_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_eus _object_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(object_msgs_geneus)
add_dependencies(object_msgs_geneus object_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS object_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)
_generate_msg_lisp(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(object_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(object_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(object_msgs_generate_messages object_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_lisp _object_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(object_msgs_genlisp)
add_dependencies(object_msgs_genlisp object_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS object_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)
_generate_msg_nodejs(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(object_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(object_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(object_msgs_generate_messages object_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_nodejs _object_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(object_msgs_gennodejs)
add_dependencies(object_msgs_gennodejs object_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS object_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Accel.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/TwistWithCovariance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/AccelWithCovariance.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)
_generate_msg_py(object_msgs
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg"
  "${MSG_I_FLAGS}"
  "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg;/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(object_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(object_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(object_msgs_generate_messages object_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObject.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Shape.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Semantic.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/State.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/Feature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/PredictedPath.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeature.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/object_recognition/DynamicObjectWithFeatureArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/LampState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoi.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightRoiArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightState.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xining095/Carmaker/smartcar/miniEV_grad/src/messages/object_msgs/msg/traffic_light_recognition/TrafficLightStateArray.msg" NAME_WE)
add_dependencies(object_msgs_generate_messages_py _object_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(object_msgs_genpy)
add_dependencies(object_msgs_genpy object_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS object_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/object_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(object_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(object_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(object_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET uuid_msgs_generate_messages_cpp)
  add_dependencies(object_msgs_generate_messages_cpp uuid_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/object_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(object_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(object_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(object_msgs_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET uuid_msgs_generate_messages_eus)
  add_dependencies(object_msgs_generate_messages_eus uuid_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/object_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(object_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(object_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(object_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET uuid_msgs_generate_messages_lisp)
  add_dependencies(object_msgs_generate_messages_lisp uuid_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/object_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(object_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(object_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(object_msgs_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET uuid_msgs_generate_messages_nodejs)
  add_dependencies(object_msgs_generate_messages_nodejs uuid_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/object_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(object_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(object_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(object_msgs_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET uuid_msgs_generate_messages_py)
  add_dependencies(object_msgs_generate_messages_py uuid_msgs_generate_messages_py)
endif()
