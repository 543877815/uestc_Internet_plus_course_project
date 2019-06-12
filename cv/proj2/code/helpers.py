# A set of helpers which are useful for debugging SIFT!
# Feel free to take a look around in case you are curious,
# but you shouldn't need to know exactly what goes on,
# and you certainly don't need to change anything

import scipy.io as scio
import numpy as np
import visualize

# Gives you the TA solution for the interest points you
# are attempting to find
def cheat_interest_points(eval_file, scale_factor):

	file_contents = scio.loadmat(eval_file)

	x1 = file_contents['x1']
	y1 = file_contents['y1']
	x2 = file_contents['x2']
	y2 = file_contents['y2']

	x1 = x1 * scale_factor
	y1 = y1 * scale_factor
	x2 = x2 * scale_factor
	y2 = y2 * scale_factor

	return x1, y1, x2, y2



def evaluate_correspondence(img_A, img_B, ground_truth_correspondence_file,
	scale_factor, x1_est, y1_est, x2_est, y2_est, matches, confidences, vis, filename="eval_corr.jpg"):

	# Sort the matches by their confidences into descending order of confidence 
	# (high confidence at low array index)
	conf_sorted = -np.sort(-confidences, kind='mergesort')
	conf_indices = np.argsort(-confidences, kind='mergesort')
	matches = matches[conf_indices,:]
	confidences = conf_sorted

	# 'unscale' interest points to compare with ground truth points
	x1_est_scaled = x1_est / scale_factor
	y1_est_scaled = y1_est / scale_factor
	x2_est_scaled = x2_est / scale_factor
	y2_est_scaled = y2_est / scale_factor

	# We want to see how good our matches are;
	# extract the coordinates of each matched point

	x1_matches = np.zeros(matches.shape[0])
	y1_matches = np.zeros(matches.shape[0])
	x2_matches = np.zeros(matches.shape[0])
	y2_matches = np.zeros(matches.shape[0])

	for i in range(matches.shape[0]):

		x1_matches[i] = x1_est_scaled[int(matches[i, 0])]
		y1_matches[i] = y1_est_scaled[int(matches[i, 0])]
		x2_matches[i] = x2_est_scaled[int(matches[i, 1])]
		y2_matches[i] = y2_est_scaled[int(matches[i, 1])]

	good_matches = np.zeros((matches.shape[0],1))

	# Loads `ground truth' positions x1, y1, x2, y2
	file_contents = scio.loadmat(ground_truth_correspondence_file)

	# x1, y1, x2, y2 = scio.loadmat(eval_file)
	x1 = file_contents['x1']
	y1 = file_contents['y1']
	x2 = file_contents['x2']
	y2 = file_contents['y2']

	uniqueness_dist = 150
	good_match_dist = 150

	good_match_counter = 0
	bad_match_counter = 0
	top_100_counter = 0

	# Used to keep track of which TA points the student has matched
	# to so the student only gets credit for matching a TA point once
	correct_matches = np.zeros(x2.shape[0])

	# for each ground truth point in image 1
	for i in range(x1.shape[0]):

		# 1. find the student points within uniqueness_dist pixels of the ground truth point
		x_dists = x1_matches - x1[i]
		y_dists = y1_matches - y1[i]

		# computes distances of each interest point to the ground truth point
		dists = np.sqrt(np.power(x_dists, 2.0) + np.power(y_dists, 2.0))

		# get indices of points where distance is < uniqueness_dist
		close_to_truth = dists < uniqueness_dist

		# 2. get the points in image1 and their corresponding matches in image2
		image1_x = x1_matches[close_to_truth]
		image1_y = y1_matches[close_to_truth]
		image2_x = x2_matches[close_to_truth]
		image2_y = y2_matches[close_to_truth]

		# 3. compute the distance of the student's image2 matches to the ground truth match
		x_dists_2 = image2_x - x2[i]
		y_dists_2 = image2_y - y2[i]

		dists_2 = np.sqrt(np.power(x_dists_2, 2.0) + np.power(y_dists_2, 2.0))

		# 4. matches within good_match_dist then count it as a correct match
		good = dists_2 < good_match_dist
		if np.sum(good) >= 1.0:
			correct_matches[i] = 1
			#good_match_counter += 1
			if i < 100:
				top_100_counter += 1
		else:
			bad_match_counter += 1

	precision = (np.sum(correct_matches) / x2.shape[0]) * 100.0
	accuracy100 = min(top_100_counter,100) # / 100) * 100# If we were testing more than the top 100, then this would be important.

	print(str(np.sum(correct_matches)) + " total good matches, " + str(bad_match_counter) + " total bad matches.")
	print(str(precision) + "% precision")
	print(str(accuracy100) + "% accuracy (top 100)")

	if vis > 0:
		print("Vizualizing...")
		# Rescale the points to the scaled input
		visualize.show_correspondences(img_A, img_B, \
				x1_est, y1_est, \
				x2_est, y2_est, \
				matches, filename)

	return accuracy100
