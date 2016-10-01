import numpy as np
import cv2
drawing = False
a = []
img = np.zeros((512,512,3), np.uint8)
img.fill(255)
def draw_line(event,x,y,flags,param):
        global img,a
        if event == cv2.EVENT_LBUTTONDOWN:
                a.append((x,y))
                if(len(a)%3 == 0):
                        cv2.line(img, a[-3], a[-2],(0,0,0),3)
                        cv2.line(img, a[-2], a[-1],(0,0,0),3)
                        cv2.line(img, a[-1], a[-3],(0,0,0),3)
cv2.namedWindow('image')
cv2.imshow('image',img)
cv2.moveWindow('image', 20, 20)
cv2.setMouseCallback('image',draw_line)

while(1):
    cv2.imshow('image',img)
    if cv2.waitKey(1) & 0xFF == 27:
        cv2.imwrite('pict_2.jpg',img)
        break
cv2.destroyAllWindows()

