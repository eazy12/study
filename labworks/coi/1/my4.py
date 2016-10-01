import numpy as np
import cv2
drawing = False
a1 = []
b1 = []
img = cv2.imread('cameraman.tif',0)
img1 = cv2.imread('cameraman.tif',0)
img2 = img.copy()
img3 = img.copy()
img4 = np.zeros((1024,1024), np.uint8)
def draw_line(event,x,y,flags,param):
        global imgg,img,a1
        if event == cv2.EVENT_LBUTTONDOWN:
                a1.append((x,y))
        elif event== cv2.EVENT_LBUTTONUP:
                a1.append((x,y))
                imgg = img[a1[-2][1]:a1[-1][1], a1[-2][0]:a1[-1][0]].copy()
                cv2.rectangle(img, a1[-1], a1[-2],(0,0,0),3)
                img2 = imgg.copy()
                
def draw_line1(event,x,y,flags,param):
        global img1,imgg1,b1
        if event == cv2.EVENT_LBUTTONDOWN:
                b1.append((x,y))
        elif event== cv2.EVENT_LBUTTONUP:
                b1.append((x,y))
                imgg1 = img[b1[-2][1]:b1[-1][1], b1[-2][0]:b1[-1][0]].copy()
                cv2.rectangle(img1, b1[-2], b1[-1],(0,0,0),3)
                img3 = imgg1.copy()

cv2.namedWindow('image')
cv2.namedWindow('image1')
cv2.imshow('image',img)
cv2.imshow('image1',img1)
cv2.moveWindow('image1', 200, 200)
cv2.moveWindow('image', 10, 10)
cv2.setMouseCallback('image',draw_line)
cv2.setMouseCallback('image1',draw_line1)

while(1):
    cv2.imshow('image',img)
    cv2.imshow('image1',img1)
    if cv2.waitKey(1) & 0xFF == 27:
        a = b1[-1][1]-b1[-2][1]
        b = b1[-1][0]-b1[-2][0]
        c = a1[-1][0]-a1[-2][0]
        d = a1[-1][1]-a1[-2][1]
        m = c+b
        
        if d > a:
                maxi = d
        else:
                maxi = a
        img4[0:d, 0:c] = img2[a1[-2][1]:a1[-1][1], a1[-2][0]:a1[-1][0]].copy()
        img4[0:a ,c:m] = img3[b1[-2][1]:b1[-1][1], b1[-2][0]:b1[-1][0]].copy()
        img4 = img4[0:maxi,0:m].copy()
        cv2.imwrite('pict_4.jpg',img4)
        break
cv2.destroyAllWindows()

