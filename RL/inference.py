import numpy as np
import torch
from zmq_class import ZmqPythonCommunication
from policy import PolicyFunction
from NN.QlearningNet import QLearningModule
import sys 
import time
import random
import math

sys.path.append('../datatype/')
from robot_data_pb2 import RobotDataFrameList, RobotData

zmq_comm = ZmqPythonCommunication()

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

if __name__ == "__main__":
    input_size = 4
    output_size = 1
    hidden_size = 64
    num_layers = 2
    num_heads = 4

    Qnet = QLearningModule(input_size, output_size, hidden_size, num_layers, num_heads).to(device)
    exsit_model_file = "q_net.pth"
    Qnet.load_state_dict(torch.load("models/" + exsit_model_file))
    print("Load model file: ", exsit_model_file)
    pf = PolicyFunction(Qnet)
    while True:
        robot_data = zmq_comm.recv_robot_data()
        reply_data = RobotData()
        state = np.array([robot_data.joint_positions[0],robot_data.joint_positions[1]])
        act = pf.sample_best_action(state)
        reply_data.joint_actions.append(act[0])
        reply_data.joint_actions.append(act[1])
        zmq_comm.send_robot_data(reply_data)
        print("Sent action: ", act)