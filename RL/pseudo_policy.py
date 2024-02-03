from zmq_class import ZmqPythonCommunication
import sys 
import time
import random
import math


sys.path.append('../datatype/')
from robot_data_pb2 import RobotDataFrameList, RobotData
act_scale = 0.05
zmq_comm = ZmqPythonCommunication()
while True:
    robot_data = zmq_comm.recv_robot_data()
    # print("Received robot data from C++:", robot_data)
    reply_data = RobotData()
    # 使用random模块生成随机数
    n = random.uniform(-act_scale, act_scale)
    reply_data.joint_actions.append(n)
    n = random.uniform(-act_scale, act_scale)
    reply_data.joint_actions.append(n)
    print("act : ",reply_data.joint_actions)
    zmq_comm.send_robot_data(reply_data)
    time.sleep(0.001)