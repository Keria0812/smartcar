'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2024-01-22 15:01:30
LastEditors: jinxiaoxin235
LastEditTime: 2024-03-21 18:15:08
FilePath: /miniEV_grad/Calc/data_process.py
'''
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from scipy.signal import butter, filtfilt

from scipy import signal
import copy

def butter_highpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = butter(order, normal_cutoff, btype='highpass', analog=False)
    return b, a
def apply_highpass_filter(data, cutoff, fs):
    # 获取巴特沃斯高通滤波器系数
    b, a = butter_highpass(cutoff, fs)

    # 获取第四列的数据
  
    column_data = data[:, 3]

    # 对第四列的数据进行滤波
    filtered_column = filtfilt(b, a, column_data)

    # 找到需要保留的行索引
    keep_indices = np.where(filtered_column > 0)[0]

    # 根据保留的行索引进行筛选
    filtered_data = data[keep_indices]
    # print(filtered_data)
    return filtered_data
# 读取txt文件并指定列名
data = pd.read_csv('jiasu.txt', delimiter='\t', header=None, names=['CMDdriver', 'GasFeedback', 'BrakeFeedback', 'AccY', 'AccX', 'ChassisSpeed', 'GpsSpeed'])
# 去除标签行
data = data[1:]
data = data.values
# print(data)
# 转换为数组

data_array = data.astype(float)
# # print(data_array)
# filtered_data = data_array[(data[:, 5] > 2.0 )]
# python
filtered_data = data_array[(data[:, 5].astype(float) > 2.0 )]
# new_data = np.delete(data, [0, 2, 3], axis=0)
# delete_row = []
# for 


# print(filtered_data)

# 剔除速度为零且加速度连续相等的行
# data = data.dropna(subset=['AccY'])
# data['AccY'] = pd.to_numeric(data['AccY'], errors='coerce')

# data = data[(data['ChassisSpeed'] != 0) | (data['AccY'].diff() != 0)]

# 保存处理后的数据到新的txt文件
# data.to_csv('filtered_file.txt', sep='\t', header=False, index=False)
filtered_data = np.round(filtered_data, decimals=4)

first_column = filtered_data[:, 0]

# 找到标志列中的唯一值和对应的索引位置
unique_values, indices = np.unique(first_column, return_index=True)

# 将数据按照标志列的唯一值进行分块
blocks = np.split(data, indices[1:], axis=0)
# np.savetxt('test.txt', blocks[0], delimiter='\t', fmt='%.4f')
print(filtered_data)

print(unique_values)
train_data = []

for id in unique_values :
    print(id)
    print(len(filtered_data))
    plot_data = []
    for gas_brake in filtered_data :
        # print(gas_brake) 
        # print(id)
        # print(type(gas_brake[0]))
        if gas_brake[0] == id :
            if gas_brake[0] < 0 and gas_brake[3] > 0 : continue
            if gas_brake[0] > 0.1 and gas_brake[3] < 0.0 : continue
            if gas_brake[0] > 0.2 and gas_brake[2] > 0.0 : continue

            if gas_brake[2] == 3.0 : continue

            # if gas_brake[0] == 0.55 and gas_brake[3] < 1.5 and gas_brake[5] < 30 :continue
            # if gas_brake[0] == 0.8 and gas_brake[3] < 2.2 and gas_brake[5] < 10 :continue

            plot_data.append(copy.deepcopy(gas_brake))
    # plot_data2 = []
    # print(len(plot_data))
    if (len(plot_data) == 0) : continue
    
            # 将plot_data按照第五列数据升序排列
    plot_data = np.array(plot_data)
    sorted_indices = np.argsort(plot_data[:, 5])
    sorted_plot_data = plot_data[sorted_indices]
    plot_data = sorted_plot_data
    #  假设acceleration是一个包含加速度数据的一维数组
    print(plot_data)
    mean = np.mean(plot_data[:, 3])  # 均值
    std = np.std(plot_data[:, 3])  # 标准差

    lower_bound = mean - 3 * std  # 下边界
    upper_bound = mean + 3 * std  # 上边界
    plot_data = plot_data[(plot_data[:, 3] > lower_bound )& (plot_data[:, 3] < upper_bound )]

    
    left = 0
    right = 0
    for i in range(0, 120, 1) :
        v = i / 2.0
        while left < len(plot_data) and plot_data[left][5] < v - 0.5 :left = left + 1
        right = left
        while right < len(plot_data) and plot_data[right][5] < v + 0.5 : right = right + 1
        if (right == left) : continue

        mean = np.mean(plot_data[left:right, 3])  # 均值
        std = np.std(plot_data[left:right, 3])  # 标准差
        lower_bound = mean - 3 * std  # 下边界
        upper_bound = mean + 3 * std  # 上边界
        tmp = []
        # plot_data = plot_data[((plot_data[left:right, 3] > lower_bound )& (plot_data[left:right, 3] < upper_bound)) | plot_data[0:left, :] | plot_data[right:-1, :]] 
        for ii, dd in enumerate(plot_data) : 
            if (dd[3] > upper_bound or dd[3] < lower_bound) and ii >= left and ii < right : continue
            tmp.append(dd)
        plot_data = np.array(tmp)

    data_to_smooth = plot_data[:, 3]

    # 构造均值滤波器
    n = 100
    mean_filter = np.ones(n)/n

    # 对数据列进行滤波操作
    smoothed_data = signal.convolve(data_to_smooth, mean_filter, mode='same')
    plot_data[:, 3] = smoothed_data

    fs = 1000 # 采样频率
    cutoff = 1 # 截止频率，单位为 Hz

    # 获取巴特沃斯高通滤波器系数
    # b, a = butter_highpass(cutoff, fs)
    

    # 对原始数据进行滤波
    # filtered_data = filtfilt(b, a, plot_data[:, 3])
    # filtered_data_a = apply_highpass_filter(plot_data, cutoff, fs)
    # plot_data = np.array(filtered_data_a) 
    # for gas_brake in plot_data :
    fourth_column = plot_data[:, 3]  # 第四列数据
    fifth_column = plot_data[:, 5]  # 第五列数据  
    # train_data.append(plot_data)
    for data in plot_data :
        train_data.append(data)
    plt.plot(fifth_column, fourth_column)
    # plt.plot(fifth_column, label = "AccX")
    plt.xlabel('Time')
    plt.ylabel('Acc')
    plt.title('Curve for Block {}'.format(id))
    # print(block[0][0])
    # 保存为图片
    plt.savefig('block_{}.png'.format(id))
    # plt.show()
    plt.clf()  # 清除当前图形，准备下一张图
np.savetxt('train_data_miniEV2.txt', train_data, delimiter='\t', fmt='%.4f')

#     plt.xlabel('Time')
#     plt.ylabel('Acc')
#     plt.title('Curve for Block {}'.format(block[0][0]))
#     print(block[0][0])
#     # 保存为图片
#     plt.savefig('block_{}.png'.format(i+1))
#     # plt.show()
#     plt.clf()  # 清除当前图形，准备下一张图 
# # 针对每个块绘制曲线并保存为图片
# for i, block in enumerate(blocks):
#     fourth_column = block[:, 3]  # 第四列数据
#     fifth_column = block[:, 4]  # 第五列数据
#     print(fourth_column)
#     print(len(fourth_column))

#     plt.plot(fourth_column, label = "AccY")
#     plt.plot(fifth_column, label = "AccX")

#     plt.xlabel('Time')
#     plt.ylabel('Acc')
#     plt.title('Curve for Block {}'.format(block[0][0]))
#     print(block[0][0])
#     # 保存为图片
#     plt.savefig('block_{}.png'.format(i+1))
#     # plt.show()
#     plt.clf()  # 清除当前图形，准备下一张图

plt.close()