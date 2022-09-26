import os
from PIL import Image
import numpy as np
path = 'data'
Save_PATH = None
FILE_NAME = "Train_DATA"

file_name = open(FILE_NAME,"w+")
file_list = []
name_dict = {'bad':0,'fresh':1}
for _,__,files in os.walk(path):
    if len(__)==0:
        label = name_dict[_.split('\\')[-1]]
        for i in files:
            line = os.path.join(_,i)+'#'+str(label)+'\n'
            file_list.append(line)

file_name.writelines(file_list)
file_name.close()