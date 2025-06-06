#include "speed_limit_decider.h"
#include <limits>
#include "math_utils.h"

SpeedLimitDecider::SpeedLimitDecider(const SL_Boundary &adc_sl_boundary,
                                     const ReferenceLine &reference_line,
                                     const PathData &path_data)
    : adc_sl_boundary_(adc_sl_boundary),
      reference_line_(reference_line),
      path_data_(path_data)
{
}

void SpeedLimitDecider::GetAvgKappa(const std::vector<PathPoint> &path_points,
                                    std::vector<double> *kappa) const
{
    // CHECK_NOTNULL(kappa);
    const int kHalfNumPoints = Config_.num_points_to_avg_kappa / 2;
    //CHECK_GT(kHalfNumPoints, 0);
    kappa->clear();
    kappa->resize(path_points.size());
    double sum = 0.0;
    int start = 0;
    int end = 0;
    while (end < static_cast<int>(path_points.size()) &&
           end - start < kHalfNumPoints + 1)
    {
        sum += path_points[end].kappa;
        ++end;
    }

    int iter = 0;
    while (iter < static_cast<int>(path_points.size()))
    {
        kappa->at(iter) = sum / (end - start);
        if (start < iter - kHalfNumPoints)
        {
            sum -= path_points[start].kappa;
            ++start;
        }
        if (end < static_cast<int>(path_points.size()))
        {
            sum += path_points[end].kappa;
            ++end;
        }
        ++iter;
    }
}

void SpeedLimitDecider::GetSpeedLimits(
    const std::vector<const Obstacle *> &obstacles,
    planning::SpeedLimit *const speed_limit_data) const
{
    // CHECK_NOTNULL(speed_limit_data);

    std::vector<double> avg_kappa;
    GetAvgKappa(path_data_.discretized_path(), &avg_kappa);
    const auto &discretized_path = path_data_.discretized_path();
    const auto &frenet_path = path_data_.frenet_frame_path();
    for (uint32_t i = 0; i < discretized_path.size(); ++i)
    {
        const double path_s = discretized_path.at(i).s;
        const double frenet_point_s = frenet_path.at(i).s;
        if (frenet_point_s > reference_line_.Length())
        {
            // AWARN << "path length [" << frenet_point_s
            //       << "] is LARGER than reference_line_ length ["
            //       << reference_line_.Length() << "]. Please debug before proceeding.";
            break;
        }

        // (1) speed limit from map, 比如道路限速
        // double speed_limit_on_reference_line =
        //     reference_line_.GetSpeedLimitFromS(frenet_point_s);
        double speed_limit_on_reference_line = Config_.planning_upper_speed_limit;

        // (2) speed limit from path curvature
        //  -- 2.1: limit by centripetal force (acceleration)
        const double centri_acc_speed_limit =
            std::sqrt(GetCentricAccLimit(std::fabs(avg_kappa[i])) /
                      std::fmax(std::fabs(avg_kappa[i]), Config_.minimal_kappa));

        // -- 2.2: limit by centripetal jerk
        double centri_jerk_speed_limit = std::numeric_limits<double>::max();
        if (i + 1 < discretized_path.size())
        {
            const double ds =
                discretized_path.at(i + 1).s - discretized_path.at(i).s;
            // DCHECK_GE(ds, 0.0);
            const double kEpsilon = 1e-9;
            const double centri_jerk =
                std::fabs(avg_kappa[i + 1] - avg_kappa[i]) / (ds + kEpsilon);
            centri_jerk_speed_limit = std::fmax(
                10.0, Config_.centri_jerk_speed_coeff / centri_jerk);
        }

        // (3) speed limit from nudge obstacles
        double nudge_obstacle_speed_limit = std::numeric_limits<double>::max();
        for (const auto *const_obstacle : obstacles)
        {
            if (const_obstacle->IsVirtual())
            {
                continue;
            }
            if (!const_obstacle->LateralDecision().has_nudge())
            {
                continue;
            }

            /* ref line:
       * -------------------------------
       *    start_s   end_s
       * ------|  adc   |---------------
       * ------------|  obstacle |------
       */
            if (frenet_point_s + Config_.front_edge_to_center < const_obstacle->PerceptionSLBoundary().start_s_ ||
                frenet_point_s - Config_.back_edge_to_center > const_obstacle->PerceptionSLBoundary().end_s_)
            {
                continue;
            }
            constexpr double kRange = 1.0; // meters
            const auto &nudge = const_obstacle->LateralDecision().nudge();

            // Please notice the differences between adc_l and frenet_point_l
            const double frenet_point_l = frenet_path.at(i).d;

            // obstacle is on the right of ego vehicle (at path point i)
            bool is_close_on_left =
                (nudge.type == ObjectNudge::Type::LEFT_NUDGE) &&
                (frenet_point_l - Config_.right_edge_to_center - kRange <
                 const_obstacle->PerceptionSLBoundary().end_l_);

            // obstacle is on the left of ego vehicle (at path point i)
            bool is_close_on_right =
                (nudge.type == ObjectNudge::Type::RIGHT_NUDGE) &&
                (const_obstacle->PerceptionSLBoundary().start_l_ - kRange <
                 frenet_point_l + Config_.left_edge_to_center);

            if (is_close_on_left || is_close_on_right)
            {
                double nudge_speed_ratio = 1.0;
                if (const_obstacle->IsStatic())
                {
                    nudge_speed_ratio = Config_.static_obs_nudge_speed_ratio;
                }
                else
                {
                    nudge_speed_ratio = Config_.dynamic_obs_nudge_speed_ratio;
                }
                nudge_obstacle_speed_limit =
                    nudge_speed_ratio * speed_limit_on_reference_line;
                break;
            }
        }

        double curr_speed_limit = 0.0;
        if (Config_.FLAGS_enable_nudge_slowdown)
        {
            curr_speed_limit =
                std::fmax(Config_.lowest_speed,
                          common::math::MinElement(std::vector<double>{
                              speed_limit_on_reference_line, centri_acc_speed_limit,
                              centri_jerk_speed_limit, nudge_obstacle_speed_limit}));
        }
        else
        {
            curr_speed_limit =
                std::fmax(Config_.lowest_speed,
                          common::math::MinElement(std::vector<double>{
                              speed_limit_on_reference_line, centri_acc_speed_limit,
                              centri_jerk_speed_limit}));
        }

        speed_limit_data->AppendSpeedLimit(path_s, curr_speed_limit);
    }
}

