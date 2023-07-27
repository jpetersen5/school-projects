import cv2 as cv
import math
#import numpy as np

"""
# takes in image as a matrix or filepath, removes the background through
# HSV manipulation, and returns the image with BG replaced with all white
# (useful for running through crop below)
def removeBG(img):
    # loads image from filepath if input is a string
    if isinstance(img, str):
        img = cv.imread(img)
    # convert to HSV
    imghsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    # remove saturation values less than half
    s = imghsv[:,:,1]
    s = np.where(s < 127, 0, 1)
    # increase brightness
    v = (imghsv[:,:,2] + 127) % 255
    v = np.where(v > 127, 1, 0)  # values above half will be part of mask
    # combine masks into "foreground"
    foreground = np.where(s+v > 0, 1, 0).astype(np.uint8)
    background = np.where(foreground==0,255,0).astype(np.uint8) # inverting foregound gives background
    background = cv.cvtColor(background, cv.COLOR_GRAY2BGR)  # convert background to RGB
    foreground=cv.bitwise_and(img,img,mask=foreground) # apply foreground to original image
    img = background+foreground # combine foreground and background
    return img
"""


# takes in an image and checks for contours then
# crops the image to the first object found using the countour's bounding rectangle
def crop(img):
    #img_nobg = removeBG(img)
    img = cv.imread(img)
    # conversion to a binary image
    img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    _, imgb = cv.threshold(img_gray, 100, 255, cv.THRESH_BINARY_INV)
    # dilate to simplify object shapes
    imgb = cv.dilate(imgb, None, iterations=2)
    # find contours
    contours, _ = cv.findContours(imgb,cv.RETR_LIST,cv.CHAIN_APPROX_SIMPLE)
    # find the bounding rectangle of the first object in the image
    boundRect = cv.boundingRect(contours[0])
    area = boundRect[3] * boundRect[2]
    crop = img[boundRect[0]:boundRect[0]+boundRect[2], boundRect[1]:boundRect[1]+boundRect[3]]
    # use the area to find the biggest object (most likely the coin)
    # crop boundaries using bounding rectangle
    # img[x:x+w, y:y+h]
    for i in contours:
        x,y,w,h = cv.boundingRect(i)
        if (area < w * h):
            area = w * h
            crop = img[y:(y+h),x:(x+w)]
    return crop

def overlap(x1,y1, x2,y2, threshold=10):
    distance = math.sqrt((x1 - x2)**2 + (y1 - y2)**2)
    return distance <= threshold