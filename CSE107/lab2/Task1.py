# Task 1
# imports
from PIL import Image, ImageOps
import numpy as np
from numpy import asarray

# open image file
im = Image.open('Beginnings.jpg')
im.show()

# convert to gray scale
im_gray = ImageOps.grayscale(im)
im_gray.show()

# calculate maximum pixel value
im_gray_pixels = asarray(im_gray)
rows, cols = im_gray_pixels.shape
max_pixel = 0
for row in range(rows):
    for col in range(cols):
        max_pixel = im_gray_pixels[row,col] if (im_gray_pixels[row,col] > max_pixel) else max_pixel

print("Maximum pixel value is: ", max_pixel)

# rotate image counter clockwise 90 degrees
im_gray_rotated_cc_pixels = np.zeros((cols,rows))
for row in range(rows):
    for col in range(cols):
        im_gray_rotated_cc_pixels[cols - col - 1,row] = im_gray_pixels[row,col]

im_gray_cc_rotated = Image.fromarray(np.uint8(im_gray_rotated_cc_pixels))
im_gray_cc_rotated.show()
im_gray_cc_rotated.save("Beginnings_grayscale_rotated_counterclockwise.jpg")

# rotate image clockwise 90 degrees
im_gray_rotated_c_pixels = np.zeros((cols,rows))
for row in range(rows):
    for col in range(cols):
        im_gray_rotated_c_pixels[col,rows - row - 1] = im_gray_pixels[row,col]

im_gray_c_rotated = Image.fromarray(np.uint8(im_gray_rotated_c_pixels))
im_gray_c_rotated.show()
im_gray_c_rotated.save("Beginnings_grayscale_rotated_clockwise.jpg")

# calculate maximum pixel value (rotated)
im_gray_pixels_rotated = asarray(im_gray_c_rotated)
rrows, rcols = im_gray_pixels_rotated.shape
rmax_pixel = 0
for row in range(rrows):
    for col in range(rcols):
        rmax_pixel = im_gray_pixels_rotated[row,col] if (im_gray_pixels_rotated[row,col] > rmax_pixel) else rmax_pixel

print("Maximum rotated pixel value is: ", rmax_pixel)