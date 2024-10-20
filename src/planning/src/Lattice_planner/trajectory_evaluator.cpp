#include "trajectory_evaluator.h"


TrajectoryEvaluator::TrajectoryEvaluator(
    const PlanningTarget &planning_target,
    const std::vector<PtrTrajectory1d> &lon_trajectories,
    const std::vector<PtrTrajectory1d> &lat_trajectories,
    const std::array<double, 3> &init_s,
    const std::shared_ptr<PathTimeGraph> &ptr_path_time_graph,
    const std::vector<ReferencePoint> &reference_points,
    const std::shared_ptr<ThreadPool> calc_pool)
    : path_time_graph_(ptr_path_time_graph), reference_points_(reference_points), init_s_(init_s)
{
  const double start_time = 0.0;
  const double end_time = Config_.FLAGS_trajectory_time_length;
  // 每个时刻，每个障碍物的s_lower, s_upper
  path_time_intervals_ = path_time_graph_->GetPathBlockingIntervals(start_time, end_time, Config_.FLAGS_trajectory_time_resolution);

  reference_s_dot_ = ComputeLongitudinalGuideVelocity(planning_target);

  if (!lon_trajectories.empty() && !lat_trajectories.empty())
  {
    //如果我们沿着参考线有一个停止点，过滤掉lon。经过停止点的轨迹。(暂不考虑)
    // double stop_point = std::numeric_limits<double>::max();
    // if (planning_target.has_stop_point())
    // {
    //     stop_point = planning_target.stop_point().s();
    // }
    //纵向轨迹和横向轨迹两两配对
    if (Config_.FLAGS_Plan4NGSIM_) {
        traj_features.reserve(lon_trajectories.size() *lat_trajectories.size());
    }
    std::vector< std::future<void>> results;
    for (const auto &lon_trajectory : lon_trajectories)
    {
      //如果我们沿着参考线有一个停止点，过滤掉lon。经过停止点的轨迹。(暂不考虑)
      // double lon_end_s = lon_trajectory->Evaluate(0, end_time);
      // if (init_s[0] < stop_point && lon_end_s + FLAGS_lattice_stop_buffer > stop_point)
      // {
      //     continue;
      // }

      if (!IsValidLongitudinalTrajectory(*lon_trajectory))
      {
        continue;
      }

      // std::cout << "has ValidLongitudinalTrajectory" << std::endl;
      

      for (const auto &lat_trajectory : lat_trajectories)
      {
        //通过优先级队列筛选最小cost的轨迹
        // double cost = Evaluate(planning_target, lon_trajectory, lat_trajectory);

        // cost_queue_.emplace(Trajectory1dPair(lon_trajectory, lat_trajectory), cost);
        results.emplace_back(calc_pool->enqueue([planning_target, lon_trajectory, lat_trajectory, calc_pool, this] {
          Evaluate(planning_target, lon_trajectory, lat_trajectory, calc_pool);
        }));
      }
    }
    // std::cout << results.size() << std::endl;
    // int i = 0;
    for (auto &res : results) {
      // std::cout << i++<< endl;
      res.get();
    } //判断线程是否运行完毕
    // std::cout << "size:" << lat_trajectories.size() << std::endl;
    //调试，打印队列
    // std::cout << "size:" << cost_queue_.size() << std::endl;
    // while (!cost_queue_.empty())
    // {
    //     auto top = cost_queue_.top();
    //     std::cout << "cost:" << top.second << std::endl;
    //     cost_queue_.pop();
    // }
  }
}

