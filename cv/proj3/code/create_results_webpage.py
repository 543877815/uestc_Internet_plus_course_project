import matplotlib.pyplot as plt
import numpy as np
import warnings
import skimage
import glob
import os

from skimage import io

# Skimage gives us some lossy conversion errors that we really don't care about
# so we suppress them
warnings.filterwarnings('ignore', '', UserWarning)

def create_results_webpage(train_image_paths, test_image_paths,
	train_labels, test_labels,
	categories, abbr_categories, predicted_categories):

	'''
	Starter code prepared by James Hays for CSCI 1430 Computer Vision
	Converted to Python by Brendan Walsh

	This function creates a webpage (html and images) visualizing the
	classiffication results. This webpage will contain:
	 (1) A confusion matrix plot
	 (2) A table with one row per category, with 4 columns - training
		 examples, true positives, false positives, and false negatives.

	False positives are instances claimed as that category but belonging to
	another category, e.g. in the 'forest' row an image that was classified
	as 'forest' but is actually 'mountain'. This same image would be
	considered a false negative in the 'mountain' row, because it should have
	been claimed by the 'mountain' classifier but was not.

	This webpage is similar to the one created for the SUN database in
	2010: http://people.csail.mit.edu/jxiao/SUN/classification397.html
	'''

	print('Creating results_webpage/index.html, thumbnails, and confusion matrix.')

	# Number of examples of training examples, true positives, false positives,
	# and false negatives. Thus the table will be num_samples * 4 images wide
	# (unless there aren't enough images)
	num_samples = 2
	thumbnail_height = 75 #pixels
	num_categories = len(categories)

	# Convert everything over to numpy arrays
	categories = np.array(categories)
	predicted_categories = np.array(predicted_categories)
	train_labels = np.array(train_labels)
	test_labels = np.array(test_labels)

	# Delete the old thumbnails, if there are any
	files = glob.glob('results_webpage/thumbnails/*.jpg')
	for f in files:
		os.remove(f)

	if not os.path.isdir('results_webpage'):
		print('Making results_webpage directory.')
		os.mkdir('results_webpage')
	if not os.path.isdir('results_webpage/thumbnails'):
		print('Making thumbnails directory.')
		os.mkdir('results_webpage/thumbnails')

	### Create And Save Confusion Matrix ###
	# Based on the predicted category for each test case, we will now build a
	# confusion matrix. Entry (i,j) in this matrix well be the proportion of
	# times a test image of ground truth category i was predicted to be
	# category j. An identity matrix is the ideal case. You should expect
	# roughly 50-95% along the diagonal depending on your features,
	# classifiers, and particular categories. For example, suburb is very easy
	# to recognize.
	with open('results_webpage/index.html', 'w+') as f:

		# Initialize the matrix
		confusion_matrix = np.zeros((num_categories, num_categories))

		# Iterate over predicted results (this is like, several hundred items long)
		for i,cat in enumerate(predicted_categories):
			# Find the row and column corresponding to the label of this entry
			# The row is the ground truth label and the column is the found label
			row = np.argwhere(categories == test_labels[i])[0][0]
			column = np.argwhere(categories == predicted_categories[i])[0][0]

			# Add 1 to the matrix for that row/col
			# This way we build up a histogram from our labeled data
			confusion_matrix[row][column] += 1;

		# If the number of training examples and test cases are not equal, this
		# statement will be invalid!
		# TODO: That's an old comment left over from the matlab code that I don't
		# think still applies
		num_test_per_cat = len(test_labels) / num_categories
		confusion_matrix = confusion_matrix / float(num_test_per_cat)
		accuracy = np.mean(np.diag(confusion_matrix))

		print('Accuracy (mean of diagonal of confusion matrix) is {:2.3%}'.format(accuracy))

		# plasma is the most easily-interpreted color map I've found so far
		plt.imshow(confusion_matrix, cmap='plasma', interpolation='nearest')

		# We put the shortened labels (e.g. "sub" for "suburb") on the x axis
		locs, labels = plt.xticks()
		plt.xticks(np.arange(num_categories), abbr_categories)

		# Full labels go on y
		locs, labels = plt.yticks()
		plt.yticks(np.arange(num_categories), categories)

		# Save the result
		plt.savefig('results_webpage/confusion_matrix.png', bbox_inches='tight')

		## Create webpage header
		f.write('<!DOCTYPE html>\n');
		f.write('<html>\n');
		f.write('<head>\n');
		f.write('<link href=''http://fonts.googleapis.com/css?family=Nunito:300|Crimson+Text|Droid+Sans+Mono'' rel=''stylesheet'' type=''text/css''>\n');
		f.write('<style type="text/css">\n');

		f.write('body {\n');
		f.write('  margin: 0px;\n');
		f.write('  width: 100%;\n');
		f.write('  font-family: ''Crimson Text'', serif;\n');
		f.write('  background: #fcfcfc;\n');
		f.write('}\n');
		f.write('table td {\n');
		f.write('  text-align: center;\n');
		f.write('  vertical-align: middle;\n');
		f.write('}\n');
		f.write('h1 {\n');
		f.write('  font-family: ''Nunito'', sans-serif;\n');
		f.write('  font-weight: normal;\n');
		f.write('  font-size: 28px;\n');
		f.write('  margin: 25px 0px 0px 0px;\n');
		f.write('  text-transform: lowercase;\n');
		f.write('}\n');
		f.write('.container {\n');
		f.write('  margin: 0px auto 0px auto;\n');
		f.write('  width: 1160px;\n');
		f.write('}\n');

		f.write('</style>\n');
		f.write('</head>\n');
		f.write('<body>\n\n');

		f.write('<div class="container">\n\n\n');
		f.write('<center>\n');
		f.write('<h1>Scene classification results visualization</h1>\n');
		f.write('<img src="confusion_matrix.png">\n\n');
		f.write('<br>\n');
		f.write('Accuracy (mean of diagonal of confusion matrix) is %2.3f\n' % (accuracy));
		f.write('<p>\n\n');

		## Create results table
		f.write('<table border=0 cellpadding=4 cellspacing=1>\n');
		f.write('<tr>\n');
		f.write('<th>Category name</th>\n');
		f.write('<th>Accuracy</th>\n');
		f.write('<th colspan=%d>Sample training images</th>\n' % num_samples);
		f.write('<th colspan=%d>Sample true positives</th>\n' % num_samples);
		f.write('<th colspan=%d>False positives with true label</th>\n' % num_samples);
		f.write('<th colspan=%d>False negatives with wrong predicted label</th>\n' % num_samples);
		f.write('</tr>\n');

		for i,cat in enumerate(categories):
			f.write('<tr>\n');

			f.write('<td>'); #category name
			f.write('%s' % cat);
			f.write('</td>\n');

			f.write('<td>'); # category accuracy
			f.write('%.3f' % confusion_matrix[i][i]);
			f.write('</td>\n');

			# Collect num_samples random paths to images of each type.
			# Training examples.
			train_examples = np.take(train_image_paths, np.argwhere(train_labels == cat))

			# True positives. There might not be enough of these if the classifier
			# is bad
			true_positives = np.take(test_image_paths, np.argwhere(np.logical_and(test_labels == cat, predicted_categories == cat)))

			# False positives. There might not be enough of them if the classifier
			# is good
			false_positive_inds = np.argwhere(np.logical_and(np.invert(cat == test_labels), cat == predicted_categories))
			false_positives = np.take(test_image_paths, false_positive_inds)
			false_positive_labels = np.take(test_labels, false_positive_inds)

			# False negatives. There might not be enough of them if the classifier
			# is good
			false_negative_inds = np.argwhere(np.logical_and(cat == test_labels, np.invert(cat == predicted_categories)))
			false_negatives = np.take(test_image_paths, false_negative_inds)
			false_negative_labels = np.take(predicted_categories, false_negative_inds)

			# Randomize each list of files
			np.random.shuffle(train_examples)
			np.random.shuffle(true_positives)

			# HACK: Well, sort of a hack. We need to shuffle the false_positives
			# and their labels in the same exact order, so we get the RNG state,
			# save it, shuffle, restore, then shuffle the other list so that they
			# shuffle in tandem.
			rng_state = np.random.get_state()
			np.random.shuffle(false_positives)
			np.random.set_state(rng_state)
			np.random.shuffle(false_positive_labels)

			rng_state = np.random.get_state()
			np.random.shuffle(false_negatives)
			np.random.set_state(rng_state)
			np.random.shuffle(false_negative_labels)

			# Truncate each list to be at most num_samples long
			train_examples  = train_examples[0:min(len(train_examples), num_samples)]
			true_positives  = true_positives[0:min(len(true_positives), num_samples)]
			false_positives = false_positives[0:min(len(false_positives), num_samples)]
			false_positive_labels = false_positive_labels[0:min(len(false_positive_labels),num_samples)]
			false_negatives = false_negatives[0:min(len(false_negatives),num_samples)]
			false_negative_labels = false_negative_labels[0:min(len(false_negative_labels),num_samples)]

			# Sample training images
			# Create and save all of the thumbnails
			for j in range(num_samples):
				if j + 1 <= len(train_examples):
					thisExample = train_examples[j][0]
					tmp = skimage.io.imread(thisExample)
					height, width = rescale(tmp.shape, thumbnail_height)
					tmp = skimage.transform.resize(tmp, (height, width),
						anti_aliasing=True, mode='wrap')

					name = os.path.basename(thisExample)
					skimage.io.imsave('results_webpage/thumbnails/' + cat + '_' + name, tmp, quality=100)
					f.write('<td bgcolor=LightBlue>')
					f.write('<img src="%s" width=%d height=%d>' % ('thumbnails/' + cat + '_' + name, width, height))
					f.write('</td>\n')
				else:
					f.write('<td bgcolor=LightBlue>')
					f.write('</td>\n')

			for j in range(num_samples):
				if j + 1 <= len(true_positives):
					thisExample = true_positives[j][0]
					tmp = skimage.io.imread(thisExample)
					height, width = rescale(tmp.shape, thumbnail_height)
					tmp = skimage.transform.resize(tmp, (height, width),
						anti_aliasing=True, mode='wrap')

					name = os.path.basename(thisExample)
					skimage.io.imsave('results_webpage/thumbnails/' + cat + '_' + name, tmp, quality=100)
					f.write('<td bgcolor=LightGreen>');
					f.write('<img src="%s" width=%d height=%d>' % ('thumbnails/' + cat + '_' + name, width, height))
					f.write('</td>\n');
				else:
					f.write('<td bgcolor=LightGreen>');
					f.write('</td>\n');

			for j in range(num_samples):
				if j + 1 <= len(false_positives):
					thisExample = false_positives[j][0]
					tmp = skimage.io.imread(thisExample)
					height, width = rescale(tmp.shape, thumbnail_height)
					tmp = skimage.transform.resize(tmp, (height, width),
						anti_aliasing=True, mode='wrap')

					name = os.path.basename(thisExample)
					skimage.io.imsave('results_webpage/thumbnails/' + cat + '_' + name, tmp, quality=100)
					f.write('<td bgcolor=LightCoral>');
					f.write('<img src="%s" width=%d height=%d>' % ('thumbnails/' + cat + '_' + name, width, height))
					f.write('<br><small>%s</small>' % false_positive_labels[j][0]);
					f.write('</td>\n');
				else:
					f.write('<td bgcolor=LightCoral>');
					f.write('</td>\n');

			for j in range(num_samples):
				if j + 1 <= len(false_negatives):
					thisExample = false_negatives[j][0]
					tmp = skimage.io.imread(thisExample)
					height, width = rescale(tmp.shape, thumbnail_height)
					tmp = skimage.transform.resize(tmp, (height, width),
						anti_aliasing=True, mode='wrap')

					name = os.path.basename(thisExample)
					skimage.io.imsave('results_webpage/thumbnails/' + cat + '_' + name, tmp, quality=100)
					f.write('<td bgcolor=#FFBB55>');
					f.write('<img src="%s" width=%d height=%d>' % ('thumbnails/' + cat + '_' + name, width, height));
					f.write('<br><small>%s</small>' % false_negative_labels[j][0]);
					f.write('</td>\n');
				else:
					f.write('<td bgcolor=#FFBB55>');
					f.write('</td>\n');

			f.write('</tr>\n');

		f.write('<tr>\n');
		f.write('<th>Category name</th>\n');
		f.write('<th>Accuracy</th>\n');
		f.write('<th colspan=%d>Sample training images</th>\n' % num_samples);
		f.write('<th colspan=%d>Sample true positives</th>\n' % num_samples);
		f.write('<th colspan=%d>False positives with true label</th>\n' % num_samples);
		f.write('<th colspan=%d>False negatives with wrong predicted label</th>\n' % num_samples);
		f.write('</tr>\n');

		f.write('</table>\n');
		f.write('</center>\n\n\n');
		f.write('</div>\n');

		## Create end of web page
		f.write('</body>\n');
		f.write('</html>\n');

	print('Wrote results page to results_webpage/index.html.')

def rescale(dims, thumbnail_height):
	height = dims[1]
	factor = thumbnail_height / height
	left = int(round(dims[0] * factor))
	right = int(round(dims[1] * factor))
	return (left, right)
