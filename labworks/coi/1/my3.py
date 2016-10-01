import numpy as np
import cv2
drawing = False
a = []
img = cv2.imread('cameraman.tif',0)
def draw_line(event,x,y,flags,param):
        global img,a,img1
        if event == cv2.EVENT_LBUTTONDOWN:
                a.append((x,y))
        elif event == cv2.EVENT_LBUTTONUP:
                a.append((x,y))
                img1 = img[a[-2][1]:a[-1][1], a[-2][0]:a[-1][0]].copy()
                cv2.rectangle(img, a[-1], a[-2],(0,0,0),3)
cv2.namedWindow('image')
cv2.imshow('image',img)
cv2.moveWindow('image', 20, 20)
cv2.setMouseCallback('image',draw_line)

while(1):
    cv2.imshow('image',img)
    if cv2.waitKey(1) & 0xFF == 27:
        cv2.imwrite('pict_3.jpg',img1)
        break
cv2.destroyAllWindows()

