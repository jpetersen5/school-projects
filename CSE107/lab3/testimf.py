# MyImageFunctions.py

# Import numpy
import numpy as np
from numpy import asarray
# For sqrt(), floor()
import math

def myImageResize(in_image_data, M, N, interpType):
    #in_image_data = asarray(in_image, dtype=np.float32)
    Minput, Ninput = in_image_data.shape

    #Find ratio of the size from scaled down from original
    x_ratio = M / np.size(in_image_data, 0)
    y_ratio = N / np.size(in_image_data, 1)
    
    newImage_data = np.zeros((M,N))

    outArray = np.array(newImage_data, dtype=np.float32)

    #For bilinear interpolation
    if interpType == 'bilinear':
        for row in range(M + 1):
            for col in range(N + 1):
                m_inter = (((row - 0.5) / M) * Minput) + 0.5
                n_inter = (((col - 0.5) / M) * Ninput) + 0.5

                #x axis
                if isinstance(m_inter, int):
                    m1 = m_inter - 1
                    m2 = m_inter - 1
                else:
                    if m_inter < 1:
                        m1 = 1
                        m2 = 2
                    elif m_inter > Minput:
                        m1 = M - 1
                        m2 = M
                    else:
                        m1 = math.floor(m_inter)
                        m2 = math.ceil(m_inter)

                #y axis
                if isinstance(n_inter, int):
                    n1 = n_inter - 1
                    n2 = n_inter - 1
                else:
                    if n_inter < 1:
                        n1 = 1
                        n2 = 2
                    elif n_inter > Ninput:
                        n1 = M - 1
                        n2 = M
                    else:
                        n1 = math.floor(n_inter)
                        n2 = math.ceil(n_inter)

                p1 = in_image_data[m1][n1]
                p2 = in_image_data[m1][n2]
                p3 = in_image_data[m2][n1]
                p4 = in_image_data[m2][n2]
                p5 = mybilinear(m1,n1,p1,m1,n2,p2,m2,n1,p3,m2,n2,p4,m_inter-1,n_inter-1)

                outArray[row - 1][col - 1] = p5
    return outArray

def myImageResize2( inImage_pixels, M, N, interpolation_method ):
    # NAME: myImageResize(inImage_pixels, M, N, interpolation_method)
    #
    # DESCRIPTION: Takes an input image and resizes it to an M x N image
    #              using the provided interpolation method
    #
    # INPUTS:  numpy array     inImage_pixels        an image as a numpy array
    #                                                using asarray() function
    #          int             M                     number of rows to resize to
    #          int             N                     number of columns to resize to
    #          string          interpolation_method  'nearest' or 'bilinear' for 
    #                                                nearest neighbor or bilinear
    #                                                interpolation methods respectively
    #
    # OUTPUTS: numpy array    outImage_pixels        the resized image as a numpy array
    #
    # NOTES:   Does not check for other inputs of interpolation_method; will 
    #          return a blank image of specified dimensions.
    inrows, incols = inImage_pixels.shape 
    rowScale = M / inrows   # calculate scales for interpolation
    colScale = N / incols   # the scale is the ratio of size between input and output
    outImage_pixels = np.zeros((M,N))  # define numpy matrix for output

    # nearest neighbor interpolation 
    # at each pixel in the output image, calculate the nearest neighbor using 
    # round() on the scaled row and column values. set the output pixel  
    # value to the calculated neighbor's pixel value from the input image
    if interpolation_method == "nearest":
        for row in range(M):
            for col in range(N):    # calculate nearest neighbor using scales and round functions
                # ensure nearest neighbor is chosen correctly (not out of bounds)
                nnrow = round(row/rowScale) if (round(row/rowScale) < inrows) else (inrows - 1)
                nncol = round(col/colScale) if (round(col/colScale) < incols) else (incols - 1)
                
                outImage_pixels[row,col] = inImage_pixels[nnrow, nncol]

    # bilinear interpolation
    # at each pixel in the output image, calculate the nearest 4 pixels
    # by using math.floor() and math.ceil() on the scaled row and column
    # values. retrieve the pixel values from these calculations, then 
    # plug all these values into mybilinear() formula to get pixel value
    if interpolation_method == "bilinear":
        for row in range(M):
            for col in range(N):    
                # scale to find position of desired pixel value
                x = row/rowScale
                y = col/colScale
                # calculate 4 nearest points (x1,y1), (x1,y2), (x2,y1), (x2,y2)
                # if statements ensure points do not exceed image bounds
                x1 = math.floor(x)
                x2 = math.ceil(x) if (math.ceil(x) < inrows) else (inrows - 1)
                y1 = math.floor(y)
                y2 = math.ceil(y) if (math.ceil(y) < incols) else (incols - 1)
                # retrieve pixel values 
                p1 = inImage_pixels[x1,y1]
                p2 = inImage_pixels[x1,y2]
                p3 = inImage_pixels[x2,y1]
                p4 = inImage_pixels[x2,y2]
                # account for if x = x1 = x2 or y = y1 = y2 
                # (prevent divide by zero error)
                if x2 == x1:
                    x2 = x2 + 1
                if y2 == y1:
                    y2 = y2 + 1

                outImage_pixels[row,col] = mybilinear2(x1,y1,x2,y2,p1,p2,p3,p4,x,y)
    
    return outImage_pixels


