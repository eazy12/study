import cv2
import numpy as np
from matplotlib import pyplot as plt
img = cv2.imread('cameraman.tif',0)
hist, b = np.histogram( img, 256,(0, 255), True)
result = np.zeros(img.shape, img.dtype)
hist_cumsum = np.cumsum(hist)
plt.subplot(221)
plt.plot(hist_cumsum,"black")
plt.xlim([0,256])
plt.title("1")
plt.grid()
hist_cumsum = hist_cumsum * 256
plt.subplot(222)
plt.plot(hist_cumsum,"black")
plt.xlim([0,256])
plt.title("2")
plt.grid()
plt.show()
cv2.waitKey()
width, height = img.shape
for y in range(0, height-1):
    for x in range(0, width-1):
        pixel = img.item(x, y)
        pixel = hist_cumsum[pixel]
        result.itemset(x, y, pixel)
cv2.imshow("img", img)
cv2.imshow("result_img", result)
cv2.waitKey()
