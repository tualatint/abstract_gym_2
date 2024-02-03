import sys
import redis

sys.path.append('../datatype/')
from robot_data_pb2 import RobotDataFrameList, RobotData

class redis_interface:
    def __init__(self, host = '127.0.0.1', port = 6379, db = 0):
        self.host = host
        self.port = port
        self.db = db
        self.r = redis.Redis(host=self.host, port=self.port, db=self.db)  
        self.dbsize = self.r.dbsize()  
        print("dbsize : ",self.dbsize)
    
    def get_random_data(self):
        random_key = self.r.randomkey()
        random_value = self.r.get(random_key)
        try: # with a 1/1e7 chance this could fail when global index is fetched.
            data_list = RobotDataFrameList()
            data_list.ParseFromString(random_value)
            return data_list
        except: # repeat once
            random_key = self.r.randomkey()
            random_value = self.r.get(random_key)            
            data_list = RobotDataFrameList()
            data_list.ParseFromString(random_value)
            return data_list
    

if __name__ == "__main__":
    redis_interface = redis_interface()
    robot_data_frames = redis_interface.get_random_data()
    for (i,data_frame) in enumerate(robot_data_frames.robot_data_frames):  
        print("i:",i)
        print(data_frame) 
        

    