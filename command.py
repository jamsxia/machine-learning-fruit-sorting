import torchvision.models as models
import  dataset
import torch
import torch.nn as nn
from PIL import Image
import numpy as np
import serial
model =models.resnet18(pretrained=False)
model.fc = nn.Linear(512,2)
model.load_state_dict(torch.load('savedModel'))
model.eval()
WIDTH = 300
HEIGHT = 300
img_path = 'test.jpg'

img = torch.tensor(np.array(Image.open(img_path).resize((WIDTH,HEIGHT))),dtype=torch.float).view(3,WIDTH,HEIGHT)

img = torch.unsqueeze(img,0)
outputs = model(img)
outputs = torch.argmax(outputs,dim=1).item()
print(outputs)
com = serial.Serial('COM5', 115200)
success_bytes = com.write(str(outputs))
print(success_bytes)