import torchvision.models as models
import  dataset
import torch
import torch.nn as nn
from PIL import Image
import numpy as np
WIDTH = 300
HEIGHT = 300
name_dict = {"0":'bad','1':'fresh'}
model =models.resnet18(pretrained=False)
model.fc = nn.Linear(512,2)
model.load_state_dict(torch.load('savedModel'))
model.eval()

path = "WIN_20210123_14_52_21_Pro"+".jpg"
img = torch.tensor(np.array(Image.open(path).resize((WIDTH,HEIGHT))),dtype=torch.float).view(3,WIDTH,HEIGHT)
img = img.unsqueeze(0)
outputs = model(img)
outputs = torch.argmax(outputs,dim=1)
print(name_dict[str(outputs.item())])

