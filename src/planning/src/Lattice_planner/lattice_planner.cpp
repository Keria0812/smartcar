#include "lattice_planner.h"

// #include <metux>

/*
1.将参考线转变为离散地图点（省去,因为我们的参考线是根据中心线生成的，本身点是离散的，不用再离散化）
2.计算参考线上初始规划点的匹配点（省去，因为我们将起点就作为了初始规划的起点，起点列入参考曲线）
3.根据匹配点计算Frenet帧的初始状态(省去，直接使用现在的Frenet框架试试)
4.解析决策，得到规划目标
5.分别生成纵向和横向一维轨迹束
6.评价：首先，根据动态约束条件对一维轨迹的可行性进行评价；其次，评估可行的纵向和横向轨迹对，并根据成本进行排序。
7.返回无碰撞的、符合条件的轨迹
*/

/*解析决策，得到规划目标(写在lattice_dynamic_routing.cpp文件中)*/
// (1).静态障碍物:
// (a).获取障碍物多边形的所有顶点（实际上雷达是很难照射到完整障碍物的，只能探测到部分面）
// (b).老方法—把所有点映射到参考线上，获得s和L，即基本的Frenet坐标，此时已经可以遍历最大最小值，形成对应的SL图了
// (c).ST图
//(2).动态障碍物
// (a).ST图


  std::vector<PathPoint> ToDiscretizedReferenceLine(
      const std::vector<ReferencePoint> &ref_points)
  {
    double s = 0.0;
    std::vector<PathPoint> path_points;
    for (const auto &ref_point : ref_points)
    {
      PathPoint path_point;
      path_point.set_x(ref_point.x_);
      path_point.set_y(ref_point.y_);
      path_point.set_theta(ref_point.heading());
      path_point.set_kappa(ref_point.kappa());
      path_point.set_dkappa(ref_point.dkappa());

      if (!path_points.empty())
      {
        double dx = path_point.x - path_points.back().x;
        double dy = path_point.y - path_points.back().y;
        s += std::sqrt(dx * dx + dy * dy);
      }
      path_point.set_s(s);
      path_points.push_back(std::move(path_point));
    }
    return path_points;
  }

  void LatticePlanner::ComputeInitFrenetState(const ReferencePoint &matched_point,
                              const TrajectoryPoint &cartesian_state,
                              std::array<double, 3> *ptr_s,
                              std::array<double, 3> *ptr_d)
  {

    CartesianFrenetConverter::cartesian_to_frenet(
        matched_point.accumulated_s_, matched_point.x_, matched_point.y_,
        matched_point.heading_, matched_point.kappa_, matched_point.dkappa_,
        cartesian_state.path_point().x, cartesian_state.path_point().y,
        cartesian_state.v, cartesian_state.a,
        cartesian_state.path_point().theta,
        cartesian_state.path_point().kappa, ptr_s, ptr_d);
  }