TrajectoryEvaluator::TrajectoryEvaluator(const PlanningTarget &planning_target,
                              const std::vector<std::pair<PtrTrajectory1d, PtrTrajectory1d>> &pair_trajectories,
                              const std::array<double, 3> &init_s,
                              const std::shared_ptr<PathTimeGraph> &ptr_path_time_graph,
                              const std::vector<ReferencePoint> &reference_points,
                              const std::shared_ptr<ThreadPool> calc_pool) 
                              : path_time_graph_(ptr_path_time_graph), reference_points_(reference_points), init_s_(init_s)
{
const double start_time = 0.0;
  const double end_time = Config_.FLAGS_trajectory_time_length;
  // 每个时刻，每个障碍物的s_lower, s_upper
  path_time_intervals_ = path_time_graph_->GetPathBlockingIntervals(start_time, end_time, Config_.FLAGS_trajectory_time_resolution);

  reference_s_dot_ = ComputeLongitudinalGuideVelocity(planning_target);

  if (!pair_trajectories.empty())
  {
    //如果我们沿着参考线有一个停止点，过滤掉lon。经过停止点的轨迹。(暂不考虑)
    // double stop_point = std::numeric_limits<double>::max();
    // if (planning_target.has_stop_point())
    // {
    //     stop_point = planning_target.stop_point().s();
    // }
    //纵向轨迹和横向轨迹两两配对
    // if (Config_.FLAGS_Plan4NGSIM_) {
    //     traj_features.reserve(lon_trajectories.size() *lat_trajectories.size());
    // }
    std::vector< std::future<void>> results;
    for (const auto &pair_trajectory : pair_trajectories)
    {
      //如果我们沿着参考线有一个停止点，过滤掉lon。经过停止点的轨迹。(暂不考虑)
      // double lon_end_s = lon_trajectory->Evaluate(0, end_time);
      // if (init_s[0] < stop_point && lon_end_s + FLAGS_lattice_stop_buffer > stop_point)
      // {
      //     continue;
      // }
      auto lon_trajectory = pair_trajectory.first;
      auto lat_trajectory = pair_trajectory.second;

      if (!IsValidLongitudinalTrajectory(*lon_trajectory))
      {
        continue;
      }

      // std::cout << "has ValidLongitudinalTrajectory" << std::endl;
      

      // for (const auto &lat_trajectory : lat_trajectories)
      {
        //通过优先级队列筛选最小cost的轨迹
        // double cost = Evaluate(planning_target, lon_trajectory, lat_trajectory);

        // cost_queue_.emplace(Trajectory1dPair(lon_trajectory, lat_trajectory), cost);
        results.emplace_back(calc_pool->enqueue([planning_target, lon_trajectory, lat_trajectory, calc_pool, this] {
          Evaluate(planning_target, lon_trajectory, lat_trajectory, calc_pool);
        }));
      }
    }
    // std::cout << results.size() << std::endl;
    // int i = 0;
    for (auto &res : results) {
      // std::cout << i++<< endl;
      res.get();
    } //判断线程是否运行完毕
    // std::cout << "size:" << lat_trajectories.size() << std::endl;
    //调试，打印队列
    // std::cout << "size:" << cost_queue_.size() << std::endl;
    // while (!cost_queue_.empty())
    // {
    //     auto top = cost_queue_.top();
    //     std::cout << "cost:" << top.second << std::endl;
    //     cost_queue_.pop();
    // }
  }
};

// top.first：fist:每条纵向轨迹和其对应的多项式，second:每条横向轨迹和其对应的多项式
// top.second:cost
std::pair<PtrTrajectory1d, PtrTrajectory1d> TrajectoryEvaluator::next_top_trajectory_pair()
{
  if (!cost_queue_.empty())
  {
    auto top = cost_queue_.top();
    cost_queue_.pop();
    return top.first;
  }
  return {};
}
//返回评价后的轨迹数量是否为空
bool TrajectoryEvaluator::has_more_trajectory_pairs() const
{
  return !cost_queue_.empty();
}
//返回评价后的轨迹数量
size_t TrajectoryEvaluator::num_of_trajectory_pairs() const
{
  return cost_queue_.size();
}
//求出轨迹的代价
double TrajectoryEvaluator::top_trajectory_pair_cost() const
{
  return cost_queue_.top().second;
}

