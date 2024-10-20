<!--
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2024-01-13 21:20:23
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-13 21:23:26
 * @FilePath: /miniEV/src/planning/README.md
-->
- 成本函数

- void PathTimeGraph::SetDynamicObstacle(const Obstacle *obstacle,
                                       const std::vector<ReferencePoint> &discretized_ref_points) //这里修改了车道障碍物的获取规则，如果接入预测算法，这里也要修改，目前就是做成本计算时，只计算本车道内的障碍物