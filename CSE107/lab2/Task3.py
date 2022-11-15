# Task 3
# imports
from PIL import Image
import numpy as np
from numpy import asarray

# initialize variables
rows = 100
cols = 256

# create image matrix of size
im_pixels = np.zeros(shape=(rows, cols))

# calculate values
for row in range(rows):
    for col in range(cols):
        im_pixels[row,col] = col

# create, display, save image
im = Image.fromarray(np.uint8(im_pixels))
im.show()
im.save("Gradient.tif")

# calculate pixel average
pixel_sum = 0
for row in range(rows):
    for col in range(cols):
        pixel_sum += im_pixels[row,col]

pixel_avg = pixel_sum / (rows * cols)
print("Average pixel value: ", pixel_avg)