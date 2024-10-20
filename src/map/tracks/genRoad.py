'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2023-11-29 11:58:39
LastEditors: jinxiaoxin235
LastEditTime: 2024-03-22 16:08:02
FilePath: /miniEV_grad/src/map/tracks/genRoad.py
'''
import math

lane_width = 3.75

def parse_trajectory(data):
    """
    解析轨迹数据
    :param data: 轨迹数据，格式为[(x1, y1, heading1), (x2, y2, heading2), ...]
    :return: 轨迹点列表，格式为[(x1, y1, heading1), (x2, y2, heading2), ...]
    """
    trajectory = []
    for line in data:
        x, y, heading = line.split()
        x = float(x)
        y = float(y)
        heading = float(heading)
        trajectory.append((x, y, heading))
    return trajectory

def extend_center_line(center_line):
    """
    根据车道中心线扩展出左右侧车道中心线的轨迹点
    :param center_line: 车道中心线，格式为[(x1, y1, heading1), (x2, y2, heading2), ...]
    :return: 左右侧车道中心线，格式为(left_lines, right_lines)，其中left_lines和right_lines分别为[(x1, y1, heading1), (x2, y2, heading2), ...]格式
    """
    left_lines = []
    right_lines = []

    for i in range(len(center_line)):
        if i == len(center_line) - 1:
            break
        x, y, heading = center_line[i]
        x_prev, y_prev, heading_prev = center_line[i+1]

        angle = math.radians(heading)

        theta_x = x_prev - x
        theta_y = y_prev - y
        theta = math.atan2(theta_y, theta_x)
        
        left_x =  x - lane_width * math.sin(theta)
        left_y =  y + lane_width * math.cos(theta)
        right_x =  x + lane_width * math.sin(theta)
        right_y =  y - lane_width * math.cos(theta)

        # left_x = x - lane_width * math.sin(angle)
        # left_y = y + lane_width * math.cos(angle)
        # right_x = x + lane_width * math.sin(angle)
        # right_y = y - lane_width * math.cos(angle)

        left_lines.append((left_x, left_y, heading))
        right_lines.append((right_x, right_y, heading))

    return left_lines, right_lines

# 读取数据文件
with open('route_1np0321.txt', 'r') as file:
    data = file.readlines()

# 解析数据
trajectory = parse_trajectory(data)

# 扩展车道中心线
left_lines, right_lines = extend_center_line(trajectory)

# 写入左侧车道中心线文件
with open('route_0np0321.txt', 'w') as file:
    for line in left_lines:
        file.write(f"{line[0]:.3f} {line[1]:.3f} {line[2]:.3f}\n")

# 写入右侧车道中心线文件
with open('route_2np0321.txt', 'w') as file:
    for line in right_lines:
        file.write(f"{line[0]:.3f} {line[1]:.3f} {line[2]:.3f}\n")


print("左侧车道中心线已写入到 left_lines.txt 文件")
print("右侧车道中心线已写入到 right_lines.txt 文件")
