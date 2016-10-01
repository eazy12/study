import numpy as np
import cv2

drawing = False
ix, iy = -1,-1

def draw_rect(event,x,y,flags,param):
        global ix,iy,drawing,mode,img,untouchedImg

        if event == cv2.EVENT_LBUTTONDOWN:
            drawing = True
            ix,iy= x,y
        elif event== cv2.EVENT_MOUSEMOVE:
            if drawing == True:
                img = untouchedImg.copy()
                cv2.rectangle(img, (ix,iy), (x,y),(0,0,0),3)
        elif event == cv2.EVENT_LBUTTONUP:
            drawing = False
            cv2.rectangle(img, (ix,iy), (x,y),(0,0,0),3)
            untouchedImg = img.copy()

img = np.zeros((512,512,3), np.uint8)
img.fill(255)
untouchedImg = img.copy()
cv2.namedWindow('image')
cv2.setMouseCallback('image',draw_rect)

while(1):
    cv2.imshow('image',img)
    if cv2.waitKey(1) & 0xFF == 27:
        break
cv2.destroyAllWindows()

