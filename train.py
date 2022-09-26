import tqdm
import torchvision
import torchvision.transforms as transforms
import torch
import torchvision.models as models
import torch.nn as nn
import torch.optim as optim
import QualityData as qd
train_set = qd.QualityDataset('data.txt')
test_set = qd.QualityDataset('data.txt')
training_loader = torch.utils.data.DataLoader ( train_set , batch_size = 32 ,
shuffle = False )
test_loader = torch.utils.data.DataLoader ( test_set , batch_size = 32 ,
shuffle = False )
torch.manual_seed (0)

model =models.resnet18(pretrained=True)
model.fc = nn.Linear(512,2)
model.cuda()
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(),lr=0.001,momentum=0.9)
model.train()
for epoch in range(30):
    running_loss=0
    least_loss=0
    for i,data in tqdm(enumerate(training_loader,0)):
        label,img = data
        img.to("cuda")
        label.cuda()
        optimizer.zero_grad()
        outputs = model(img)

        loss = criterion(outputs,label)
        loss.backward()
        optimizer.step()
        running_loss +=loss.item()
        if i % 2000 == 1999:
            print('[%d, %5d] loss: %.3f' %
                  (epoch + 1, i + 1, running_loss / 2000))
            if running_loss <= least_loss:
                least_loss = running_loss
                state = {
    'epoch': epoch,
    'state_dict': model.state_dict(),
    'optimizer': optimizer.state_dict()

}

                running_loss = 0



print("finish training")