//评价纵向轨迹
double TrajectoryEvaluator::Evaluate(const PlanningTarget &planning_target,
                                     const PtrTrajectory1d &lon_trajectory,
                                     const PtrTrajectory1d &lat_trajectory)
{
  // Costs:
  // 1. Cost of missing the objective, e.g., cruise, stop, etc.
  // 2. Cost of longitudinal jerk
  // 3. Cost of longitudinal collision
  // Longitudinal costs
  TrajFeature cur_feature;

  double lon_objective_cost = LonObjectiveCost(lon_trajectory, reference_s_dot_, cur_feature );
  double lon_jerk_cost = LonComfortCost(lon_trajectory);
  //我们速度低。先不开
  double lon_collision_cost = LonCollisionCost(lon_trajectory); //接近障碍物的绕行的时候车辆会减速，就是因为这个。
  // double lon_collision_cost = 0;
  double centripetal_acc_cost = CentripetalAccelerationCost(lon_trajectory);
  // decides the longitudinal evaluation horizon for lateral trajectories.
  double evaluation_horizon = std::min(Config_.FLAGS_speed_lon_decision_horizon, fabs(lon_trajectory->Evaluate(0, lon_trajectory->ParamLength())));
  std::vector<double> s_values;
  for (double s = 0.0; s < evaluation_horizon; s += Config_.FLAGS_trajectory_space_resolution)
  {
    s_values.emplace_back(s);
  }

  // Costs:
  // 1. Cost of lateral offsets
  // 2. Cost of lateral comfort
  // Lateral costs

  double lat_offset_cost = LatOffsetCost(lat_trajectory, s_values, cur_feature);

  double lat_comfort_cost = LatComfortCost(lon_trajectory, lat_trajectory);

  if (Config_.FLAGS_Plan4NGSIM_) {
    cur_feature.lon_objective_cost = lon_objective_cost;
    cur_feature.centripetal_acc_cost = centripetal_acc_cost;
    cur_feature.lon_collision_cost = lon_collision_cost;

    cur_feature.lat_offset_cost = lat_offset_cost;
    cur_feature.lat_comfort_cost = lat_comfort_cost;
    cur_feature.lon_comfort_cost = lon_jerk_cost;

    printf("The features : %f\n", lat_trajectory->Evaluate(0, 0.0));
    printf("lon_length : %f,  latoffset : %f, length_time : %f, target_speed %f\n", 
    cur_feature.length_s, cur_feature.lat_offset, cur_feature.length_time, cur_feature.target_speed);

    printf("lon_objective_cost : %f,  lon_comfort_cost : %f, lon_collision_cost : %f, lat_offset_cost %f, lat_comfort_cost %f, centripetal_acc_cost %f\n", 
    cur_feature.lon_objective_cost, cur_feature.lon_comfort_cost, cur_feature.lon_collision_cost, cur_feature.lat_offset_cost, cur_feature.lat_comfort_cost, cur_feature.speed_cost);
    {
      std::lock_guard<std::mutex> lock(features_mutex_);
      if (cur_feature.length_time == 8.0)
      traj_features.emplace_back(cur_feature);
    }
    

  }
  
  return lon_objective_cost * Config_.FLAGS_weight_lon_objective +
         lon_jerk_cost * Config_.FLAGS_weight_lon_jerk +
         lon_collision_cost * Config_.FLAGS_weight_lon_collision +
         centripetal_acc_cost * Config_.FLAGS_weight_centripetal_acceleration +
         lat_offset_cost * Config_.FLAGS_weight_lat_offset +
         lat_comfort_cost * Config_.FLAGS_weight_lat_comfort;
}

void TrajectoryEvaluator::Evaluate(const PlanningTarget &planning_target, const PtrTrajectory1d &lon_trajectory,
  const PtrTrajectory1d &lat_trajectory, const std::shared_ptr<ThreadPool> calc_pool) {
    double cost = Evaluate(planning_target, lon_trajectory, lat_trajectory);
    {
      std::lock_guard<std::mutex> lock(cost_queue_mutex_);
      cost_queue_.emplace(Trajectory1dPair(lon_trajectory, lat_trajectory), cost);
    }
};


