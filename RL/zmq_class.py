import zmq
import sys 
import time
sys.path.append('../datatype/')
from robot_data_pb2 import RobotDataFrameList, RobotData

class ZmqPythonCommunication:
    def __init__(self):
        self.context = zmq.Context.instance()
        self.socket = self.context.socket(zmq.REP)
        self.socket.bind("tcp://*:5555")

    def send_robot_data(self, robot_data):
        serialized_data = robot_data.SerializeToString()
        self.socket.send(serialized_data)

    def recv_robot_data(self):
        # print("Waiting for data...")
        data = self.socket.recv()
        return RobotData().FromString(data)

if __name__ == "__main__":
    zmq_comm = ZmqPythonCommunication()
    while True:
        robot_data = zmq_comm.recv_robot_data()
        print("Received robot data from C++:", robot_data)
        reply_data = RobotData()
        reply_data.joint_actions.append(0.1)
        reply_data.joint_actions.append(0.2)
        zmq_comm.send_robot_data(reply_data)
        time.sleep(0.01)