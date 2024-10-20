'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2024-01-15 01:47:00
LastEditors: jinxiaoxin235
LastEditTime: 2024-03-21 18:42:48
FilePath: /miniEV_grad/realgps2dig_xy.py
'''
from mimetypes import init
from operator import truediv
import matplotlib.pyplot as plt
import numpy as np
from pyproj import Proj
from pyproj import Transformer
from scipy import interpolate
import os
from enum import Enum
import copy

if __name__ == "__main__":

    transformer = Transformer.from_crs("epsg:4326", "epsg:4526", always_xy="true")

    tracks  = np.loadtxt("long0321.txt")

    init_lon = tracks[0, 0]
    init_lat = tracks[0, 1]

    # init_point = transformer.transform(init_lon, init_lat)
    init_point = [init_lon, init_lat]

    points = []
    for lon, lat , heading in tracks[:, 0:3]:
        x, y = lon, lat
        # print("%.3f  %.3f" % (x y))
        point = [0.0] * 3
        point[0] = x - init_point[0]
        point[1] = y - init_point[1]
        points.append(copy.deepcopy(point))

    # plt.figure(1)
    xxx = [i[0] for i in points] 
    yyy = [i[1] for i in points]
    # # plt.scatter(xxx, yyy)
    # plt.scatter(xxx, yyy)

    # plt.show()

    save_name = "longlingshan0321.dig"
    with open(save_name, 'w') as f:
        f.write(":	x	y	z\n")
        for i in range(len(xxx)):
            # print(f"line is {line}")
            point_new = ""
            point_new += str(xxx[i]) + "\t" + str(yyy[i]) + "\t" + str(0.0)
            
            point_new = point_new + "\n"
            f.write(point_new)

    print('end...')