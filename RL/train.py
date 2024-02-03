import numpy as np
from NN.QlearningNet import QLearningModule
from redis_interface import redis_interface
import torch
from dataloader import Sampler
from torch.utils import data
from TransfromerEncoder import TransformerEncoder
from ringbuffer import RingBufferSampler

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

if __name__ == '__main__':

    # input_size = 4
    # output_size = 1
    # hidden_size = 64
    # num_layers = 2
    # num_heads = 4

    # Qnet = QLearningModule(input_size, output_size, hidden_size, num_layers, num_heads).to(device)
    Qnet = TransformerEncoder().to(device)

    # state = torch.randn(1, 2).to(device)
    # action = torch.randn(1, 2).to(device)
    # print("state : ",state)
    # print("action : ",action)
    redis = redis_interface()
    sampler = RingBufferSampler(redis)
    data_size = len(sampler)
    params = {"batch_size": 1, "shuffle": True, "num_workers": 2}
    training_generator = data.DataLoader(sampler, **params)
    """
    Define network.
    """
    criterion = torch.nn.MSELoss()
    learning_rate = 1e-4
    optimizer = torch.optim.Adam(Qnet.parameters(), lr=learning_rate, weight_decay=1e-5)
    max_epoch = np.int64(1000)
    exsit_model_file = "q3_net_best.pth"
    # Qnet.load_state_dict(torch.load("models/" + exsit_model_file))
    print("Load model file: ", exsit_model_file)
    best_loss = 1e10
    try:
        for epoch in range(max_epoch):
            total_loss = 0.0
            iteration = 0
            for x, y in training_generator:
            # for iteration in range (redis.dbsize):
                iteration += 1
                x = x.view(1,-1, 4).to(device, dtype=torch.float)
                y = y.view(-1, 1).to(device, dtype=torch.float)
                # x,y = sampler.__getitem__()
                # x = torch.from_numpy(x).view(-1, 4).to(device, dtype=torch.float)
                # y = torch.from_numpy(np.array(y)).view(-1, 1).to(device, dtype=torch.float)
                out = Qnet.forward(x)
                loss = criterion(y, out)
                total_loss += loss
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
                # if iteration % 10000 == 0:
                    # print("Epoch {}: {}/{} loss = {:.4f}".format(epoch, iteration, data_size, total_loss / iteration))
            print("Epoch {}: {:.4f}".format(epoch, total_loss / iteration))
            model_file_name = "q3_net"+str(epoch)+"_"+str(iteration)+".pth"
            torch.save(Qnet.state_dict(), "models/" + model_file_name)
            print("Model file: " + model_file_name + " saved.")
            if total_loss / iteration < best_loss:
                best_loss = total_loss / iteration
                best_model_file_name = "q3_net_best.pth"
                torch.save(Qnet.state_dict(), "models/" + best_model_file_name)
                print("Model file: " + best_model_file_name + " saved.")
    except (KeyboardInterrupt, SystemExit, RuntimeError):
        model_file_name = "q3_net.pth"
        torch.save(Qnet.state_dict(), "models/" + model_file_name)
        print("Model file: " + model_file_name + " saved.")

# q2_net : number of layer = 1
# q3_net : number of layer = 2
