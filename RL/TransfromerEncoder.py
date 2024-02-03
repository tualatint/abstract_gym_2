import torch
import torch.nn as nn
import torch.nn.functional as F

class TransformerEncoder(nn.Module):
    def __init__(self, input_dim=4, hidden_dim=64, output_dim=1, num_heads=8, dropout=0.2):
        super(TransformerEncoder, self).__init__()
        self.transformer = nn.TransformerEncoder(
            nn.TransformerEncoderLayer(hidden_dim, num_heads, hidden_dim * 4, dropout),
            num_layers=2
        )
        self.fc = nn.Linear(hidden_dim, output_dim)
        self.fc0 = nn.Linear(input_dim, hidden_dim)

    def forward(self, x):
        # x: (batch_size, seq_length, input_dim)
        x = self.fc0(x)
        x = self.transformer(x)
        # Take the last output as the final representation
        x = x[:, -1, :]
        # Pass through the fully connected layer to get the score
        score = self.fc(x)

        return score

if __name__ == '__main__':
    model = TransformerEncoder()

    # Create a random input tensor with shape (batch_size, seq_length, input_dim)
    # Here, we assume batch_size = 2 and seq_length = 5 input_dim = 4
    input_tensor = torch.rand(2, 5, 4)
    # input_tensor = torch.randint(0, input_dim, (1, 4, input_dim))
    print("input tensor : ", input_tensor)
    print("input tensor shape : ", input_tensor.shape)

    # Get the output score
    output_score = model(input_tensor)

    print(output_score)