// 1.LonObjectiveCost
double TrajectoryEvaluator::LonObjectiveCost(const std::shared_ptr<Curve1d> &lon_trajectory,
                                             const std::vector<double> ref_s_dots, TrajFeature& cur_feature) const
{
  // 获得轨迹长度
  double t_max = lon_trajectory->ParamLength();
  // 轨迹走过的 s 距离
  double dist_s =
      lon_trajectory->Evaluate(0, t_max) - lon_trajectory->Evaluate(0, 0.0);

  cur_feature.length_s = dist_s;
  cur_feature.length_time = t_max;
  cur_feature.target_speed = lon_trajectory->Evaluate(1, t_max);

  double speed_cost_sqr_sum = 0.0;
  double speed_cost_weight_sum = 0.0;
  for (size_t i = 0; i < ref_s_dots.size(); ++i)
  {
    // 当前t
    double t = static_cast<double>(i) * Config_.FLAGS_trajectory_time_resolution;
    // V_ref_t - V_evaluate_t
    double cost = ref_s_dots[i] - lon_trajectory->Evaluate(1, t);
    // sum_0_to_length(t^2*|V_ref_t - V_evaluate_t|)
    speed_cost_sqr_sum += t * t * std::fabs(cost);
    // sum_0_to_length(t^2)
    speed_cost_weight_sum += t * t;
  }
  // Cost_speed
  double speed_cost =
      speed_cost_sqr_sum / (speed_cost_weight_sum + Config_.FLAGS_numerical_epsilon);
  // Cost_dist
  double dist_travelled_cost = 1.0 / (1.0 + dist_s);
  // Cost_Object
  cur_feature.speed_cost = speed_cost;
  cur_feature.dist_travelled_cost = dist_travelled_cost;

  return (speed_cost * Config_.FLAGS_weight_target_speed +                          // 1.0
          dist_travelled_cost * Config_.FLAGS_weight_dist_travelled) /              // 10.0
         (Config_.FLAGS_weight_target_speed + Config_.FLAGS_weight_dist_travelled); // 1.0 + 10.0
}

// 2.LonComfortCost
double TrajectoryEvaluator::LonComfortCost (
    const PtrTrajectory1d &lon_trajectory) const
{
  double cost_sqr_sum = 0.0;
  double cost_abs_sum = 0.0;
  for (double t = 0.0; t < Config_.FLAGS_trajectory_time_length;
       t += Config_.FLAGS_trajectory_time_resolution)
  {
    // 每个时刻的jerk
    double jerk = lon_trajectory->Evaluate(3, t);
    // jerk_t/2
    double cost = jerk / Config_.FLAGS_longitudinal_jerk_upper_bound; // 2.0
    // sum_0_to_length(jerk_t/2)^2
    cost_sqr_sum += cost * cost;
    // sum_0_to_length(|jerk_t/2|)
    cost_abs_sum += std::fabs(cost);
  }
  // Cost_jerk
  return cost_sqr_sum / (cost_abs_sum + Config_.FLAGS_numerical_epsilon);
}