/*轨迹的生成规划*/
DiscretizedTrajectory LatticePlanner::LatticePlan(
    const TrajectoryPoint &planning_init_point,
    const PlanningTarget &planning_target,
    const std::vector<const Obstacle *> &obstacles,
    const std::vector<double> &accumulated_s,
    const std::vector<ReferencePoint> &reference_points, const bool &lateral_optimization,
    const double &init_relative_time, const double lon_decision_horizon,
    std::vector<DiscretizedTrajectory> &feasible_paths,
    DiscretizedTrajectory &ego_human_path,
    std::vector<TrajFeature> &features,
    std::shared_ptr<ThreadPool> calc_pool,
    std::vector<DiscretizedTrajectory> &cur_sl_graph,
    std::vector<size_t> &analysis_data
    )
{
  feasible_paths.resize(0);
  int cout_path = 0;
  int num_path = 0;
  DiscretizedTrajectory Optim_trajectory;
  auto combine_start =  std::chrono::system_clock::now();

  // 1. compute the matched point of the init planning point on the reference line.
  ReferencePoint matched_point = PathMatcher::MatchToPath(reference_points, planning_init_point.path_point().x,
                                                          planning_init_point.path_point().y);

  // 2. according to the matched point, compute the init state in Frenet frame.
  std::array<double, 3> init_s;
  std::array<double, 3> init_d;
  ComputeInitFrenetState(matched_point, planning_init_point, &init_s, &init_d);
  std::cout << "init_s: " << init_s[0] << std::endl;
  // std::cout << "init_sd: " << init_s[1] << std::endl;
  // std::cout << "init_sdd: " << init_s[2] << std::endl;
  std::cout << "init_l: " << init_d[0] << std::endl;
  // std::cout << "init_ld: " << init_d[1] << std::endl;
  // std::cout << "init_ldd: " << init_d[2] << std::endl;

  //与Apollo不同，我们的前探距离不加上init_s[0]，因为我们的仿真的参考线不长
  auto ptr_path_time_graph = std::make_shared<PathTimeGraph>(obstacles, reference_points, init_s[0],
                                                             init_s[0] + lon_decision_horizon, //前瞻多少m lon_decision_horizon
                                                             0.0, Config_.FLAGS_trajectory_time_length, init_d);
  // cur_sl_graph
  auto ptr_reference_line = std::make_shared<std::vector<PathPoint>>(ToDiscretizedReferenceLine(reference_points));
  auto ptr_prediction_querier = std::make_shared<PredictionQuerier>(obstacles, ptr_reference_line);

  // 3.生成纵向和横向轨迹
  Trajectory1dGenerator trajectory1d_generator(init_s, init_d, ptr_path_time_graph, ptr_prediction_querier);
  std::vector<std::shared_ptr<Curve1d>> lon_trajectory1d_bundle;
  std::vector<std::shared_ptr<Curve1d>> lat_trajectory1d_bundle;
  trajectory1d_generator.GenerateTrajectoryBundles(planning_target, &lon_trajectory1d_bundle, &lat_trajectory1d_bundle);
  //打印轨迹数
  std::cout << "lon_trajectory1d_bundle:" << lon_trajectory1d_bundle.size() << "\n";
  std::cout << "lat_trajectory1d_bundle:" << lat_trajectory1d_bundle.size() << "\n";
  
  // 4.计算每条轨迹的代价,并得出优先级队列
  TrajectoryEvaluator trajectory_evaluator(planning_target, lon_trajectory1d_bundle, lat_trajectory1d_bundle,
                                           init_s, ptr_path_time_graph, reference_points,calc_pool);
  
std::chrono::duration<double> combine_cost_time = std::chrono::system_clock::now() - combine_start;
  std::cout << "combine_cost_time: " << combine_cost_time.count() * 1000 << " ms." << std::endl;
  // 5.轨迹拼接和最后的筛选
  std::cout << "num_of_trajectory_pairs: " << trajectory_evaluator.num_of_trajectory_pairs() << std::endl;
  num_path = trajectory_evaluator.num_of_trajectory_pairs();
  if (Config_.FLAGS_Plan4NGSIM_){
    int cur_index = (int)(ego_human_path.back().kappa);
    // ·Evaluate(const PlanningTarget &planning_target,
    //                                    const PtrTrajectory1d &lon_trajectory,
    //                                    const PtrTrajectory1d &lat_trajectory)
    if (cur_index < ego_human_path.size() - 80)
    {
        std::array<double, 3> end_s_state = {ego_human_path[cur_index + 80].s - ego_human_path[cur_index].s, ego_human_path[cur_index + 80].v};
        std::pair<std::array<double, 3>, double> Con_s = {end_s_state, 8.0};

        std::array<double, 3> end_d_state = {ego_human_path[cur_index + 80].d, 0, 0.0};
      
        std::pair<std::array<double, 3>, double> Con_d = {end_d_state,fabs( ego_human_path[cur_index + 80].x - ego_human_path[cur_index].x)};
        //   end_s_conditions.emplace_back(end_state, t);
        auto ptr_trajectory1d_lat = std::make_shared<LatticeTrajectory1d>(std::shared_ptr<Curve1d>(
                  new QuinticPolynomialCurve1d(trajectory1d_generator.init_lat_state_, Con_d.first, Con_d.second)));
              ptr_trajectory1d_lat->set_target_position(Con_d.first[0]);
              ptr_trajectory1d_lat->set_target_velocity(Con_d.first[1]);
              ptr_trajectory1d_lat->set_target_time(Con_d.second);

        auto ptr_trajectory1d_lon = std::make_shared<LatticeTrajectory1d>(std::shared_ptr<Curve1d>(
                  new QuinticPolynomialCurve1d(trajectory1d_generator.init_lon_state_, Con_s.first, Con_s.second)));
              ptr_trajectory1d_lon->set_target_position(Con_s.first[0]);
              ptr_trajectory1d_lon->set_target_velocity(Con_s.first[1]);
        ptr_trajectory1d_lon->set_target_time(Con_s.second);
        auto combined_trajectory = trajectorycombiner.Combine(accumulated_s, *ptr_trajectory1d_lon, *ptr_trajectory1d_lat,
                                                          reference_points, init_relative_time);
        trajectory_evaluator.Evaluate(planning_target, ptr_trajectory1d_lon, ptr_trajectory1d_lat);  
        if (init_d[0] <  (6 / 3.281) &&  init_d[0] > -(6 / 3.281))                                     
        feasible_paths.push_back(combined_trajectory);
      }
    for (size_t fi = 0; fi < trajectory_evaluator.traj_features.size(); fi++) {
        if (init_d[0] > (6 / 3.281))
          trajectory_evaluator.traj_features[fi].lat_offset += 12 / 3.281;
        else if ((init_d[0] < -(6 / 3.281)))
          trajectory_evaluator.traj_features[fi].lat_offset -= 12 / 3.281;
        if (cur_index < 0 || cur_index >= ego_human_path.size() - 80) {
          fprintf(stderr, "The ego_human_path Error !\n");
        }
        // trajectory_evaluator.traj_features[fi].human_likeness =pow(pow((ego_human_path[cur_index + 80].d -trajectory_evaluator.traj_features[fi].lat_offset), 2) 
        //                                                         +pow((ego_human_path[cur_index + 80].s - ego_human_path[cur_index].s - trajectory_evaluator.traj_features[fi].length_s), 2 )
        //                                                         , 0.5);
        trajectory_evaluator.traj_features[fi].human_likeness = fabs(ego_human_path[cur_index + 80].d -trajectory_evaluator.traj_features[fi].lat_offset);
        // printf("human_like %f %f %f %f %f\n", trajectory_evaluator.traj_features[fi].human_likeness, trajectory_evaluator.traj_features[fi].lon_objective_cost, 
        // trajectory_evaluator.traj_features[fi].length_s, ego_human_path[cur_index + 80].s, ego_human_path[cur_index].s);
    }

    swap(features, trajectory_evaluator.traj_features);
    trajectory_evaluator.traj_features.clear();
  }
  // State end_state = {s, v, 0.0};
  
  //四
  // auto ptr_trajectory1d =
  //           std::make_shared<LatticeTrajectory1d>(std::shared_ptr<Curve1d>(new QuarticPolynomialCurve1d(
  //               init_state, {end_condition.first[1], end_condition.first[2]}, end_condition.second)));

  //       ptr_trajectory1d->set_target_velocity(end_condition.first[1]);
  //       ptr_trajectory1d->set_target_time(end_condition.second);
  //       ptr_trajectory_bundle->push_back(ptr_trajectory1d);
  if (num_path == 0) return Optim_trajectory;

  //       
  
  //   for (auto &res : results) res.get();//判断线程是否运行完毕

  //不训练的时候才拼接轨迹
  std::vector< std::future<void> > results;
  std::mutex feasible_paths_mutex; 
        CollisionChecker collision_checker(obstacles, init_s[0], init_d[0], reference_points, ptr_path_time_graph);
  size_t all_traj_pairs_num = trajectory_evaluator.num_of_trajectory_pairs();
  size_t in_VALID_num = 0;
  if (!Config_.FLAGS_Plan4NGSIM_)
  while (trajectory_evaluator.has_more_trajectory_pairs())
  {
    if (cout_path >= 40) {
      for (auto &res : results) res.get();
      results.clear();
      // if (feasible_paths.size() >= 80){
      //   break;
      // } else {
      //   cout_path = 0;
      // }
    }
    cout_path++;
    double trajectory_pair_cost = trajectory_evaluator.top_trajectory_pair_cost();
    auto trajectory_pair = trajectory_evaluator.next_top_trajectory_pair();
    // combine two 1d trajectories to one 2d trajectory
    results.emplace_back(calc_pool->enqueue([trajectory_pair_cost, trajectory_pair, accumulated_s 
                          ,&reference_points, &lateral_optimization, init_relative_time, init_s, 
                          init_d, ptr_path_time_graph, &obstacles, &feasible_paths, &feasible_paths_mutex,
                          &collision_checker,
                          &in_VALID_num,
                           &cout_path,this] {
  //         Evaluate(planning_target, lon_trajectory, lat_trajectory, calc_pool);
      DiscretizedTrajectory combined_trajectory = trajectorycombiner.Combine(accumulated_s, *trajectory_pair.first, *trajectory_pair.second,
                                                            reference_points, init_relative_time);

      combined_trajectory.cost = trajectory_pair_cost;
      // std::cout << "combined_trajectory_size: " << combined_trajectory.size() << std::endl;
      // 采样时候才调用，二次规划不用
      if (lateral_optimization == false)
      {
        // std::cout << "select combined_trajectory" << std::endl;
        // check longitudinal and lateral acceleration
        // considering trajectory curvatures
        auto result = constraintchecker_.ValidTrajectory(combined_trajectory);

        if (result != ConstraintChecker::Result::VALID)
        {
          in_VALID_num++;
          // std::cout << "ssssssssssssssssssssssssssssssssssss" << std::endl;
          // std::cout << result << std::endl;
          switch (result)
          {
          case ConstraintChecker::Result::LON_VELOCITY_OUT_OF_BOUND: {
            // printf(" lon Vel \n");
            break;
          }
          case ConstraintChecker::Result::LON_ACCELERATION_OUT_OF_BOUND: {
            // printf(" lon acc \n");

            break;
          }
            
          case ConstraintChecker::Result::LON_JERK_OUT_OF_BOUND: {
            // printf(" lon jerk \n");

            break;
          }
      
          case ConstraintChecker::Result::CURVATURE_OUT_OF_BOUND:{
            // printf(" lat kappa \n");

            break;
          }
        
          case ConstraintChecker::Result::LAT_ACCELERATION_OUT_OF_BOUND:{
            // printf(" lat acc \n");

            break;
          }
          case ConstraintChecker::Result::LAT_JERK_OUT_OF_BOUND:{
            // printf(" lat acc \n");

            break;
          }
          default:
            // Intentional empty
            break;
          }
          return;
        }
        // Get instance of collision checker and constraint checker
        // printf("%f sssssssssssss  %ld\n", init_d[0], trajectory_evaluator.traj_features.size());


        //碰撞检测
        if (collision_checker.InCollision(combined_trajectory))
        {
          // std::cout << "has collision" << std::endl;
          // continue;
          return;
        }
        {
          std::lock_guard<std::mutex> lock(feasible_paths_mutex);
          feasible_paths.emplace_back( combined_trajectory);
          // if (feasible_paths.size() < 80) {
          //   cout_path++;
          // }
        }
        // if (feasible_paths.size() >= 80) {
        //     // continue;
        //     break;
        // }
        // else {
        //   cout_path++;
        //   continue;
        // }      
        // std::cout << "combined_trajectory_size: " << combined_trajectory.size() << std::endl;
      }
    // Optim_trajectory = std::move(combined_trajectory);
    // break;
    }));

  }
  for (auto &res : results) res.get();
  
  analysis_data.emplace_back(all_traj_pairs_num);
  analysis_data.emplace_back(in_VALID_num);
  analysis_data.emplace_back(feasible_paths.size());
    std::cout << "combined_trajectory_size: " << feasible_paths.size() << std::endl;
  if (feasible_paths.size() <= 0) {
    ROS_WARN("The Planning Error!!!");
    return Optim_trajectory;
  }
  return feasible_paths.front();

}


