;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::VehicleChassis)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'VehicleChassis (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::VEHICLECHASSIS")
  (make-package "SMARTCAR_MSGS::VEHICLECHASSIS"))

(in-package "ROS")
;;//! \htmlinclude VehicleChassis.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::VehicleChassis
  :super ros::object
  :slots (_header _cmd_torque _cmd_decelaration _cmd_gas _cmd_brake _cmd_steerAng _feedback_brake_press _feedback_gas _feedback_torque _feedback_Motor_rotv _feedback_steerAng _feedback_tireAng _gas_pedal_press _brake_pedal_press _gear _orientation _linear_velocity _vehicleAcceleration _wheelspeed _light_state _vehiclespeed _vcu_mode ))

(defmethod smartcar_msgs::VehicleChassis
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:cmd_torque __cmd_torque) 0.0)
    ((:cmd_decelaration __cmd_decelaration) 0.0)
    ((:cmd_gas __cmd_gas) 0.0)
    ((:cmd_brake __cmd_brake) 0.0)
    ((:cmd_steerAng __cmd_steerAng) 0.0)
    ((:feedback_brake_press __feedback_brake_press) 0.0)
    ((:feedback_gas __feedback_gas) 0.0)
    ((:feedback_torque __feedback_torque) 0.0)
    ((:feedback_Motor_rotv __feedback_Motor_rotv) 0.0)
    ((:feedback_steerAng __feedback_steerAng) 0.0)
    ((:feedback_tireAng __feedback_tireAng) 0.0)
    ((:gas_pedal_press __gas_pedal_press) nil)
    ((:brake_pedal_press __brake_pedal_press) nil)
    ((:gear __gear) "")
    ((:orientation __orientation) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:linear_velocity __linear_velocity) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:vehicleAcceleration __vehicleAcceleration) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:wheelspeed __wheelspeed) (make-array 4 :initial-element 0.0 :element-type :float))
    ((:light_state __light_state) (instance smartcar_msgs::VehicleLightState :init))
    ((:vehiclespeed __vehiclespeed) 0.0)
    ((:vcu_mode __vcu_mode) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _cmd_torque (float __cmd_torque))
   (setq _cmd_decelaration (float __cmd_decelaration))
   (setq _cmd_gas (float __cmd_gas))
   (setq _cmd_brake (float __cmd_brake))
   (setq _cmd_steerAng (float __cmd_steerAng))
   (setq _feedback_brake_press (float __feedback_brake_press))
   (setq _feedback_gas (float __feedback_gas))
   (setq _feedback_torque (float __feedback_torque))
   (setq _feedback_Motor_rotv (float __feedback_Motor_rotv))
   (setq _feedback_steerAng (float __feedback_steerAng))
   (setq _feedback_tireAng (float __feedback_tireAng))
   (setq _gas_pedal_press __gas_pedal_press)
   (setq _brake_pedal_press __brake_pedal_press)
   (setq _gear (string __gear))
   (setq _orientation __orientation)
   (setq _linear_velocity __linear_velocity)
   (setq _vehicleAcceleration __vehicleAcceleration)
   (setq _wheelspeed __wheelspeed)
   (setq _light_state __light_state)
   (setq _vehiclespeed (float __vehiclespeed))
   (setq _vcu_mode (round __vcu_mode))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:cmd_torque
   (&optional __cmd_torque)
   (if __cmd_torque (setq _cmd_torque __cmd_torque)) _cmd_torque)
  (:cmd_decelaration
   (&optional __cmd_decelaration)
   (if __cmd_decelaration (setq _cmd_decelaration __cmd_decelaration)) _cmd_decelaration)
  (:cmd_gas
   (&optional __cmd_gas)
   (if __cmd_gas (setq _cmd_gas __cmd_gas)) _cmd_gas)
  (:cmd_brake
   (&optional __cmd_brake)
   (if __cmd_brake (setq _cmd_brake __cmd_brake)) _cmd_brake)
  (:cmd_steerAng
   (&optional __cmd_steerAng)
   (if __cmd_steerAng (setq _cmd_steerAng __cmd_steerAng)) _cmd_steerAng)
  (:feedback_brake_press
   (&optional __feedback_brake_press)
   (if __feedback_brake_press (setq _feedback_brake_press __feedback_brake_press)) _feedback_brake_press)
  (:feedback_gas
   (&optional __feedback_gas)
   (if __feedback_gas (setq _feedback_gas __feedback_gas)) _feedback_gas)
  (:feedback_torque
   (&optional __feedback_torque)
   (if __feedback_torque (setq _feedback_torque __feedback_torque)) _feedback_torque)
  (:feedback_Motor_rotv
   (&optional __feedback_Motor_rotv)
   (if __feedback_Motor_rotv (setq _feedback_Motor_rotv __feedback_Motor_rotv)) _feedback_Motor_rotv)
  (:feedback_steerAng
   (&optional __feedback_steerAng)
   (if __feedback_steerAng (setq _feedback_steerAng __feedback_steerAng)) _feedback_steerAng)
  (:feedback_tireAng
   (&optional __feedback_tireAng)
   (if __feedback_tireAng (setq _feedback_tireAng __feedback_tireAng)) _feedback_tireAng)
  (:gas_pedal_press
   (&optional (__gas_pedal_press :null))
   (if (not (eq __gas_pedal_press :null)) (setq _gas_pedal_press __gas_pedal_press)) _gas_pedal_press)
  (:brake_pedal_press
   (&optional (__brake_pedal_press :null))
   (if (not (eq __brake_pedal_press :null)) (setq _brake_pedal_press __brake_pedal_press)) _brake_pedal_press)
  (:gear
   (&optional __gear)
   (if __gear (setq _gear __gear)) _gear)
  (:orientation
   (&optional __orientation)
   (if __orientation (setq _orientation __orientation)) _orientation)
  (:linear_velocity
   (&optional __linear_velocity)
   (if __linear_velocity (setq _linear_velocity __linear_velocity)) _linear_velocity)
  (:vehicleAcceleration
   (&optional __vehicleAcceleration)
   (if __vehicleAcceleration (setq _vehicleAcceleration __vehicleAcceleration)) _vehicleAcceleration)
  (:wheelspeed
   (&optional __wheelspeed)
   (if __wheelspeed (setq _wheelspeed __wheelspeed)) _wheelspeed)
  (:light_state
   (&rest __light_state)
   (if (keywordp (car __light_state))
       (send* _light_state __light_state)
     (progn
       (if __light_state (setq _light_state (car __light_state)))
       _light_state)))
  (:vehiclespeed
   (&optional __vehiclespeed)
   (if __vehiclespeed (setq _vehiclespeed __vehiclespeed)) _vehiclespeed)
  (:vcu_mode
   (&optional __vcu_mode)
   (if __vcu_mode (setq _vcu_mode __vcu_mode)) _vcu_mode)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _cmd_torque
    8
    ;; float64 _cmd_decelaration
    8
    ;; float64 _cmd_gas
    8
    ;; float64 _cmd_brake
    8
    ;; float64 _cmd_steerAng
    8
    ;; float64 _feedback_brake_press
    8
    ;; float64 _feedback_gas
    8
    ;; float64 _feedback_torque
    8
    ;; float64 _feedback_Motor_rotv
    8
    ;; float64 _feedback_steerAng
    8
    ;; float64 _feedback_tireAng
    8
    ;; bool _gas_pedal_press
    1
    ;; bool _brake_pedal_press
    1
    ;; string _gear
    4 (length _gear)
    ;; float64[3] _orientation
    (* 8    3)
    ;; float64[3] _linear_velocity
    (* 8    3)
    ;; float64[3] _vehicleAcceleration
    (* 8    3)
    ;; float64[4] _wheelspeed
    (* 8    4)
    ;; smartcar_msgs/VehicleLightState _light_state
    (send _light_state :serialization-length)
    ;; float64 _vehiclespeed
    8
    ;; int32 _vcu_mode
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _cmd_torque
       (sys::poke _cmd_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _cmd_decelaration
       (sys::poke _cmd_decelaration (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _cmd_gas
       (sys::poke _cmd_gas (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _cmd_brake
       (sys::poke _cmd_brake (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _cmd_steerAng
       (sys::poke _cmd_steerAng (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback_brake_press
       (sys::poke _feedback_brake_press (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback_gas
       (sys::poke _feedback_gas (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback_torque
       (sys::poke _feedback_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback_Motor_rotv
       (sys::poke _feedback_Motor_rotv (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback_steerAng
       (sys::poke _feedback_steerAng (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback_tireAng
       (sys::poke _feedback_tireAng (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _gas_pedal_press
       (if _gas_pedal_press (write-byte -1 s) (write-byte 0 s))
     ;; bool _brake_pedal_press
       (if _brake_pedal_press (write-byte -1 s) (write-byte 0 s))
     ;; string _gear
       (write-long (length _gear) s) (princ _gear s)
     ;; float64[3] _orientation
     (dotimes (i 3)
       (sys::poke (elt _orientation i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _linear_velocity
     (dotimes (i 3)
       (sys::poke (elt _linear_velocity i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _vehicleAcceleration
     (dotimes (i 3)
       (sys::poke (elt _vehicleAcceleration i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[4] _wheelspeed
     (dotimes (i 4)
       (sys::poke (elt _wheelspeed i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; smartcar_msgs/VehicleLightState _light_state
       (send _light_state :serialize s)
     ;; float64 _vehiclespeed
       (sys::poke _vehiclespeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _vcu_mode
       (write-long _vcu_mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _cmd_torque
     (setq _cmd_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _cmd_decelaration
     (setq _cmd_decelaration (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _cmd_gas
     (setq _cmd_gas (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _cmd_brake
     (setq _cmd_brake (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _cmd_steerAng
     (setq _cmd_steerAng (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback_brake_press
     (setq _feedback_brake_press (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback_gas
     (setq _feedback_gas (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback_torque
     (setq _feedback_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback_Motor_rotv
     (setq _feedback_Motor_rotv (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback_steerAng
     (setq _feedback_steerAng (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback_tireAng
     (setq _feedback_tireAng (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _gas_pedal_press
     (setq _gas_pedal_press (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _brake_pedal_press
     (setq _brake_pedal_press (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _gear
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _gear (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64[3] _orientation
   (dotimes (i (length _orientation))
     (setf (elt _orientation i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _linear_velocity
   (dotimes (i (length _linear_velocity))
     (setf (elt _linear_velocity i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _vehicleAcceleration
   (dotimes (i (length _vehicleAcceleration))
     (setf (elt _vehicleAcceleration i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[4] _wheelspeed
   (dotimes (i (length _wheelspeed))
     (setf (elt _wheelspeed i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; smartcar_msgs/VehicleLightState _light_state
     (send _light_state :deserialize buf ptr-) (incf ptr- (send _light_state :serialization-length))
   ;; float64 _vehiclespeed
     (setq _vehiclespeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _vcu_mode
     (setq _vcu_mode (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::VehicleChassis :md5sum-) "ebba083aece22e9a5c6fc1592f401f4c")
(setf (get smartcar_msgs::VehicleChassis :datatype-) "smartcar_msgs/VehicleChassis")
(setf (get smartcar_msgs::VehicleChassis :definition-)
      "Header header
#控制量
float64 cmd_torque  #N·m
float64 cmd_decelaration #m/s^2
float64 cmd_gas 
float64 cmd_brake
float64 cmd_steerAng #deg
#反馈量
float64 feedback_brake_press  #%100
float64 feedback_gas  #%100
float64 feedback_torque  #N·m
float64 feedback_Motor_rotv #round/min
float64 feedback_steerAng #deg
float64 feedback_tireAng #deg


bool gas_pedal_press
bool brake_pedal_press
string gear
float64[3] orientation #deg, Guass frame(deg), X-front, Y-right, Z-down pitch, roll, yaw
float64[3] linear_velocity  #km/h, Guass frame
float64[3] vehicleAcceleration #m/s^2 vehicle frame
float64[4] wheelspeed #FL、FR、RL、RR km/h

#EV
smartcar_msgs/VehicleLightState light_state #EV
#km/h
float64 vehiclespeed 

#vcu_mode, 0 manual_driving, 1 iECU , 2 remote_driving, 3 only control steer, 4 only control gas/brake
int32 vcu_mode  

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: smartcar_msgs/VehicleLightState
Header header
#0 mid, 1 turn left, 2 turn right
int32 turn_light 

#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam
int32 car_light

")



(provide :smartcar_msgs/VehicleChassis "ebba083aece22e9a5c6fc1592f401f4c")


