"""
This code adapted from scikit-image documentation
http://scikit-image.org/docs/dev/auto_examples/features_detection/plot_corner.html

For CSCI1430 @ Brown University Spring 2019
"""

"""
================
Corner detection
================

Detect corner points using the Harris corner detector and determine the
subpixel position of corners ([1]_, [2]_).

.. [1] https://en.wikipedia.org/wiki/Corner_detection
.. [2] https://en.wikipedia.org/wiki/Interest_point_detection

"""

from matplotlib import pyplot as plt

from skimage import io, color, transform
from skimage.feature import corner_harris, peak_local_max

# load in different images to see where the Harris Corner Detector finds corners
image = transform.rescale(color.rgb2gray(io.imread("LaddObservatory1.jpg")),0.25)

harris_response = corner_harris(image)
# Note: Feel free to play with these parameters to investigate their effects
coords = peak_local_max( harris_response, min_distance=5, threshold_rel=0.05 )

plt.imshow(image, cmap=plt.cm.gray)
plt.plot(coords[:, 1], coords[:, 0], '+r', markersize=15)
plt.axis((-100, image.shape[1]+100, image.shape[0]+100, -100))
plt.show()