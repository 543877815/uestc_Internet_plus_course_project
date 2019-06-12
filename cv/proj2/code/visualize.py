
from skimage.feature import plot_matches
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import numpy as np

def show_correspondences(imgA, imgB, X1, Y1, X2, Y2, matches, mode='arrows', filename=None):
	'''
		Visualizes corresponding points between two images, either as
		arrows or dots

		mode='dots': Corresponding points will have the same random color
		mode='arrows': Corresponding points will be joined by a line

		Writes out a png of the visualization if 'filename' is not None.
	'''

	# generates unique figures so students can
	# look at all three at once
	fig, ax = plt.subplots(nrows=1, ncols=1)

	if mode == 'dots':
		print("dot visualization not implemented yet :(")

	else:
		kp1 = zip_x_y(Y1, X1)
		kp2 = zip_x_y(Y2, X2)
		matches = matches.astype(int)
		plot_matches(ax, imgA, imgB, kp1, kp2, matches)

	plt.show()

	if filename:
		plt.savefig(filename)

	return

def zip_x_y(x, y):
	zipped_points = []
	for i in range(len(x)):
		zipped_points.append(np.array([x[i], y[i]]))
	return np.array(zipped_points)
