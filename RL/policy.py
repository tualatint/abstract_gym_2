import numpy as np
import torch

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

class PolicyFunction:

    def __init__(self, q_net, scale_factor=0.1):
        self.q_net = q_net
        self.scale_factor = scale_factor
        self.sample_size = 50
        self.buff_seq_len = 5
        self.input_dim = 4
        self.buff = torch.zeros(self.sample_size, self.buff_seq_len,self.input_dim)

    def reset_buffer(self, state): # state shape (1,2)
        rp_state = state.repeat(self.sample_size,self.buff_seq_len, 1) #(20,5,2)
        self.buff = torch.cat((rp_state, torch.zeros(self.sample_size, self.buff_seq_len,2)),dim=2)

    def sample_best_action(self, state):
        action_list = (np.random.rand(self.sample_size, 2) - 0.5) * self.scale_factor
        state_list = np.tile(state, (self.sample_size, 1))
        input_x = torch.cat((torch.Tensor(state_list), torch.Tensor(action_list)), 1)
        input_x = torch.Tensor(input_x).to(device, dtype=torch.float)
        try:
            with torch.no_grad():
                q_list = self.q_net.forward(input_x)
        finally:
            best_index = torch.argmax(q_list)
        return action_list[best_index]
    
    def sample_best_action_batch(self, state):
        action_list = (torch.rand(self.sample_size,1, 2) - 0.5) * self.scale_factor #(20,1,2)
        # print("action_list : ",action_list)
        state_list = state.repeat(self.sample_size,1, 1) #(20,1,2)
        input_x = torch.cat((torch.Tensor(state_list), torch.Tensor(action_list)), 2) #(20,1,4)
        self.buff = self.buff[:, :-1, :]
        self.buff = torch.cat((input_x, self.buff), dim=1)
        input_x = self.buff.clone().to(device, dtype=torch.float)
        # print("input_x : ",input_x)
        try:
            with torch.no_grad():
                q_list = self.q_net.forward(input_x)
                # print("q : ",q_list)
                # print(q_list.shape)
        finally:
            best_index_list = torch.argmax(q_list, dim=0)
            # print("best idx: ",best_index_list)
        # update the first line in buff
        # choosen_action = action_list[best_index_list].repeat(self.sample_size,1,1)
        # print("chosen act shape: ",choosen_action.shape)
        # print("choosen action: ",choosen_action)
        # print("state list shape : ",torch.Tensor(state_list).shape)
        # print("cat shape",torch.cat((torch.Tensor(state_list), choosen_action), 2).shape)
        # print("buff 0 shape:",self.buff[:, 0, :].shape)
        # self.buff[:, 0, :] = torch.cat((torch.Tensor(state_list), choosen_action), 2).squeeze()
        return action_list[best_index_list]
    

