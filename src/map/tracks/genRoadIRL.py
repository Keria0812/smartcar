'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2023-11-29 11:58:39
LastEditors: jinxiaoxin235
LastEditTime: 2024-01-06 16:40:39
FilePath: /miniEV/src/map/tracks/genRoadIRL.py
'''
import math

lane_width = 12.0/3.281


def generate_center_line(start_x, start_y, start_heading, length):
    """
    生成车道中心线
    :param start_x: 起点x坐标
    :param start_y: 起点y坐标
    :param start_heading: 起点航向角
    :param length: 车道中心线长度
    :return: 车道中心线，格式为[(x1, y1, heading1), (x2, y2, heading2), ...]
    """
    center_line = []
    x = start_x
    y = start_y
    heading = start_heading
    center_line.append((x, y, heading))

    for i in range(1, length):
        x_prev, y_prev, _ = center_line[i-1]

        angle = math.radians(heading)

        x = x_prev + math.cos(angle)
        y = y_prev + math.sin(angle)

        center_line.append((x, y, heading))

    return center_line

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

# # 读取数据文件
# with open('route_1long.txt', 'r') as file:
#     data = file.readlines()

# # 解析数据
# trajectory = parse_trajectory(data)

center_line = generate_center_line(0, 0, 0, 800)

# 扩展车道中心线
left_lines, right_lines = extend_center_line(center_line)

# 写入左侧车道中心线文件
with open('route_1_IRL.txt', 'w') as file:
    for line in center_line:
        file.write(f"{line[0]} {line[1]} {line[2]}\n")

# 写入左侧车道中心线文件
with open('route_0_IRL.txt', 'w') as file:
    for line in left_lines:
        file.write(f"{line[0]} {line[1]} {line[2]}\n")

# 写入右侧车道中心线文件
with open('route_2_IRL.txt', 'w') as file:
    for line in right_lines:
        file.write(f"{line[0]} {line[1]} {line[2]}\n")

print("左侧车道中心线已写入到 left_lines.txt 文件")
print("右侧车道中心线已写入到 right_lines.txt 文件")
