'''
Copyright: 
file name: File name
Data: Do not edit
LastEditor: 
LastData: 
Describe: 
'''
'''
Copyright: 
file name: File name
Data: Do not edit
LastEditor: 
LastData: 
Describe: 
'''
#!/usr/bin/env python3
# coding=UTF-8
'''
此程序为测试测试程序， 用以测试message_filters同时
订阅两个topic,可以同时进行数据处理。
'''
from matplotlib.pyplot import title
import rospy, math, random, cv_bridge, cv2
import rospy
import message_filters
from cv_bridge import CvBridge,CvBridgeError
from sensor_msgs.msg import Image, CameraInfo
import os
import time
import rospkg
import argparse
from smartcar_msgs.msg import DetectedObjectArray

save_id = 1
save_name = 'scripts/collect/car_' + str(save_id) + '.csv'
save_name = rospkg.RosPack().get_path('naive_motion_predict') + '/' + save_name

f = open(save_name, 'w')
title = 'time(s)' + ',' + 'x(m)' + ',' + 'y(m)' + ',' + 'z(m)' + ',' + 'theta(rad)' + ',' + 'v(m/s)' + '\n'
f.write(title)

def multi_callback(msg1):
    global f

    point_new = ""
    target_id = int(save_id/100)
    point_new = str(rospy.get_time()) + ',' \
                + str(msg1.objects[target_id].utm_x) + ',' \
                + str(msg1.objects[target_id].utm_y) + "," \
                + str(msg1.objects[target_id].utm_z) + "," \
                + str(msg1.objects[target_id].utm_heading) + "," \
                + str(msg1.objects[target_id].speed)

    point_new = point_new + "\n"
    f.write(point_new)

    # print(rospy.get_time())


if __name__ == '__main__':
    rospy.init_node('Collect_ObjectInfo', anonymous=True)#初始化节点

    subcriber_detectObjects = message_filters.Subscriber('/ITS/DetectObjects', DetectedObjectArray)#订阅第一个话题
 
    sync = message_filters.ApproximateTimeSynchronizer([subcriber_detectObjects], 10,1)#同步时间戳，具体参数含义需要查看官方文档。
    sync.registerCallback(multi_callback)#执行反馈函数
    try:
        rospy.spin()
    except rospy.ROSInterruptException:
        print("over!")
    
    f.close()
    print('end...')



