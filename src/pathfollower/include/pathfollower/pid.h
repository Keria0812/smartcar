/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-11 16:20:25
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-06-11 21:29:51
 * @FilePath: /miniEV/src/pathfollower/include/pathfollower/pid.h
 */
#ifndef PATHFOLLOWER_PID_H_
#define PATHFOLLOWER_PID_H_
namespace PathFollower {

class PID {
 public:
  PID(const double kp, const double ki, const double kd) : kp_(kp), ki_(ki), kd_(kd) {};
  PID(const double kp, const double ki, const double kd, double limMax, double limMin,
         double limMaxInt, double limMinInt) :     kp_(kp), ki_(ki), kd_(kd),
        limMax_(limMax), limMin_(limMin),limMaxInt_(limMaxInt), limMinInt_(limMinInt) {} ;

        
  ~PID() = default;

  void Reset();

  /**
   * @brief compute control value based on the error
   * @param error error value, the difference between
   * a desired value and a measured value
   * @param dt sampling time interval
   * @return control value based on PID terms
   */
  double Control(const double error, const double dt);

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

}//PathFollower
#endif //PATHFOLLOWER_PID_H_