// 3.LonCollisionCost
// TODO(all): consider putting pointer of reference_line_info and frame
// while constructing trajectory evaluator
double TrajectoryEvaluator::LonCollisionCost(
    const PtrTrajectory1d &lon_trajectory) const
{
  double cost_sqr_sum = 0.0;
  double cost_abs_sum = 0.0;
  for (size_t i = 0; i < path_time_intervals_.size(); ++i)
  {
    // 获得当前时间点对应的t下 ，所有障碍物在ST图上存在的s范围
    const auto &pt_interval = path_time_intervals_[i];
    // 如果当前时间点内没有障碍物,就不进行当前时间点碰撞项的cost构建
    if (pt_interval.empty())
    {
      continue;
    }
    double t = static_cast<double>(i) * Config_.FLAGS_trajectory_time_resolution;
    // 当前时间点的s
    double traj_s = lon_trajectory->Evaluate(0, t);
    double sigma = Config_.FLAGS_lon_collision_cost_std; // 0.5
    // 遍历当前时间点下,所有障碍物(即对应的s_lower和s_upper)
    for (const auto &m : pt_interval)
    {
      double dist = 0.0;
      // 如果 当前障碍物的s_lower减去一个lon_collision_yield_buffer 大于 当前t对应的自车s
      if (traj_s < m.first - Config_.FLAGS_lon_collision_yield_buffer)
      { // 1.0
        // 当前障碍物的s_lower减去一个lon_collision_yield_buffer 与自车 的差值
        dist = m.first - Config_.FLAGS_lon_collision_yield_buffer - traj_s;
        // 如果 当前障碍物的s_upper加上一个lon_collision_overtake_buffer 小于 当前t对应的自车s
      }
      else if (traj_s > m.second + Config_.FLAGS_lon_collision_overtake_buffer)
      { // 5.0
        // 自车与 当前障碍物的s_upper加上一个lon_collision_overtake_buffer 的差值
        dist = traj_s - m.second - Config_.FLAGS_lon_collision_overtake_buffer;
      }
      // cost = e^(-d^2/2*sigma^2)
      // double cost = std::exp(-dist * dist / (2.0 * sigma * sigma));
      double cost = 1 - dist / Config_.FLAGS_speed_lon_decision_horizon;


      // sum_0_to_length(cost^2)
      cost_sqr_sum += cost * cost;
      // sum_0_to_length(cost)
      cost_abs_sum += cost;
    }
    // printf("\n");
  }
  // Cost_collision
  return cost_sqr_sum / (cost_abs_sum + Config_.FLAGS_numerical_epsilon);
}

// 4.CentripetalAccelerationCost:向心加速成本
double TrajectoryEvaluator::CentripetalAccelerationCost(
    const PtrTrajectory1d &lon_trajectory) const
{
  // Assumes the vehicle is not obviously deviate from the reference line.
  double centripetal_acc_sum = 0.0;
  double centripetal_acc_sqr_sum = 0.0;
  for (double t = 0.0; t < Config_.FLAGS_trajectory_time_length;
       t += Config_.FLAGS_trajectory_time_resolution)
  {
    double s = lon_trajectory->Evaluate(0, t);
    double v = lon_trajectory->Evaluate(1, t);
    ReferencePoint ref_point = PathMatcher::MatchToPath(s, reference_points_); //求匹配点

    // 向心加速度 = v^2/r, 由于kappa = 1/r, 所以有 向心加速度 = v^2*kappa
    double centripetal_acc = v * v * ref_point.kappa();
    // sum_0_to_length(|a_centr_t|)
    centripetal_acc_sum += std::fabs(centripetal_acc);
    // sum_0_to_length(a_centr_t^2)
    centripetal_acc_sqr_sum += centripetal_acc * centripetal_acc;
  }

  // Cost_CentriAcc
  return centripetal_acc_sqr_sum / (centripetal_acc_sum + Config_.FLAGS_numerical_epsilon);
}

