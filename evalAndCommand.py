import torchvision.models as models
import  dataset
import torch
import torch.nn as nn
model =models.resnet18(pretrained=False)
model.fc = nn.Linear(512,2)
model.load_state_dict(torch.load('savedModel'))
model.eval()
train_set = dataset.WC('Train_DATA')

training_loader = torch.utils.data.DataLoader ( train_set , batch_size = 4 ,
shuffle = False )
count = 0
rightNum =0
for i, data in enumerate(training_loader, 0):
    label, img = data


    outputs = model(img)
    outputs = torch.argmax(outputs,dim=1)
    right = torch.where(outputs-label==0,torch.tensor(1),torch.tensor(0))
    rightNum=torch.sum(right)+rightNum
    count=len(outputs)+count
print(rightNum/count)