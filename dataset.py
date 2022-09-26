import numpy as np
import torch
from PIL import Image
from torch.utils.data.dataset import Dataset
import torch.nn as nn
WIDTH = 300
HEIGHT = 300
class WC(Dataset):
    def __init__(self,path):
        self.file = open(path,"r")
        self.lines = self.file.readlines()
    def __len__(self):
        return len(self.lines)
    def __getitem__(self, idx):
        img_path,cls_label = self.lines[idx].split("#")

        cls_label=int(cls_label)
        cls_label = torch.tensor(cls_label,dtype=torch.long)
        img_path = img_path
        #print(np.array(Image.open(img_path).resize((WIDTH,HEIGHT))).shape)
        #print(img_path)
        img = torch.tensor(np.array(Image.open(img_path).resize((WIDTH,HEIGHT))),dtype=torch.float).view(3,WIDTH,HEIGHT)
        return (cls_label,img)



