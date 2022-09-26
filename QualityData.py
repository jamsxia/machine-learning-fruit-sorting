from torch.utils.data import Dataset, DataLoader
import torch
from PIL import Image
import numpy as np
class QualityDataset(Dataset):
    def __init__(self,path):
        self.f = open('data.txt','r')
        self.contents = self.f.readlines()
    def __len__(self):
        return len(self.contents)
    def __getitem__(self,idx):
        img_path,label = self.contents[idx].split('#')
        label = label[:-1]
        img = Image.open(img_path).convert('RGB').resize((300,300))
        img = np.asarray(img)
        img = torch.from_numpy(img)
        return img,label


