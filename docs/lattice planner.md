lattice planner:

纵向采样：巡航 跟车 停止

横向采样：假设不管车怎么到达终点状态。它都应该与参考线平行。既不是横向移动，即一阶导数为0，也不是横向加速，即二阶导数为0。

轨迹合成：通过S值匹配


碰撞检测：1、简化:AABB不相交，则原来的肯定不相交

1、巡航状态下的纵向轨迹束：
首先不考虑障碍物信息，只考虑车辆的目标车速，以此进行速度规划：末点的采样->根据起点和末点计算四次多项式系数。

对末点的采样规则：时距8s,采样间隔1s，所以实际的采样时间相对时间戳为:[0.01,1,2,···,7,8]

在每个采样时刻进行6次速度采样。根据车辆当前速度、加/减速度的最大值(非剧烈驾驶下的最大值)以及最大巡航速度，计算该时刻车速的范围，然后均匀插入4个点。这样就可以确定终点状态。实际采样过程示意图:

![Alt text](/image/纵向速度采样.jpg)

2、基于障碍物ST的纵向轨迹束
基于障碍物的纵向规划和基于巡航规划没有本质区别，主要差异在于：末点的采样→根据起点和末点计算五次多项式系数，由四次多项式换为五次多项式。原因在于根据障碍物ST图，我们可以确定末点的s、v、a(a=0)，即明确了六个变量（起始点s、v、a和末点的s、v、a）。

3、轨迹cost评价

在这一阶段，分两步，一个是可行性判断，第二个是cost计算。超车、跟车、停车的轨迹都会产生，至于选哪个，先cost排排好，谁低选谁，便完成了决策的过程，所以并没有出现前述的状态机。

3.1 首先，根据动态约束条件对一维轨迹的可行性进行评价

纵向：速度约束检查、加速度约束检查、加加速度约束检查

3.2 其次，评估可行的纵向和横向轨迹对，并根据成本进行排序

纵向cost: 
目标cost: FLAGS_weight_lon_objective 10(目标的cost由两部分构成 w_speed = 1, w_dist = 10)
舒适性cost: FLAGS_weight_lon_jerk 1.0
碰撞cost: FLAGS_weight_lon_collision 5.0


向心加速度cost: FLAGS_weight_centripetal_acceleration 1.5

横向cost:
横向偏移cost: FLAGS_weight_lat_offset 2.0
横向舒适性cost: FLAGS_weight_lat_comfort 10.0

FLAGS_cost_non_priority_reference_line 5.0
FLAGS_weight_dist_travelled = 10.0
FLAGS_weight_target_speed = 1.0

FLAGS_weight_same_side_offset = 1.0
FLAGS_weight_opposite_side_offset = 10.0

7、轨迹的合并、挑选&无碰撞轨迹的产出
在第6步评价阶段，除了有效性检查(属于硬约束了吧)，是不会对轨迹进行删减操作的，仅仅是按cost进行排序，里边的用到了标准库的优先级队列

7.1 横纵向轨迹对的序列抽取

7.2 轨迹的combine
t采样，得到s，根据s采样，得到L，然后组合得到完整的S、L、t

7.3 轨迹合理性校验

速度、曲率校验这些，要注意和第6阶段cost不一样的地方：此处对速度的约束不再简单的是目标车速，因为在Frenet中进行ST规划时是与真实道路曲率脱节的，而车辆在实际道路转弯时最高车速是车辆操纵稳定性与道路曲率博弈的结果，所以这一阶段的判断是要将道路实际曲率纳入范畴的。

7.4 轨迹的碰撞检测

collision_checker.InCollision(combined_trajectory)