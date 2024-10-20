'''
Copyright: jinxiaoxin@whut.edu.cn
Author: jinxiaoxin235
Date: 2024-04-03 02:14:48
LastEditors: jinxiaoxin235
LastEditTime: 2024-04-03 02:17:51
FilePath: /miniEV_grad/Calc/plottt.py
'''
import matplotlib.pyplot as plt

def plot_loss_from_txt(filename):
    epochs = []
    losses = []

    # 读取txt文件并提取Epoch和Loss值
    with open(filename, 'r') as file:
        for line in file:

        
            losses.append(float(line))
    epochs = range(0, len(losses))
    # 绘制曲线
    plt.plot(epochs, losses)
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    # plt.title('Loss vs. Epoch')
    plt.grid(False)
    plt.show()
    # plt.grid(True)
# 用法示例
filename = 'loss_history.txt'  # 替换为你的txt文件路径
plot_loss_from_txt(filename)