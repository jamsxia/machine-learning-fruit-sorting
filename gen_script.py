import os
label = {'bad':0,'good':1}
contents = list()
for root, dirs, files in os.walk('data'):
    if len(dirs)==0:
        for i in range(len(files)):
            line = root+"\\"+files[i]+'#'+str(label[root.split('\\')[-1]])+'\n'
            contents.append(line)
f = open('data.txt','w')
f.writelines(contents)