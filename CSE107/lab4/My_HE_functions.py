# MyHEFunctions.py

# Import numpy
import numpy as np

def compute_histogram( image_pixels ):
    # compute_histogram  Computes the normalized histogram of 
    # an input grayscale image
    #
    # Syntax:
    #   compute_histogram( image_pixels )
    #
    # Input:
    #   image_pixels = the numpy matrix of pixel values from 
    #   a grayscale image
    #
    # Output:
    #   hist = a length 256 histogram vector of probabilities
    #   at their respective pixel values
    #
    # History:
    #   J. Petersen     11/2/2022   created
    inrows, incols = image_pixels.shape
    hist = np.zeros(shape=(256))
    
    for row in range(inrows):
        for col in range(incols):
            hist[int(image_pixels[row][col])] += 1

    hist = hist / (inrows * incols)

    return hist


def equalize( in_image_pixels ):
    # equalize  Computes the equalized histogram of 
    # an input grayscale image
    #
    # Syntax:
    #   equalize( in_image_pixels )
    #
    # Input:
    #   in_image_pixels = the numpy matrix of pixel values from 
    #   a grayscale image
    #
    # Output:
    #   out_image_pixels = the numpy matrix of pixel values calculated
    #   through equalization to create a better contrast image
    #
    # History:
    #   J. Petersen     11/2/2022   created
    hist = compute_histogram(in_image_pixels)
    transform_vec = np.zeros(shape=(256))

    L = 256     # number of possible intensity levels in the image

    for k in range(L):
        for i in range(k):
            transform_vec[k] += hist[i]
        transform_vec[k] = (L - 1) * transform_vec[k]   # from 3-15 in the textbook
    
    inrows, incols = in_image_pixels.shape
    out_image_pixels = np.zeros((inrows,incols))

    for row in range(inrows):
        for col in range(incols):
            out_image_pixels[row][col] = transform_vec[int(in_image_pixels[row][col])]
    
    return out_image_pixels


def plot_histogram( hist ):
    # plot_histgram  Plots the length 256 numpy vector representing the normalized
    # histogram of a grayscale image.
    #
    # Syntax:
    #   plot_histogram( hist )
    #
    # Input:
    #   hist = The length 256 histogram vector..
    #
    # Output:
    #   none
    #
    # History:
    #   S. Newsam     10/23/2022   created

    # Import plotting functions from matplotlib.
    import matplotlib.pyplot as plt

    plt.bar( range(256), hist )

    plt.xlabel('intensity value')

    plt.ylabel('PMF'); 

    plt.show()