double SpeedLimitDecider::GetCentricAccLimit(const double kappa) const
{
    // this function uses a linear model with upper and lower bound to determine
    // centric acceleration limit

    // suppose acc = k1 * v + k2
    // consider acc = v ^ 2 * kappa
    // we determine acc by the two functions above, with uppper and lower speed
    // bounds
    const double v_high = Config_.high_speed_threshold;
    const double v_low = Config_.low_speed_threshold;

    const double h_v_acc = Config_.high_speed_centric_acceleration_limit;
    const double l_v_acc = Config_.low_speed_centric_acceleration_limit;

    if (std::fabs(v_high - v_low) < 1.0)
    {
        // std::cout << "High speed and low speed threshold are too close to each other. "
        //              "Please check config file."
        //           << " Current high speed threshold = " << v_high
        //           << ", current low speed threshold = " << v_low;
        return h_v_acc;
    }
    const double kMinKappaEpsilon = 1e-9;
    if (kappa < kMinKappaEpsilon)
    {
        return h_v_acc;
    }

    const double k1 = (h_v_acc - l_v_acc) / (v_high - v_low);
    const double k2 = h_v_acc - v_high * k1;

    const double v = (k1 + std::sqrt(k1 * k1 + 4.0 * kappa * k2)) / (2.0 * kappa);
    //  std::cout << "v = " << v;

    if (v > v_high)
    {
        return h_v_acc;
    }
    else if (v < v_low)
    {
        return l_v_acc;
    }
    else
    {
        return v * k1 + k2;
    }
}