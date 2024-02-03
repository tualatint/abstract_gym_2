import numpy as np
# import sys
# from torch.utils import data
# sys.path.append('../datatype/')
# from robot_data_pb2 import RobotDataFrameList, RobotData

# class Sampler(data.Dataset):
class Sampler:
    """
    Randomly sample a data point in the record data list.
    Calculate the expected future reward (Q value) of that data point, and feed into a NN for training.
    gamma: discount factor.
    """

    def __init__(self, redis):
        self.r = redis
        self.gamma = 0.99

    def __len__(self):
        return self.r.dbsize

    def __getitem__(self, index):
    # def __getitem__(self):
        """
        Sample one data point from a given epoch (specified by index).
        :param index: randomly generated through torch.utils.data.DataLoader if shuffle is True.
        :return: a data pair of (last_state, action),(q_value)
        """
        try:
            # record = self.r[index]
            robot_data_frames = self.r.get_random_data()
            length = len(robot_data_frames.robot_data_frames)
            end_reward = float(robot_data_frames.robot_data_frames[length - 1].reward)
            if length == 1:
                last_state = np.array(robot_data_frames.robot_data_frames[0].joint_positions, dtype=np.float32)
                last_action = np.array(robot_data_frames.robot_data_frames[0].joint_actions, dtype=np.float32)
                x = np.concatenate((last_state, last_action), axis=0)
                return x, end_reward
            seed = np.random.randint(1, length)
            last_state = np.array(robot_data_frames.robot_data_frames[seed - 1].joint_positions, dtype=np.float32)
            future_reward = self.calculate_expected_future_reward(length - seed - 1, end_reward)
            x = np.concatenate((last_state, np.array(robot_data_frames.robot_data_frames[seed].joint_actions)), axis=0)
            return x, future_reward
        except:
            print("Error length :", length)
            print("Error seed :", seed)
            print("record:", robot_data_frames.robot_data_frames[seed])

    def calculate_expected_future_reward(self, l, end_reward):
        """
        Calculate the expected future reward
        :param l: the steps between sampled step and end.

        :param end_reward: the end reward, either -1e4 (collision) or 1e4 (success)
        :return:
        """
        return end_reward * pow(self.gamma, l)