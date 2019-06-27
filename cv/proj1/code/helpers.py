# Project Image Filtering and Hybrid Images Stencil Code
# Based on previous and current work
# by James Hays for CSCI 1430 @ Brown and
# CS 4495/6476 @ Georgia Tech
import numpy as np
from numpy import pi, exp, sqrt
from skimage import io, img_as_ubyte, img_as_float32
from skimage.transform import rescale
import math
import cv2

def gen_hybrid_image_cv(image1, image2, cutoff_frequency):
    """
     Inputs:
     - image1 -> The image from which to take the low frequencies.
     - image2 -> The image from which to take the high frequencies.
     - cutoff_frequency -> The standard deviation, in pixels, of the Gaussian
                           blur that will remove high frequencies.

     Task:
     - Use my_imfilter to create 'low_frequencies' and 'high_frequencies'.
     - Combine them to create 'hybrid_image'.
    """
    assert image1.shape[0] == image2.shape[0]
    assert image1.shape[1] == image2.shape[1]
    assert image1.shape[2] == image2.shape[2]

    # Steps: (1) Remove the high frequencies from image1 by blurring it. The amount of blur that works best will vary
    #  with different image pairs generate a 1x(2k+1) gaussian kernel with mean=0 and sigma = s,
    # see https://stackoverflow.com/questions/17190649/how-to-obtain-a-gaussian-filter-in-python
    s, k = cutoff_frequency, cutoff_frequency * 2
    probs = np.asarray([exp(-z * z / (2 * s * s)) / sqrt(2 * pi * s * s) for z in range(-k, k + 1)], dtype=np.float32)
    kernel = np.outer(probs, probs)
    large_1d_blur_filter = kernel.reshape(-1,1)
    
    # Your code here:
   
    #large_blur_image1 = my_imfilter(large_blur_image1, large_1d_blur_filter.T)
    low_frequencies = cv2.filter2D(image1, -1, kernel)

    # (2) Remove the low frequencies from image2. The easiest way to do this is to
    #     subtract a blurred version of image2 from the original version of image2.
    #     This will give you an image centered at zero with negative values.
    # Your code here #
    large_blur_image2 = cv2.filter2D(image2, -1, kernel)
    #large_blur_image2 = my_imfilter(large_blur_image2, large_1d_blur_filter.T)
    high_frequencies = image2 - large_blur_image2  # Replace with your implementation

    # (3) Combine the high frequencies and low frequencies
    # Your code here #
    hybrid_image = low_frequencies + high_frequencies  # Replace with your implementation

    # (4) At this point, you need to be aware that values larger than 1.0
    # or less than 0.0 may cause issues in the functions in Python for saving
    # images to disk. These are called in proj1_part2 after the call to
    # gen_hybrid_image().
    # One option is to clip (also called clamp) all values below 0.0 to 0.0,
    # and all values larger than 1.0 to 1.0.
    for i in range(hybrid_image.shape[0]):
        for j in range(hybrid_image.shape[1]):
            for k in range(hybrid_image.shape[2]):
                if hybrid_image[i,j,k] > 1.0:
                    hybrid_image[i,j,k] = 1.0
                if hybrid_image[i,j,k] < 0.0:
                    hybrid_image[i,j,k] = 0.0
    return low_frequencies, high_frequencies, hybrid_image

# padding zero
def my_imfilter(image, filter):
    """
    Your function should meet the requirements laid out on the project webpage.
    Apply a filter to an image. Return the filtered image.
    Inputs:
    - image -> numpy nd-array of dim (m, n, c)
    - filter -> numpy nd-array of odd dim (k, l)
    Returns
    - filtered_image -> numpy nd-array of dim (m, n, c)
    Errors if:
    - filter has any even dimension -> raise an Exception with a suitable error message.
    """
    filter_reshape = filter.reshape(-1,1)
    filtered_image = np.zeros(image.shape) 
    filter_size = filter.size
    filter_size_sqrt = round(math.sqrt(filter_size))
    filter_size_ceil = math.ceil(filter_size_sqrt/2)
    filter_size_floor = math.floor(filter_size_sqrt/2)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if i>=filter_size_floor and i<=image.shape[0]-filter_size_ceil and j>=filter_size_floor and j<=image.shape[1]-filter_size_ceil:
                convolute_image = image[i-filter_size_floor:i+filter_size_ceil, j-filter_size_floor:j+filter_size_ceil]
                reshape_image = np.reshape(convolute_image[0:filter_size_sqrt,0:filter_size_sqrt], (filter_size,3))
                for k in range(filter_reshape.shape[0]):
                    filtered_image[i,j] += filter_reshape[k] * reshape_image[k]
    return filtered_image

