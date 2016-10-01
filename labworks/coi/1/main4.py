import numpy as np
import cv2

def set_current_seeker_position(x):
        global current_position
        current_position = x

cap = cv2.VideoCapture('tree.avi')
frames_count = int(cap.get(cv2.cv.CV_CAP_PROP_FRAME_COUNT))

current_position = 0

cv2.namedWindow('video')
cv2.createTrackbar('s','video',0,frames_count,set_current_seeker_position)

while(True):
        current_position = cv2.getTrackbarPos('s','video')

        cap.set(cv2.cv.CV_CAP_PROP_POS_FRAMES, current_position)
        ret,frame = cap.read()

        if frame is not None:
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                cv2.imshow('video',gray)

        if cv2.waitKey(1) & 0xFF == 27:
                break
        current_position +=1
        cv2.setTrackbarPos('s','video',current_position)

cap.release()
cv2.destroyAllWindows()

