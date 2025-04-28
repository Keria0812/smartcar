```
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-04-23 19:56:39
 * @LastEditors: xining095@whut.edu.cn
 * @LastEditTime: 2025-03-23
 * @FilePath: src/prediction/motion_predictor/naive_motion_predict/src/naive_motion_predict.cpp
```


## 录制的轨迹文件名

轨迹文件名一定是car_*.csv的格式，*是0、100、200、...、6300，最大支持64个障碍物


## 录制环境车轨迹前

在carmaker中将object sensor的感知范围设置得很大，保证一直能检测得到

```
rosrun naive_motion_predict collect_object_path.py
```

## 使用Path-based 预测

在naive_motion_prediction.launch文件中启动基于path-based 预测，并补充中心线txt文件路径（miniEV_grad/src/map/tracks）