DiscretizedTrajectory LatticePlanner::LatticePlanbyMySampleModel(
    const TrajectoryPoint &planning_init_point,
    const PlanningTarget &planning_target,
    const std::vector<const Obstacle *> &obstacles,
    const std::vector<double> &accumulated_s,
    const std::vector<ReferencePoint> &reference_points, const bool &lateral_optimization,
    const double &init_relative_time, const double lon_decision_horizon,
    std::vector<DiscretizedTrajectory> &feasible_paths,
    DiscretizedTrajectory &learning_sample_points,
    std::vector<TrajFeature> &features,
    std::shared_ptr<ThreadPool> calc_pool,
    std::vector<DiscretizedTrajectory> &cur_sl_graph,
    std::vector<size_t> &analysis_data
    ) {
  feasible_paths.resize(0);
  int cout_path = 0;
  int num_path = 0;
  DiscretizedTrajectory Optim_trajectory;
  auto combine_start =  std::chrono::system_clock::now();

  // 1. compute the matched point of the init planning point on the reference line.
  ReferencePoint matched_point = PathMatcher::MatchToPath(reference_points, planning_init_point.path_point().x,
                                                          planning_init_point.path_point().y);

  // 2. according to the matched point, compute the init state in Frenet frame.
  std::array<double, 3> init_s;
  std::array<double, 3> init_d;
  ComputeInitFrenetState(matched_point, planning_init_point, &init_s, &init_d);
  std::cout << "init_s: " << init_s[0] << std::endl;
  // std::cout << "init_sd: " << init_s[1] << std::endl;
  // std::cout << "init_sdd: " << init_s[2] << std::endl;
  std::cout << "init_l: " << init_d[0] << std::endl;
  // std::cout << "init_ld: " << init_d[1] << std::endl;
  // std::cout << "init_ldd: " << init_d[2] << std::endl;


  //与Apollo不同，我们的前探距离不加上init_s[0]，因为我们的仿真的参考线不长
  auto ptr_path_time_graph = std::make_shared<PathTimeGraph>(obstacles, reference_points, init_s[0],
                                                             init_s[0] + lon_decision_horizon, //前瞻多少m lon_decision_horizon
                                                             0.0, Config_.FLAGS_trajectory_time_length, init_d);
  // cur_sl_graph
  auto ptr_reference_line = std::make_shared<std::vector<PathPoint>>(ToDiscretizedReferenceLine(reference_points));
  auto ptr_prediction_querier = std::make_shared<PredictionQuerier>(obstacles, ptr_reference_line);
  std::vector<std::pair<PtrTrajectory1d, PtrTrajectory1d>> pair_trajectories;
  Trajectory1dGenerator trajectory1d_generator(init_s, init_d, ptr_path_time_graph, ptr_prediction_querier);

  this->SamplepointsFilter(learning_sample_points);
  for (auto &sample_point : sample_pointsbylearing_)
  {
    std::array<double, 3> end_s_state = {sample_point.s, sample_point.v};
    std::pair<std::array<double, 3>, double> Con_s = {end_s_state, sample_point.relative_time};

    std::array<double, 3> end_d_state = {sample_point.d, 0, 0.0};
  
    std::pair<std::array<double, 3>, double> Con_d = {end_d_state,sample_point.s};
    //   end_s_conditions.emplace_back(end_state, t);
    auto ptr_trajectory1d_lat = std::make_shared<LatticeTrajectory1d>(std::shared_ptr<Curve1d>(
              new QuinticPolynomialCurve1d(trajectory1d_generator.init_lat_state_, Con_d.first, Con_d.second)));
          ptr_trajectory1d_lat->set_target_position(Con_d.first[0]);
          ptr_trajectory1d_lat->set_target_velocity(Con_d.first[1]);
          ptr_trajectory1d_lat->set_target_time(Con_d.second);

    auto ptr_trajectory1d_lon = std::make_shared<LatticeTrajectory1d>(std::shared_ptr<Curve1d>(
              new QuinticPolynomialCurve1d(trajectory1d_generator.init_lon_state_, Con_s.first, Con_s.second)));
          ptr_trajectory1d_lon->set_target_position(Con_s.first[0]);
          ptr_trajectory1d_lon->set_target_velocity(Con_s.first[1]);
    ptr_trajectory1d_lon->set_target_time(Con_s.second);
    pair_trajectories.emplace_back(make_pair(ptr_trajectory1d_lon, ptr_trajectory1d_lat));
      // auto combined_trajectory = trajectorycombiner.Combine(accumulated_s, *ptr_trajectory1d_lon, *ptr_trajectory1d_lat,
    //                                 reference_points, init_relative_time);
    // trajectory_evaluator.Evaluate(planning_target, ptr_trajectory1d_lon, ptr_trajectory1d_lat);
  }

  

  // // 3.生成纵向和横向轨迹
  // Trajectory1dGenerator trajectory1d_generator(init_s, init_d, ptr_path_time_graph, ptr_prediction_querier);
  // std::vector<std::shared_ptr<Curve1d>> lon_trajectory1d_bundle;
  // std::vector<std::shared_ptr<Curve1d>> lat_trajectory1d_bundle;
  // trajectory1d_generator.GenerateTrajectoryBundles(planning_target, &lon_trajectory1d_bundle, &lat_trajectory1d_bundle);
  // //打印轨迹数
  // std::cout << "lon_trajectory1d_bundle:" << lon_trajectory1d_bundle.size() << "\n";
  // std::cout << "lat_trajectory1d_bundle:" << lat_trajectory1d_bundle.size() << "\n";
  
  // 4.计算每条轨迹的代价,并得出优先级队列
  TrajectoryEvaluator trajectory_evaluator(planning_target, pair_trajectories,
                                           init_s, ptr_path_time_graph, reference_points,calc_pool);
  
  std::chrono::duration<double> combine_cost_time = std::chrono::system_clock::now() - combine_start;
  std::cout << "combine_cost_time: " << combine_cost_time.count() * 1000 << " ms." << std::endl;
  // 5.轨迹拼接和最后的筛选
  std::cout << "num_of_trajectory_pairs: " << trajectory_evaluator.num_of_trajectory_pairs() << std::endl;
  num_path = trajectory_evaluator.num_of_trajectory_pairs();
 
  
  // //四
  // // auto ptr_trajectory1d =
  // //           std::make_shared<LatticeTrajectory1d>(std::shared_ptr<Curve1d>(new QuarticPolynomialCurve1d(
  // //               init_state, {end_condition.first[1], end_condition.first[2]}, end_condition.second)));

  // //       ptr_trajectory1d->set_target_velocity(end_condition.first[1]);
  // //       ptr_trajectory1d->set_target_time(end_condition.second);
  // //       ptr_trajectory_bundle->push_back(ptr_trajectory1d);
  // if (num_path == 0) return Optim_trajectory;

  // //       
  
    // for (auto &res : results) res.get();//判断线程是否运行完毕

  // //不训练的时候才拼接轨迹
  std::vector< std::future<void> > results;
  std::mutex feasible_paths_mutex; 
  CollisionChecker collision_checker(obstacles, init_s[0], init_d[0], reference_points, ptr_path_time_graph);

  size_t all_traj_pairs_num = trajectory_evaluator.num_of_trajectory_pairs();
  size_t in_VALID_num = 0;
  
  // if (!Config_.FLAGS_Plan4NGSIM_)
  while (trajectory_evaluator.has_more_trajectory_pairs())
  {
    if (cout_path >= 40) {
      for (auto &res : results) res.get();
      results.clear();
      // if (feasible_paths.size() >= 80){
      //   break;
      // } else {
      //   cout_path = 0;
      // }
    }
    cout_path++;
    double trajectory_pair_cost = trajectory_evaluator.top_trajectory_pair_cost();
    auto trajectory_pair = trajectory_evaluator.next_top_trajectory_pair();
    // combine two 1d trajectories to one 2d trajectory
    results.emplace_back(calc_pool->enqueue([trajectory_pair_cost, trajectory_pair, accumulated_s 
                          ,&reference_points, &lateral_optimization, init_relative_time, init_s, 
                          init_d, ptr_path_time_graph, &obstacles, &feasible_paths, &feasible_paths_mutex,
                          &collision_checker,
                          &in_VALID_num,
                           &cout_path,this] {
  //         Evaluate(planning_target, lon_trajectory, lat_trajectory, calc_pool);
      DiscretizedTrajectory combined_trajectory = trajectorycombiner.Combine(accumulated_s, *trajectory_pair.first, *trajectory_pair.second,
                                                            reference_points, init_relative_time);

      combined_trajectory.cost = trajectory_pair_cost;
      // std::cout << "combined_trajectory_size: " << combined_trajectory.size() << std::endl;
      // 采样时候才调用，二次规划不用
      if (lateral_optimization == false)
      {
        // std::cout << "select combined_trajectory" << std::endl;
        // check longitudinal and lateral acceleration
        // considering trajectory curvatures
        auto result = constraintchecker_.ValidTrajectory(combined_trajectory);

        if (result != ConstraintChecker::Result::VALID)
        { 
          in_VALID_num++;
          // std::cout << "ssssssssssssssssssssssssssssssssssss" << std::endl;
          // std::cout << result << std::endl;
          switch (result)
          {
          case ConstraintChecker::Result::LON_VELOCITY_OUT_OF_BOUND: {
            // printf(" lon Vel \n");
            break;
          }
          case ConstraintChecker::Result::LON_ACCELERATION_OUT_OF_BOUND: {
            // printf(" lon acc \n");

            break;
          }
            
          case ConstraintChecker::Result::LON_JERK_OUT_OF_BOUND: {
            // printf(" lon jerk \n");

            break;
          }
      
          case ConstraintChecker::Result::CURVATURE_OUT_OF_BOUND:{
            // printf(" lat kappa \n");

            break;
          }
        
          case ConstraintChecker::Result::LAT_ACCELERATION_OUT_OF_BOUND:{
            // printf(" lat acc \n");

            break;
          }
          case ConstraintChecker::Result::LAT_JERK_OUT_OF_BOUND:{
            // printf(" lat acc \n");

            break;
          }
          default:
            // Intentional empty
            break;
          }
          return;
        }
        // // Get instance of collision checker and constraint checker
        // // printf("%f sssssssssssss  %ld\n", init_d[0], trajectory_evaluator.traj_features.size());


        //碰撞检测
        if (collision_checker.InCollision(combined_trajectory))
        {
          // std::cout << "has collision" << std::endl;
          // continue;
          return;
        }
        {
          std::lock_guard<std::mutex> lock(feasible_paths_mutex);
          feasible_paths.emplace_back( combined_trajectory);
          if (feasible_paths.size() < 80) {
            cout_path++;
          }
        }
        // if (feasible_paths.size() >= 80) {
        //     // continue;
        //     break;
        // }
        // else {
        //   cout_path++;
        //   continue;
        // }      
        // std::cout << "combined_trajectory_size: " << combined_trajectory.size() << std::endl;
      }
    // Optim_trajectory = std::move(combined_trajectory);
    // break;
    }));

  }
  for (auto &res : results) res.get();
  
  analysis_data.emplace_back(all_traj_pairs_num);
  analysis_data.emplace_back(in_VALID_num);
  analysis_data.emplace_back(feasible_paths.size());
  std::cout << "combined_trajectory_size: " << feasible_paths.size() << std::endl;
  if (feasible_paths.size() <= 0) {
    ROS_WARN("The Planning Error!!!");
    return Optim_trajectory;
  }
  

  sample_pointsbylearing_.clear();
  return feasible_paths.front();

};


