'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2023-10-25 14:33:28
LastEditors: jinxiaoxin235
LastEditTime: 2024-01-23 01:55:31
FilePath: /miniEV/accTrain.py
'''
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense
from keras.models import load_model
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


# 加载数据
# data = pd.read_csv('2023-10-29-03:35:18GasBrake.txt')
# import pandas as pd

try:
    data = pd.read_csv('Calc/train_data.txt', sep='\t')
except FileNotFoundError:
    print("File not found!")
except Exception as e:
    print("Error:", e)

# 计算XY方向合成加速度
# data['acc'] = np.sqrt(data['accX']**2 + data['accY']**2)
# data['acc'] = data['accY']


# 剔除异常值
# data = data[(data['acc'] >= -10) & (data['acc'] <= 10)]

# 打乱数据
data = data.sample(frac=1).reset_index(drop=True)

# 提取特征和标签
# X = data[['Gas', 'Brake']] / [100.0, 8.0]
# y = data[['ChassisSpeed(km/h)','acc']]
X = data[:, 0]
y = data[:, [3, 5]]
# for index, row in X.iterrows():
#     brake_value = row['Brake']
#     if brake_value > 0:
#         row['Gas'] -= brake_value
#         row['Brake'] = -brake_value
# # 删除 'Brake' 列
# # data.drop(columns=['Brake'], axis=1 , inplace=True)
# X = X['Gas'].to_frame()
# Z = X
# X = y
# y = Z
print(X)
print(y)
# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# # 构建神经网络模型
model = Sequential()
model.add(Dense(10, input_dim=2, activation='relu'))
model.add(Dense(1, activation='linear'))
model.compile(loss='mean_squared_error', optimizer='adam')

# 训练模型
model.fit(X_train, y_train, epochs=100, batch_size=10, verbose=1)

# 预测测试集
y_pred = model.predict(X_test)

# 评估模型
score = model.evaluate(X_test, y_test, verbose=0)
print('Test loss:', score)

# 保存模型
model.save('model.h5')


# # 加载模型
# model = load_model('model.h5')

# # 使用加载的模型进行预测
# y_pred = model.predict(X_test)

# # 评估加载的模型
# score = model.evaluate(X_test, y_test, verbose=0)
# print('Test loss:', score)


# 生成速度范围和步长
speed_range = np.arange(0, 41, 1)

# 生成加速度范围和步长
acceleration_range = np.arange(-2.5, 1.55, 0.05)

# 创建空的标定表
calibration_table = np.zeros((len(speed_range), len(acceleration_range)))

# 填充标定表
for i, speed in enumerate(speed_range):
    for j, acceleration in enumerate(acceleration_range):
        # 构造输入特征
        print(i, j, speed, acceleration)
        input_features = np.array([[speed, acceleration]])
        # print(input_features)
        # # 预测油门和刹车控制量
        throttle_brake = model.predict(input_features)[0]
        print(throttle_brake)
        # 将预测的油门和刹车控制量填入标定表
        calibration_table[i][j] = throttle_brake


calibration_table_reshaped = calibration_table.reshape(len(speed_range), len(acceleration_range))
np.savetxt('calibration_table.txt', calibration_table_reshaped, fmt='%.6f')

# # 保存标定表到txt文件
# xx, yy = np.meshgrid(acceleration_range, speed_range)
# fig = plt.figure()
# ax = fig.gca(projection='3d')
# ax.plot_surface(xx, yy, calibration_table.T, cmap='viridis')
# ax.set_xlabel('Acceleration')
# ax.set_ylabel('Speed (km/h)')
# ax.set_zlabel('Throttle')

# plt.show()

print('Calibration table saved successfully.')