def myRMSE( first_im_pixels, second_im_pixels ):
    # NAME: myRMSE(first_im_pixels, second_im_pixels)
    #
    # DESCRIPTION: Takes two input matrices of the same dimensions and 
    #              calculates the similarity between them with RMSE formula
    #
    # INPUTS:  numpy array     first_im_pixels   a numpy array, typically of
    #                                            pixel values
    #          numpy array     second_im_pixels  a numpy array, typically of
    #                                            pixel values
    #
    # OUTPUTS: float           RMSE              the calculated "likeness" 
    #                                            between two matrices
    M, N = first_im_pixels.shape
    M2, N2 = second_im_pixels.shape
    # ensure input matrices are same size
    if not ((M2 == M) and (N2 == N)):
        print("RMSE sum impossible; matrices inconsistent")
        return 0
    RMSEsum = 0     # initialize for calculation loops
    
    # calculate RMSE
    # nested loop is used for nested sum from RMSE equation
    for m in range(M):
        for n in range(N):
            RMSEsum = RMSEsum + pow(first_im_pixels[m,n] - second_im_pixels[m,n], 2)
    # from RMSE equation
    RMSE = math.sqrt(1/(M*N) * RMSEsum)
    
    return RMSE


def mybilinear(x1,y1,p1,x2,y2,p2,x3,y3,p3,x4,y4,p4,x5,y5):
    r1 = (p3 + p1) * ((x5 - x1) / (x3 - x1))
    r2 = (p4 + p2) * ((x5 - x2) / (x4 - x2))
    p = (r2 + r1) * ((y5 - y1) / (y2 - y1))
    #r1 = (x2 - x) / (x2 - x1) * p1 + (x - x1) / (x2 - x1) * p3
    #r2 = (x2 - x) / (x2 - x1) * p2 + (x - x1) / (x2 - x1) * p4
    #p = (y2 - y) / (y2 - y1) * r1 + (y - y1) / (y2 - y1) * r2
    return p

def mybilinear2(x1,y1,x2,y2,p1,p2,p3,p4,x,y):
    # NAME: mybilinear(x1,y1,x2,y2,p1,p2,p3,p4,x,y)
    #
    # DESCRIPTION: Takes 4 x,y points and their values (x1,y1), (x1,y2), (x2,y1),
    #              and (x2,y2) and p1, p2, p3, p4 respectively, and a point (x,y)
    #              that exists between (x1,y1) and (x2,y2). The value of (x,y) is
    #              found using bilinear interpolation and returned as p
    #
    # INPUTS:  float          x1                     coordinate value of the left side
    #          float          y1                     coordinate value of the top side
    #          float          x2                     coordinate value of the right side
    #          float          y2                     coordinate value of the bottom side
    #          float          p1                     point weight of the top left point
    #          float          p2                     point weight of the bottom left point
    #          float          p3                     point weight of the top right point
    #          float          p4                     point weight of the bottom right point
    #          float          x                      coordinate value of the point to interpolate
    #          float          y                      coordinate value of the point to interpolate
    #
    # OUTPUTS: float          p                      The interpolated point weight at (x,y)
    #
    # NOTES:   x1 <= x <= x2 and y1 <= y <= y2
    # linear interpolation on (x,y1)
    r1 = (x2 - x) / (x2 - x1) * p1 + (x - x1) / (x2 - x1) * p3
    # linear interpolation on (x,y2)
    r2 = (x2 - x) / (x2 - x1) * p2 + (x - x1) / (x2 - x1) * p4
    # linear interpolation on (x,y) using previous interpolation values
    p = (y2 - y) / (y2 - y1) * r1 + (y - y1) / (y2 - y1) * r2
    # p is the pixel value to assign to output image
    return p