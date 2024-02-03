import numpy as np
from torch.utils import data
import sys
sys.path.append('../datatype/')
from robot_data_pb2 import RobotDataFrameList, RobotData

class RingBufferSampler(data.Dataset):
    """
    Randomly sample a data point in the record data list.
    Calculate the expected future reward (Q value) of that data point, and feed into a NN for training.
    gamma: discount factor.
    """

    def __init__(self, redis, window_size = 5):
        self.r = redis
        self.window_size = window_size
        self.gamma = 0.99

    def __len__(self):
        return self.r.r.llen('p_ring_buff')

    def __getitem__(self, index):
        """
        Sample one data point from a given epoch (specified by index).
        :param index: randomly generated through torch.utils.data.DataLoader if shuffle is True.
        :return: a data pair of (last_state, action),(q_value)
        """
        try:
            redis_data = self.r.r.lindex('p_ring_buff', index)
            dl = RobotDataFrameList()
            dl.ParseFromString(redis_data)
            length = len(dl.robot_data_frames)
            seed = np.random.randint(0, length)
            if length < self.window_size:
                low_index = 0
                upper_index = length - 1
                ext = self.window_size - length
            elif seed < (self.window_size-1):
                low_index = 0
                upper_index = seed
                ext = self.window_size - seed - 1
            else:
                low_index = seed - (self.window_size-1)
                upper_index = seed
                ext = 0
            x_ext = np.array([])
            reward = np.array(dl.robot_data_frames[upper_index].reward,dtype=np.float32).reshape(-1, 1)

            for i in range(low_index, upper_index+1):
                x = np.concatenate((np.array(dl.robot_data_frames[i].joint_positions, dtype=np.float32),
                                        np.array(dl.robot_data_frames[i].joint_actions, dtype=np.float32)), axis=0)
                x_ext = np.concatenate((x_ext, x), axis=0)
            if ext:
                first_state = np.array(dl.robot_data_frames[0].joint_positions, dtype=np.float32)
                first_action = np.array(dl.robot_data_frames[0].joint_actions, dtype=np.float32)
                x0 = np.concatenate((first_state, first_action), axis=0)
                for i in range(ext):
                    x_ext = np.concatenate((x_ext, x0), axis=0)
            result = x_ext.reshape(-1, 4)
            return result, reward
        except:
            print("Error length :", length)
            print("Error seed :", seed)
            print("record:", dl.robot_data_frames[seed])

    def calculate_expected_future_reward(self, l, end_reward):
        """
        Calculate the expected future reward
        :param l: the steps between sampled step and end.

        :param end_reward: the end reward, either -1e4 (collision) or 1e4 (success)
        :return:
        """
        return end_reward * pow(self.gamma, l)
    

