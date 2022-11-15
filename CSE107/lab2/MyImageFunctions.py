# MyImageFunctions
# imports
import numpy as np

def myImageInverse(inImage_pixels):
# takes numpy matrix input of grayscale image and outputs 
# matrix of inverse values (each pixel output: 255 - input)
    rows, cols = inImage_pixels.shape
    outImage_pixels = np.zeros((rows,cols))

    for row in range(rows):
        for col in range(cols):
            outImage_pixels[row,col] = 255 - inImage_pixels[row,col]
    
    return outImage_pixels