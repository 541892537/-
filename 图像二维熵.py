import cv2
import matplotlib.pyplot as plt
import numpy as np
import os
import glob
import time
def calc_2D_Entropy(x):
    img=cv2.imread(x,0)#读取图像
    S=img.shape
    print(S)
    IJ=[]
    F={}
    Start_time = time.perf_counter()
    for row in range(S[0]):
        for col in range(S[1]):
            Left_x=max(0,col-1)
            Right_x=min(S[1],col+2)
            up_y=max(0,row-1)
            down_y=min(S[0],row+2)
            region=img[up_y:down_y,Left_x:Right_x] # 九宫格区域
            j=(np.sum(region)-img[row][col])/(8)
            IJ.append((img[row][col],j))
            F[(img[row][col],j)]=0
    End_time = time.perf_counter()
    print("程序运行时间:%s秒" % ((End_time - Start_time)))
    for i in IJ:
        F[i]=F[i]+1
    sq=(int)(S[0]*S[1])#计算pij
    G=F.values()
    P=[]
    for i in G:
        P.append(i/sq)
    End_time = time.perf_counter()
    print("程序运行时间:%s秒" % ((End_time - Start_time)))
    E=np.sum([p*np.log2(p) for p in P])#二维熵
    print("E=",E)
    
if __name__== "__main__" :
    Start_time = time.perf_counter()
    WSI_MASK_PATH = 'C:\\Users\\Mr_cold\\Desktop\\data\\L01'#存放图片的文件夹路径
    paths = glob.glob(os.path.join(WSI_MASK_PATH, '*.jpg'))
    print(paths)
    for x in paths:
        calc_2D_Entropy(x)
    End_time = time.perf_counter()
    print("程序运行时间:%s秒" % ((End_time - Start_time)))