// 1.LatOffsetCost
double TrajectoryEvaluator::LatOffsetCost(
    const PtrTrajectory1d &lat_trajectory,
    const std::vector<double> &s_values,
    TrajFeature& cur_feature) const
{
  // 当前位置(s = 0)对应的 l 值
  double lat_offset_start = lat_trajectory->Evaluate(0, 0.0);
  double cost_sqr_sum = 0.0;
  double cost_abs_sum = 0.0;
  
  cur_feature.lat_offset = lat_trajectory->Evaluate(0, s_values.back());
  for (const auto &s : s_values)
  {
    // 估计当前 s 对应的 l 值
    double lat_offset = lat_trajectory->Evaluate(0, s);
    // l_s/3
    double cost4center = std::fabs(lat_offset) / Config_.FLAGS_lat_offset_bound; // 3.0
    // double cost4changeline = std::abs(lat_offset - lat_offset_start) / Config_.FLAGS_default_reference_line_width;
    // double cost = (cost4center + cost4changeline) / 2.0;
    double cost = cost4center;//这里主要考虑的是，该成本函数驱动车辆向车道中心线靠拢，而舒适性指标驱动车辆保持车道
    // 如果当前s对应的横向偏移 与 起点的横向偏移 方向相反
    // sum_s_to_s_values((l_s/3)^2*w_s)
    cost_sqr_sum += cost * cost; // 1.0
    // sum_s_to_s_values(|l_s/3|*w_s)
    cost_abs_sum += std::fabs(cost); // 1,0

    // if (lat_offset * lat_offset_start < 0.0)
    // {
    //   // sum_s_to_s_values((l_s/3)^2*w_s)
    //   cost_sqr_sum += cost * cost * Config_.FLAGS_weight_opposite_side_offset; // 10.0
    //   // sum_s_to_s_values(|l_s/3|*w_s)
    //   cost_abs_sum += std::fabs(cost) * Config_.FLAGS_weight_opposite_side_offset; // 10.0
    // }
    // else
    // {
    //   // sum_s_to_s_values((l_s/3)^2*w_s)
    //   cost_sqr_sum += cost * cost * Config_.FLAGS_weight_same_side_offset; // 1.0
    //   // sum_s_to_s_values(|l_s/3|*w_s)
    //   cost_abs_sum += std::fabs(cost) * Config_.FLAGS_weight_same_side_offset; // 1,0
    // }
  }
  // Cost_LatOffsetCost
  return cost_sqr_sum / (cost_abs_sum + Config_.FLAGS_numerical_epsilon);
}

// 2.LatComfortCost
double TrajectoryEvaluator::LatComfortCost(const std::shared_ptr<Curve1d> &lon_trajectory,
                                           const std::shared_ptr<Curve1d> &lat_trajectory) const
{
  double max_cost = 0.0;
  for (double t = 0.0; t < Config_.FLAGS_trajectory_time_length; // 8.0
       t += Config_.FLAGS_trajectory_time_resolution)
  { // 0.1
    // 估计当前时间点对应的 s
    double s = lon_trajectory->Evaluate(0, t);
    // 估计当前时间点对应的 纵向v
    double s_dot = lon_trajectory->Evaluate(1, t);
    // 估计当前时间点对应的 纵向a
    double s_dotdot = lon_trajectory->Evaluate(2, t);

    // 当前时间点下, s与初始s的差值
    double relative_s = s - init_s_[0];
    // 这里的Evaluate为什么传入的是relative_s?
    // 答案: 因为横向轨迹是关于s的函数,即 l(s)=a0+a1*s+a2*s^2+a3*s^3+a4*s^4+a5*s^5
    // l_prime 即 l', 解释:https://www.zhihu.com/question/430355710/answer/1576049116
    double l_prime = lat_trajectory->Evaluate(1, relative_s);
    double l_primeprime = lat_trajectory->Evaluate(2, relative_s);
    double cost = l_primeprime * s_dot * s_dot + l_prime * s_dotdot;
    max_cost = std::max(max_cost, std::fabs(cost));
  }
  return max_cost;
}

bool TrajectoryEvaluator::fuzzy_within(const double v, const double lower, const double upper) const
{
  const double e = 1.0e-4;
  return v > lower - e && v < upper + e;
}

