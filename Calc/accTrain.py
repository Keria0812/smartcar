'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2023-10-25 14:33:28
LastEditors: jinxiaoxin235
LastEditTime: 2024-04-03 02:07:53
FilePath: /miniEV_grad/Calc/accTrain.py
'''
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense
from keras.models import load_model
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


# # 加载数据
# data = pd.read_csv('2023-10-29-03:35:18GasBrake.txt')
# import pandas as pd

# try:
#     data = pd.read_csv('train_data_miniEV2.txt', sep='\t')
# except FileNotFoundError:
#     print("File not found!")
# except Exception as e:
#     print("Error:", e)

# # 计算XY方向合成加速度
# # data['acc'] = np.sqrt(data['accX']**2 + data['accY']**2)
# # data['acc'] = data['accY']


# # 剔除异常值
# # data = data[(data['acc'] >= -10) & (data['acc'] <= 10)]

# # 打乱数据
# data = data.sample(frac=1).reset_index(drop=True)
# data = np.array(data)
# # 提取特征和标签
# # X = data[['Gas', 'Brake']] / [100.0, 8.0]
# # y = data[['ChassisSpeed(km/h)','acc']]
# X = data[:, [3, 6]]
# y = data[:, 0]

# # for index, row in X.iterrows():
# #     brake_value = row['Brake']
# #     if brake_value > 0:
# #         row['Gas'] -= brake_value
# #         row['Brake'] = -brake_value
# # # 删除 'Brake' 列
# # # data.drop(columns=['Brake'], axis=1 , inplace=True)
# # X = X['Gas'].to_frame()
# # Z = X
# # X = y
# # y = Z
# print(X)
# print(y)
# # 划分训练集和测试集
# X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# # # 构建神经网络模型
# model = Sequential()
# model.add(Dense(10, input_dim=2, activation='relu'))
# model.add(Dense(1, activation='linear'))
# model.compile(loss='mean_squared_error', optimizer='adam')

# # 训练模型
# history = model.fit(X_train, y_train, epochs=100, batch_size=10, verbose=1)

# # 预测测试集
# y_pred = model.predict(X_test)

# # 评估模型
# score = model.evaluate(X_test, y_test, verbose=0)
# print('Test loss:', score)

# # 保存模型
# model.save('model_miniEV.h5')


# # 训练模型


# # 保存loss到txt文件
# loss_history = np.array(history.history['loss'])
# np.savetxt('loss_history.txt', loss_history, delimiter=',')

# # 绘制loss曲线
# plt.plot(history.history['loss'])
# plt.title('Model Loss')
# plt.xlabel('Epoch')
# plt.ylabel('Loss')
# # plt.savefig('loss_plot.png')

# # # 展示loss曲线
# # plt.show()

# # # # 加载模型
model = load_model('model_tesla.h5')

# # 使用加载的模型进行预测
# y_pred = model.predict(X_test)

# # 评估加载的模型
# score = model.evaluate(X_test, y_test, verbose=0)
# print('Test loss:', score)


# 生成速度范围和步长
speed_range = np.arange(0, 100, 1)

# 生成加速度范围和步长
acceleration_range = np.arange(-3.5, 2.5, 0.1)

# 创建空的标定表
calibration_table = np.zeros((len(speed_range), len(acceleration_range)))

# 填充标定表
for i, speed in enumerate(speed_range):
    for j, acceleration in enumerate(acceleration_range):
        # 构造输入特征
        print(i, j, speed, acceleration)
        input_features = np.array([[acceleration, speed]])
        # print(input_features)
        # # 预测油门和刹车控制量
        throttle_brake = model.predict(input_features)[0]
        print(throttle_brake)

        throttle_brake = min(throttle_brake, 1.0)
        throttle_brake = max(throttle_brake, -1.0)

        # 将预测的油门和刹车控制量填入标定表
        calibration_table[i][j] =  throttle_brake


calibration_table_reshaped = calibration_table.reshape(len(speed_range), len(acceleration_range))
# np.savetxt('calibration_table_miniEV.txt', calibration_table_reshaped, fmt='%.2f')
import matplotlib as mpl

mpl.rcParams['font.family'] = 'WenQuanYi Micro Hei'
mpl.rcParams['axes.unicode_minus'] = False  # 正确显示负号

mpl.rcParams['font.size'] = 20
# # 保存标定表到txt文件
xx, yy = np.meshgrid(acceleration_range, speed_range)
fig = plt.figure(figsize=(10, 6))
ax = fig.gca(projection='3d')
print(xx.shape)
print(yy.shape)
print(calibration_table_reshaped.shape)
print(type(xx), type(yy), type(calibration_table_reshaped))
ax.plot_surface(xx, yy, calibration_table_reshaped, cmap='viridis')
ax.set_xlabel('加速度',labelpad=20)
ax.set_ylabel('速度(km/h)',labelpad=20)
ax.set_zlabel('油门刹车',labelpad=20)
ax.zaxis.label.set_rotation(90)    # 设置旋转角度
ax.xaxis.label.set_rotation(90)    # 设置旋转角度


ax.view_init(elev=20, azim=170)
ax.set_box_aspect([100,100,100])  # 控制 S 坐标轴的长度，可以根据具体需求调整比例
plt.show()
# plt.savefig('real.jpg')
plt.savefig('real.jpg', format='png', dpi=100)

print('Calibration table saved successfully.')
