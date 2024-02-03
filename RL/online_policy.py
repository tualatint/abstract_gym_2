from zmq_class import ZmqPythonCommunication
import sys 
import torch
import numpy as np
from TransfromerEncoder import TransformerEncoder
from policy import PolicyFunction
import os
import time

sys.path.append('../datatype/')
from robot_data_pb2 import RobotDataFrameList, RobotData
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")


# Function to load the model from the .pth file
def load_model(model_path):
    # Assuming you have a model class defined somewhere
    model = TransformerEncoder().to(device)  # Replace with your actual model class
    model.load_state_dict(torch.load(model_path))
    return model

act_scale = 0.05
zmq_comm = ZmqPythonCommunication()
Qnet = TransformerEncoder().to(device)
# exsit_model_file = "q2_net174_10001.pth"
exsit_model_file = "q3_net_best.pth"
model_path = "models/" + exsit_model_file
Qnet.load_state_dict(torch.load(model_path))
last_modified_time = os.path.getmtime(model_path)
Qnet.eval()
print("Load model file: ", exsit_model_file)
pf = PolicyFunction(Qnet)
iter = 0
with torch.no_grad():
    while True:
        iter+=1
        robot_data = zmq_comm.recv_robot_data()
        reply_data = RobotData()
        state = torch.Tensor([robot_data.joint_positions[0],robot_data.joint_positions[1]])
        if robot_data.done_flag == True:
            pf.reset_buffer(state)
        act = pf.sample_best_action_batch(state)
        reply_data.joint_actions.append(act[0][0][0].float())
        reply_data.joint_actions.append(act[0][0][1].float())
        zmq_comm.send_robot_data(reply_data)
        # print("Sent action: ", [act[0][0][0].float(), act[0][0][1].float()])
        if iter%10000 == 0:
            current_modified_time = os.path.getmtime(model_path)
            if current_modified_time > last_modified_time:
            # The file has been updated, reload the model
                Qnet = load_model(model_path)
                Qnet.eval()
                print("Reload model file...")
                pf = PolicyFunction(Qnet)
                last_modified_time = current_modified_time  