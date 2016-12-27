import cv2
import numpy as np
import aruco
import math
import sys

cv2.namedWindow("sourceImage", cv2.WINDOW_NORMAL)
cv2.namedWindow("binaryImage", cv2.WINDOW_NORMAL)
cv2.namedWindow("bilateralFilter", cv2.WINDOW_NORMAL)
cv2.namedWindow("Thresholded", cv2.WINDOW_NORMAL)
cv2.namedWindow("final", cv2.WINDOW_NORMAL)
cv2.namedWindow("crop", cv2.WINDOW_NORMAL)
cv2.moveWindow("sourceImage",100,100)
cv2.moveWindow("binaryImage",430,100)
cv2.moveWindow("bilateralFilter",760,100)
cv2.moveWindow("Thresholded",1090,100)
cv2.moveWindow("final",100,400)
cv2.moveWindow("crop",430,400)

sourceImage = cv2.imread(sys.argv[1], 1)
cv2.imshow('sourceImage', sourceImage)

binaryImage = np.zeros( sourceImage.shape[0:2] ,  sourceImage.dtype )
cv2.cvtColor(sourceImage, cv2.COLOR_BGR2GRAY ,binaryImage)
cv2.imshow('binaryImage', binaryImage)

blur = cv2.medianBlur(binaryImage,55)
cv2.imshow('bilateralFilter', blur)

thresholded=cv2.adaptiveThreshold(blur,255,cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY,55,2)
cv2.imshow('Thresholded', thresholded)

dictionary = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_ARUCO_ORIGINAL)
corners, ids, rejected = cv2.aruco.detectMarkers(thresholded, dictionary)
print(corners)
if corners !=[]:
    dist = math.sqrt( (corners[0][0][0][0]-corners[0][0][1][0])**2+ (corners[0][0][0][1]-corners[0][0][1][1])**2 )
    dist /=3.5
    print("1 сантиметр равен " ,dist, " пикселям")
else:
    print("There is no marker here.")
    sys.exit()
# dist = math.sqrt(corners[0][0][0]*corners[0][0][0] - corners[0][1]*corners[0][1])


image, contours, hierarchy = cv2.findContours(thresholded,  cv2.RETR_TREE, cv2.CHAIN_APPROX_TC89_L1)
a = []
b = []
d=[]
arr = []
for i in contours:
    d.append(cv2.approxPolyDP(i, 20, True) )
    x,y,w,h = cv2.boundingRect(d[-1])
    arr.append([x,y,w,h,w*h])
    #cv2.rectangle(sourceImage,(x,y),(x+w,y+h),(0,255,0),2)

arr.sort(key=lambda tup: tup[4])
crop_img = thresholded[ arr[-2][1] : (arr[-2][1]+arr[-2][3]) , arr[-2][0] : (arr[-2][0]+arr[-2][2]) ]
for i, value in enumerate(arr):
    if(value[2]>dist or value[3]>dist):
        cv2.rectangle(sourceImage, (arr[i][0],arr[i][1]) ,(arr[i][0]+arr[i][2],arr[i][1]+arr[i][3]),(0,255,0),2)
        dist2 = max(arr[i][2], arr[i][3])
        cv2.putText(sourceImage, str(dist2/dist), ((arr[i][0]+10),(arr[i][1] +10)), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,255,255))
cv2.imshow('crop', crop_img)



cv2.imshow('final', sourceImage)



cv2.waitKey(0)
cv2.destroyAllWindows()
