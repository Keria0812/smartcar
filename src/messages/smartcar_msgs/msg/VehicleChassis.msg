Header header
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
