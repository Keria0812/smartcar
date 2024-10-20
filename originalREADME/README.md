# smartcar

#### 介绍

实验室小车代码库

#### 下载及编译
```C++
//一、安装依赖库
1.ubuntu 18.04
sudo apt install ros-melodic-jsk-recognition-msgs 
sudo apt install ros-melodic-jsk-rviz-plugins
sudo apt install ros-melodic-ecl-geometry
sudo apt install ros-melodic-gps-umd

2.ubuntu 20.04
sudo apt install ros-noetic-jsk-recognition-msgs
sudo apt install ros-noetic-jsk-rviz-plugins
sudo apt install ros-noetic-ecl-geometry
sudo apt install ros-noetic-gps-umd

2022 0523更新：
关键：
更新了功能包的结构，包名也发生了变化
start_sim.sh是仿真启动的所有节点
录制的轨迹发布包改名为map,多条轨迹，轨迹名需要包含route_*，目前最大支持3条轨迹
添加protobuf支持

新加的planning，多了很多依赖库，在planning/installers里面有安装脚本


//二、下载小车仓库
git clone https://gitee.com/chenjian688/smartcar.git

//三、编译、安装PROJ库,PRJO已经下载到gps_bridge包下，编译安装方法见
//https://www.cnblogs.com/chenjian688/p/15624038.html

//四、不同Ubuntu版本高，针对自带opencv库的位置做如下修改:
simulator/include/simulator/grid_publisher.h用到了opencv库,请注意修改

1.1ubuntu18.04 自带的opencv库在user/include下，注意include路径
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

1.2ubuntu20.04 自带的opencv库在user/include/opencv4下，注意include路径
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>




//五、编译ros程序
//先编译msg
catkin_make -DCATKIN_WHITELIST_PACKAGES="smartcar_msgs"
catkin_make -DCATKIN_WHITELIST_PACKAGES="can_msgs"
message里面多了很多msg包，先手动一个个编译。以后有时间再清理合并

//再编译剩下的功能包
catkin_make -DCATKIN_WHITELIST_PACKAGES=""
```


#### 软件架构

##### 目前的功能包如下

1. canbus

这个包的功能是启动一个can卡，将接收的can消息转换为topic消息，将接收的topic消息转换为can消息发送到can总线。

2. control

这个包功能是控制模块，算法：纯跟踪

3. gps_bridge

这个包有两个可执行程序

```C++
rosrun gps_bridge gps_bridge_node
//接收组合导向的定位信息，将经纬度转换为UTM坐标发出去
```

```C++
rosrun gps_bridge gps_bridge_collect
//接收定位topic，存为全局轨迹
```

4. messages

一些自定义的msgs。
注意：如果你是新git的这个工程，先运行以下命令，单独编译smartcar_msgs这个包

```C++
catkin_make -DCATKIN_WHITELIST_PACKAGES="smartcar_msgs"  //白名单编译方式，用完后记得再用一次catkin_make -DCATKIN_WHITELIST_PACKAGES=""，不然只会编译smartcar_msgs 
```

然后运行下面命令编译剩下所有包

```C++
catkin_make -DCATKIN_WHITELIST_PACKAGES=""
```

5. simulator

仿真接口。
1、用udp接收carmaker的状态信息，再转发为底盘和定位的topic，保持和实车上的定位和canbus程序发出的topic一致

2、接收控制模块下发的转角、速度

3、接收驾驶模拟器发送的油门、刹车、方向盘转角、自动驾驶和人工驾驶切换指令

4、将2、3步接收的信息经过逻辑处理后，用UDP下发控制模式和对应的控制量

6. track_publisher 全局轨迹发布模块

读取该包tracks下的全局轨迹轨迹文件，然后转发出去。
目前没有规划模块，所以会再转发一个plan的topic。
launch文件制定读取那个全局轨迹，以及目标速度。

7. visualization 可视化功能包
   启动如下命令

```C++
roslaunch show_trajectory show_trajectory.launch
```

8. 注意:运行smartcar的功能包，都在工作空间这一级目录运行。

   方法1： ctrl + alt + T打开终端，cd 到 /home/user/smartcar目录，然后运行各功能包

   方法2： 直接在上述目录右键打开终端

##### 地图坐标系UTM

UTM X —— 东

UTM Y —— 北

UTM Z —— 向上指向天

##### 自车坐标系

x —— 指向车前

y —— 指向左侧

定位点 —— 后轴中心

![Alt text](/image/car.jpeg)

#### 安装教程

1. xxxx
2. xxxx
3. xxxx

#### 使用说明(默认你启动了roscore,后面不在说明)

1. 仿真中新轨迹录制方法

- 1.1启动carmaker

```C++
CM-10.0.1 &
```

然后选择仿真专用工程、testrun，点击start运行

- 1.2 启动轨迹采集节点

```c++
rosrun gps_bridge gps_bridge_collect
```

- 1.3 启动仿真节点
  
修改launch文件中的drivemode为2，即让内置驾驶员模型开车，然后运行下面命令

```c++
roslaunch simulator simulator_node.launch
```

- 1.4 到达终点后
关闭轨迹采集节点，生成的轨迹在smartcar目录下

1. 实车上新轨迹录制方法
   - 如上开启定位节点和轨迹采集节点，然后人工开车录制轨迹

```
rosrun gps_bridge gps_bridge_node
```

```C++
rosrun gps_bridge gps_bridge_collect
```

1. 仿真中循迹功能使用方法
   
   1、将录制的估计移动到 track_publisher这个功能包的track目录下，修改launch文件内容，指定你要读取的轨迹

   2、启动track_publisher

```C++
roslaunch track_publisher track_publisher.launch
```

3、启动 waypoint_follewer

```C++
roslaunch waypoint_follower pure_pursuit.launch 
```

4、启动可视化节点

```C++
roslaunch show_trajectory show_trajectory.launch
```

5、启动仿真节点

```C++
roslaunch simulator simulator_node.launch    //注意将launch文件的驾驶模式改成1
```

6、启动carmaker

#### 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request

#### 特技

1. 使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2. Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3. 你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4. [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5. Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6. Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
