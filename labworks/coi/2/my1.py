import cv2
import numpy as np

graph_img = np.zeros( (256,256,1), np.uint8)
graph_img.fill(255)
def set_current_a_trackbar_position(position):
    global a
    a = position
    drawW()

def set_current_b_trackbar_position(position):
    global b
    b = position 
    drawW()

def set_current_c_trackbar_position(position):
    global c
    c = position
    drawW()
    
def drawW():
    global a,b,c
    graph_img.fill(255)
    cv2.line(graph_img, (0,255),(85,255-int(a)),(0,0,0),1)
    cv2.line(graph_img, (85,255-int(a)),(170,255-int(b)),(0,0,0),1)
    cv2.line(graph_img, (170,255-int(b)),(255,255-int(c)),(0,0,0),1)
    cv2.imshow('graph', graph_img)
    
gray = cv2.imread('gradient_test.tif', 0)
result = gray.copy()

cv2.namedWindow('result',cv2.WINDOW_AUTOSIZE )
cv2.namedWindow('graph' )
cv2.createTrackbar('a', 'result', 0, 256, set_current_a_trackbar_position)
cv2.createTrackbar('b', 'result', 0, 256, set_current_b_trackbar_position)
cv2.createTrackbar('c', 'result', 0, 256, set_current_c_trackbar_position)
cv2.imshow('gray', gray)
a = 0
b = 0
c = 0
width, height = gray.shape

cv2.setTrackbarPos('c', 'result', 255)
cv2.setTrackbarPos('a', 'result', 85)
cv2.setTrackbarPos('b', 'result', 170)
while cv2.waitKey(1) & 0xFF != 27:
    for y in range(0, height-1):
        for x in range(0, width-1):
            pixel = gray.item(x, y)
            if 0<=pixel<85:
                pixel = pixel*a/85
            elif 85<=pixel<170:
                pixel = a + (pixel -85)*(b-a)/85
            elif 170<= pixel <=255:
                pixel = b+(pixel-170)*(c-b)/85
            if pixel >255:
                pixel = 255
            

            result.itemset(x, y, pixel)
    
    cv2.imshow('result', result)

cv2.destroyAllWindows();
