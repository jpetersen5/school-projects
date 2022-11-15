# Task 2
# imports
from PIL import Image
import numpy as np
from numpy import asarray
from MyImageFunctions import myImageInverse

# open image file
im = Image.open('Watertower.tif')
print("image mode is:", im.mode)
im.show()

# pixel values matrices
im_pixels = asarray(im)
im_inv_pixels = myImageInverse(im_pixels)

# create new inverted image
im_inv = Image.fromarray(np.uint8(im_inv_pixels))
im_inv.show()
im_inv.save("Watertower_inv.tif")

# calculate maximum pixel value of inverted image
rows, cols = im_inv_pixels.shape
max_pixel = 0
for row in range(rows):
    for col in range(cols):
        max_pixel = im_inv_pixels[row,col] if (im_inv_pixels[row,col] > max_pixel) else max_pixel

print("Maximum pixel value is: ", max_pixel)