/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-11 16:20:25
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-09 03:47:27
 * @FilePath: /miniEV/src/simulation/simulator/include/simulator/pid.h
 */
#ifndef SIMULATOR_PID_H_
#define SIMULATOR_PID_H_
// namespace PathFollower {

class PID {
 public:
  PID(const double kp, const double ki, const double kd) : kp_(kp), ki_(ki), kd_(kd) {};
  PID(const double kp, const double ki, const double kd, double limMax, double limMin,
         double limMaxInt, double limMinInt) :     kp_(kp), ki_(ki), kd_(kd),
        limMax_(limMax), limMin_(limMin),limMaxInt_(limMaxInt), limMinInt_(limMinInt) {} ;

        
  ~PID() = default;

//   void Reset();

  /**
   * @brief compute control value based on the error
   * @param error error value, the difference between
   * a desired value and a measured value
   * @param dt sampling time interval
   * @return control value based on PID terms
   */
//   double Control(const double error, const double dt);
  double Control(const double error, const double dt) {
    if (dt <= 0) {
        return previous_output_;
    }
    double diff = 0;
    double output = 0;

    if (first_hit_)    // first_hit_: 用来选择是否计算diff
    {
        first_hit_ = false;
    } else {
        diff = (error - previous_error_) / dt;
    }

    integral_ += ki_ * error * dt;    // 积分环节

    output = kp_ * error + integral_ + diff * kd_;
    if (output > limMax_) output = limMax_;
    if (output < limMin_) output = limMin_;

    previous_output_ = output;
    previous_error_ = error;
    return output;
}

void Reset() {
    previous_error_ = 0.0;
    previous_output_ = 0.0;
    integral_ = 0.0;
    first_hit_ = true;
}

 protected:
    double kp_ = 0.0;
    double ki_ = 0.0;
    double kd_ = 0.0;
    double previous_error_ = 0.0;
    double previous_output_ = 0.0;
    double integral_ = 0.0;

    // double sim_dt_ = 0.01;//simple_time, s

    double limMax_ = __DBL_MAX__;
    double limMin_ = __DBL_MIN__;
    double limMaxInt_ = __DBL_MAX__;
    double limMinInt_ = __DBL_MIN__;

    bool first_hit_ = true;
};

// }//SIMULATOR_PID_H_
#endif //SIMULATOR_PID_H_