# padding fix
def my_imfilter1(image, filter):
    """
    Your function should meet the requirements laid out on the project webpage.
    Apply a filter to an image. Return the filtered image.
    Inputs:
    - image -> numpy nd-array of dim (m, n, c)
    - filter -> numpy nd-array of odd dim (k, l)
    Returns
    - filtered_image -> numpy nd-array of dim (m, n, c)
    Errors if:
    - filter has any even dimension -> raise an Exception with a suitable error message.
    """
    filter_reshape = filter.reshape(-1,1)
    filter_size = filter.size
    filter_size_sqrt = round(math.sqrt(filter_size))
    filter_size_floor = math.floor(filter_size_sqrt/2)
    filtered_image = np.zeros(image.shape) 
    image_padding = np.zeros([image.shape[0] + 2 * filter_size_floor, image.shape[1] + 2 * filter_size_floor, image.shape[2]]) 
    image_padding[filter_size_floor:image_padding.shape[0]-filter_size_floor,filter_size_floor:image_padding.shape[1]-filter_size_floor] = image
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            convolute_image = image_padding[i:i+filter_size_sqrt, j:j+filter_size_sqrt]
            reshape_image = np.reshape(convolute_image[0:filter_size_sqrt,0:filter_size_sqrt], (filter_size,3))
            filtered_image[i,j] = sum(np.multiply(reshape_image, filter_reshape))
    return filtered_image

def gen_hybrid_image(image1, image2, cutoff_frequency):
    """
     Inputs:
     - image1 -> The image from which to take the low frequencies.
     - image2 -> The image from which to take the high frequencies.
     - cutoff_frequency -> The standard deviation, in pixels, of the Gaussian
                           blur that will remove high frequencies.

     Task:
     - Use my_imfilter to create 'low_frequencies' and 'high_frequencies'.
     - Combine them to create 'hybrid_image'.
    """

    assert image1.shape[0] == image2.shape[0]
    assert image1.shape[1] == image2.shape[1]
    assert image1.shape[2] == image2.shape[2]

    # Steps: (1) Remove the high frequencies from image1 by blurring it. The amount of blur that works best will vary
    #  with different image pairs generate a 1x(2k+1) gaussian kernel with mean=0 and sigma = s,
    # see https://stackoverflow.com/questions/17190649/how-to-obtain-a-gaussian-filter-in-python
    s, k = cutoff_frequency, cutoff_frequency * 2
    probs = np.asarray([exp(-z * z / (2 * s * s)) / sqrt(2 * pi * s * s) for z in range(-k, k + 1)], dtype=np.float32)
    kernel = np.outer(probs, probs)
    large_1d_blur_filter = kernel.reshape(-1,1)
    
    # Your code here:
    large_blur_image1 = my_imfilter1(image1, large_1d_blur_filter)
    low_frequencies = large_blur_image1

    # (2) Remove the low frequencies from image2. The easiest way to do this is to
    #     subtract a blurred version of image2 from the original version of image2.
    #     This will give you an image centered at zero with negative values.
    # Your code here #
    large_blur_image2 = my_imfilter1(image2, large_1d_blur_filter)
    # large_blur_image2 = my_imfilter(large_blur_image2, large_1d_blur_filter.T)
    high_frequencies = image2 - large_blur_image2  # Replace with your implementation

    # (3) Combine the high frequencies and low frequencies
    # Your code here #
    hybrid_image = low_frequencies + high_frequencies  # Replace with your implementation

    # (4) At this point, you need to be aware that values larger than 1.0
    # or less than 0.0 may cause issues in the functions in Python for saving
    # images to disk. These are called in proj1_part2 after the call to
    # gen_hybrid_image().
    # One option is to clip (also called clamp) all values below 0.0 to 0.0,
    # and all values larger than 1.0 to 1.0.
    for i in range(hybrid_image.shape[0]):
        for j in range(hybrid_image.shape[1]):
            for k in range(hybrid_image.shape[2]):
                if hybrid_image[i,j,k] > 1.0:
                    hybrid_image[i,j,k] = 1.0
                if hybrid_image[i,j,k] < 0.0:
                    hybrid_image[i,j,k] = 0.0
    return low_frequencies, high_frequencies, hybrid_image


def vis_hybrid_image(hybrid_image):
    """
    Visualize a hybrid image by progressively downsampling the image and
    concatenating all of the images together.
    """
    scales = 5
    scale_factor = 0.5
    padding = 5
    original_height = hybrid_image.shape[0]
    num_colors = 1 if hybrid_image.ndim == 2 else 3

    output = np.copy(hybrid_image)
    cur_image = np.copy(hybrid_image)
    for scale in range(2, scales + 1):
        # add padding
        output = np.hstack((output, np.ones((original_height, padding, num_colors),
                                            dtype=np.float32)))
        # downsample image
        cur_image = rescale(cur_image, scale_factor, mode='reflect')
        # pad the top to append to the output
        pad = np.ones((original_height - cur_image.shape[0], cur_image.shape[1],
                       num_colors), dtype=np.float32)
        tmp = np.vstack((pad, cur_image))
        output = np.hstack((output, tmp))
    return output


def load_image(path):
    return img_as_float32(io.imread(path))


def save_image(path, im):
    return io.imsave(path, img_as_ubyte(im.copy()))