bool TrajectoryEvaluator::IsValidLongitudinalTrajectory(const Curve1d &lon_trajectory) const
{
  double t = 0.0;
  // std::cout << "lon_trajectory.ParamLength: " << lon_trajectory.ParamLength() << std::endl;
  // std::cout << "Config_.FLAGS_trajectory_time_resolution: " << Config_.FLAGS_trajectory_time_resolution << std::endl;
  // std::cout << "lon_trajectory.ParamLength: " << lon_trajectory.ParamLength() << std::endl;

  // std::cout << "Config_.FLAGS_speed_lower_bound: " << Config_.FLAGS_speed_lower_bound << std::endl;
  // std::cout << "Config_.FLAGS_speed_upper_bound: " << Config_.FLAGS_speed_upper_bound << std::endl;
  // std::cout << "Config_.FLAGS_longitudinal_acceleration_lower_bound: " << Config_.FLAGS_longitudinal_acceleration_lower_bound << std::endl;
  // std::cout << "Config_.FLAGS_longitudinal_acceleration_upper_bound: " << Config_.FLAGS_longitudinal_acceleration_upper_bound << std::endl;
  // std::cout << "Config_.FLAGS_longitudinal_jerk_lower_bound: " << Config_.FLAGS_longitudinal_jerk_lower_bound << std::endl;
  // std::cout << "Config_.FLAGS_longitudinal_jerk_upper_bound: " << Config_.FLAGS_longitudinal_jerk_upper_bound << std::endl;
  while (t < lon_trajectory.ParamLength())
  {
    double v = lon_trajectory.Evaluate(1, t); // evaluate_v
    // std::cout << "v: " << v << std::endl;
    if (!fuzzy_within(v, Config_.FLAGS_speed_lower_bound, Config_.FLAGS_speed_upper_bound))
    {
      return false;
    }
    double a = lon_trajectory.Evaluate(2, t); // evaluate_a
    // std::cout << "a: " << a << std::endl;
    if (!fuzzy_within(a, Config_.FLAGS_longitudinal_acceleration_lower_bound, Config_.FLAGS_longitudinal_acceleration_upper_bound))
    {
      return false;
    }
    double j = lon_trajectory.Evaluate(3, t); // evaluate_j
    // std::cout << "j: " << j <<std::endl;
    if (!fuzzy_within(j, Config_.FLAGS_longitudinal_jerk_lower_bound, Config_.FLAGS_longitudinal_jerk_upper_bound))
    {
      return false;
    }
    t += Config_.FLAGS_trajectory_time_resolution;
  }
  return true;
}

std::vector<double> TrajectoryEvaluator::ComputeLongitudinalGuideVelocity(const PlanningTarget &planning_target) const
{
  std::vector<double> reference_s_dot;
  double cruise_v = planning_target.cruise_speed();

  if (!planning_target.has_stop_point())
  {
    PiecewiseAccelerationTrajectory1d lon_traj(init_s_[0], cruise_v);

    lon_traj.AppendSegment(0.0, Config_.FLAGS_trajectory_time_length + Config_.FLAGS_numerical_epsilon);

    for (double t = 0.0; t < Config_.FLAGS_trajectory_time_length; t += Config_.FLAGS_trajectory_time_resolution)
    {
      reference_s_dot.emplace_back(lon_traj.Evaluate(1, t));
    }
  }
  else
  {
    double dist_s = planning_target.stop_point() - init_s_[0];
    if (dist_s < Config_.FLAGS_numerical_epsilon)
    {
      PiecewiseAccelerationTrajectory1d lon_traj(init_s_[0], 0.0);

      lon_traj.AppendSegment(0.0, Config_.FLAGS_trajectory_time_length + Config_.FLAGS_numerical_epsilon);

      for (double t = 0.0; t < Config_.FLAGS_trajectory_time_length; t += Config_.FLAGS_trajectory_time_resolution)
      {
        reference_s_dot.emplace_back(lon_traj.Evaluate(1, t));
      }
      return reference_s_dot;
    }

    double a_comfort = Config_.FLAGS_longitudinal_acceleration_upper_bound * Config_.FLAGS_comfort_acceleration_factor;
    double d_comfort = -Config_.FLAGS_longitudinal_acceleration_lower_bound * Config_.FLAGS_comfort_acceleration_factor;

    std::shared_ptr<Trajectory1d> lon_ref_trajectory = PiecewiseBrakingTrajectoryGenerator::Generate(
        planning_target.stop_point(), init_s_[0], planning_target.cruise_speed(), init_s_[1],
        a_comfort, d_comfort, Config_.FLAGS_trajectory_time_length + Config_.FLAGS_numerical_epsilon);

    for (double t = 0.0; t < Config_.FLAGS_trajectory_time_length; t += Config_.FLAGS_trajectory_time_resolution)
    {
      reference_s_dot.emplace_back(lon_ref_trajectory->Evaluate(1, t));
    }
  }
  return reference_s_dot;
}