void LatticePlanner::SamplepointsFilter(DiscretizedTrajectory &learning_sample_points) {
    double lane_width = 12 / 3.821;
    double length_step = 1.0;
    double width_step = 0.1;
    double V_step = 0.25;
    double V_length = 30.0;
    double lane_length = 200.0;
    size_t grid_lon_size = size_t(lane_length / length_step);
    size_t grid_lat_size = size_t(lane_width * 3 / width_step);
    size_t grid_time_size = 8;
    size_t grid_vel_size = size_t(V_length / V_step);
    std::vector<std::vector<std::vector<std::vector<short>>>> isGet(grid_vel_size,std::vector<std::vector<std::vector<short>>>(grid_time_size, std::vector<std::vector<short>>
    (grid_lon_size, std::vector<short>(grid_lat_size, 0))));
    // DiscretizedTrajectory sample_pointsbylearing_;
    for (size_t i = 0; i < learning_sample_points.size(); i++) {
        // 根据网格粒度筛选点
        size_t lon_index = size_t(learning_sample_points[i].x / length_step);
        size_t lat_index = size_t(learning_sample_points[i].y + 1.5 *lane_width  / width_step);
        size_t time_index = size_t(learning_sample_points[i].relative_time - 1.0);
        size_t vel_index = size_t(learning_sample_points[i].v / V_step);
        if (lon_index >= grid_lon_size || lat_index >= grid_lat_size || time_index >=grid_time_size || vel_index>= grid_vel_size) continue;
        if (isGet[vel_index][time_index][lon_index][lat_index] == 0) {
            isGet[vel_index][time_index][lon_index][lat_index] = 1;  // 标记该点已经被选择
            TrajectoryPoint tmp;
            tmp = learning_sample_points[i];

            // tmp.s = learning_sample_points[i].s;
            // tmp.d = learning_sample_points[i].d;
            // tmp.x = learning_sample_points[i].x;
            // tmp.y = learning_sample_points[i].y;
            // tmp.v = learning_sample_points[i].v;
            sample_pointsbylearing_.emplace_back(tmp);
        }
    }

    // 将筛选后的点存入sample_pointsbylearing_
    // ...
}
