import numpy as np
import matplotlib
from skimage.io import imread
from skimage.color import rgb2grey
from skimage.feature import hog
from skimage.transform import resize
from sklearn.cluster import KMeans
from sklearn.neighbors import KNeighborsClassifier
from sklearn.neighbors import KDTree
from sklearn import svm
from scipy.spatial.distance import cdist
import cv2
from tqdm import tqdm
import random

from sklearn.model_selection import GridSearchCV
from PIL import Image
import scipy.spatial.distance as distance
from cyvlfeat.sift.dsift import dsift
from cyvlfeat.kmeans import kmeans
from time import time
import pickle
 


def get_tiny_images(image_paths):
    '''
    This feature is inspired by the simple tiny images used as features in
    80 million tiny images: a large dataset for non-parametric object and
    scene recognition. A. Torralba, R. Fergus, W. T. Freeman. IEEE
    Transactions on Pattern Analysis and Machine Intelligence, vol.30(11),
    pp. 1958-1970, 2008. http://groups.csail.mit.edu/vision/TinyImages/
    Inputs:
        image_paths: a 1-D Python list of strings. Each string is a complete
                     path to an image on the filesystem.
    Outputs:
        An n x d numpy array where n is the number of images and d is the
        length of the tiny image representation vector. e.g. if the images
        are resized to 16x16, then d is 16 * 16 = 256.
    To build a tiny image feature, resize the original image to a very small
    square resolution (e.g. 16x16). You can either resize the images to square
    while ignoring their aspect ratio, or you can crop the images into squares
    first and then resize evenly. Normalizing these tiny images will increase
    performance modestly.
    As you may recall from class, naively downsizing an image can cause
    aliasing artifacts that may throw off your comparisons. See the docs for
    skimage.transform.resize for details:
    http://scikit-image.org/docs/dev/api/skimage.transform.html#skimage.transform.resize
    Suggested functions: skimage.transform.resize, skimage.color.rgb2grey,
                         skimage.io.imread, np.reshape
    '''

    #TODO: Implement this function!
    image_feats = []
    size = 16
    for image_path in tqdm(image_paths, desc="Image-tiny"):
        image = cv2.imread(image_path)
        image = cv2.resize(image, (size, size))
        # column vector
        image_feat = np.resize(image, [size * size])
        image_feat = image_feat.tolist()
        # Normalizing
        mean = np.mean(image_feat)
        image_feat = [(value - mean) for value in image_feat]
        image_feats.append(image_feat)
    return np.array(image_feats)

def build_vocabulary(image_paths, vocab_size):
    '''
    This function should sample HOG descriptors from the training images,
    cluster them with kmeans, and then return the cluster centers.
    Inputs:
        image_paths: a Python list of image path strings
         vocab_size: an integer indicating the number of words desired for the
                     bag of words vocab set
    Outputs:
        a vocab_size x (z*z*9) (see below) array which contains the cluster
        centers that result from the K Means clustering.
    You'll need to generate HOG features using the skimage.feature.hog() function.
    The documentation is available here:
    http://scikit-image.org/docs/dev/api/skimage.feature.html#skimage.feature.hog
    However, the documentation is a bit confusing, so we will highlight some
    important arguments to consider:
        cells_per_block: The hog function breaks the image into evenly-sized
            blocks, which are further broken down into cells, each made of
            pixels_per_cell pixels (see below). Setting this parameter tells the
            function how many cells to include in each block. This is a tuple of
            width and height. Your SIFT implementation, which had a total of
            16 cells, was equivalent to setting this argument to (4,4).
        pixels_per_cell: This controls the width and height of each cell
            (in pixels). Like cells_per_block, it is a tuple. In your SIFT
            implementation, each cell was 4 pixels by 4 pixels, so (4,4).
        feature_vector: This argument is a boolean which tells the function
            what shape it should use for the return array. When set to True,
            it returns one long array. We recommend setting it to True and
            reshaping the result rather than working with the default value,
            as it is very confusing.
    It is up to you to choose your cells per block and pixels per cell. Choose
    values that generate reasonably-sized feature vectors and produce good
    classification results. For each cell, HOG produces a histogram (feature
    vector) of length 9. We want one feature vector per block. To do this we
    can append the histograms for each cell together. Let's say you set
    cells_per_block = (z,z). This means that the length of your feature vector
    for the block will be z*z*9.
    With feature_vector=True, hog() will return one long np array containing every
    cell histogram concatenated end to end. We want to break this up into a
    list of (z*z*9) block feature vectors. We can do this using a really nifty numpy
    function. When using np.reshape, you can set the length of one dimension to
    -1, which tells numpy to make this dimension as big as it needs to be to
    accomodate to reshape all of the data based on the other dimensions. So if
    we want to break our long np array (long_boi) into rows of z*z*9 feature
    vectors we can use small_bois = long_boi.reshape(-1, z*z*9).
    The number of feature vectors that come from this reshape is dependent on
    the size of the image you give to hog(). It will fit as many blocks as it
    can on the image. You can choose to resize (or crop) each image to a consistent size
    (therefore creating the same number of feature vectors per image), or you
    can find feature vectors in the original sized image.
    ONE MORE THING
    If we returned all the features we found as our vocabulary, we would have an
    absolutely massive vocabulary. That would make matching inefficient AND
    inaccurate! So we use K Means clustering to find a much smaller (vocab_size)
    number of representative points. We recommend using sklearn.cluster.KMeans
    to do this. Note that this can take a VERY LONG TIME to complete (upwards
    of ten minutes for large numbers of features and large max_iter), so set
    the max_iter argument to something low (we used 100) and be patient. You
    may also find success setting the "tol" argument (see documentation for
    details)
    '''
    
    #TODO: Implement this function!
    # cluster_SIFT_features = []
    # sift = cv2.xfeatures2d.SIFT_create()
    # for image_path in tqdm(image_paths, desc="Imaging-SIFT"):
    #     image = cv2.imread(image_path)
    #     gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    #     locations, SIFT_features = sift.detectAndCompute(gray, None)
    #     temp = SIFT_features.tolist()
    #     cluster_SIFT_features += temp
    # cluster_SIFT_features = random.sample(cluster_SIFT_features, 400 * 3)
    # kmeans = KMeans(n_clusters=vocab_size, max_iter=100).fit(cluster_SIFT_features)
    # cluster_centers = kmeans.cluster_centers_
    # return np.array(cluster_centers)


    bag_of_features = []
    
    print("Extract SIFT features")
    #pdb.set_trace()
    for path in tqdm(image_paths,desc='build_vocabulary'):
        img = np.asarray(Image.open(path),dtype='float32')
        frames, descriptors = dsift(img, step=[5,5], fast=True)
        bag_of_features.append(descriptors)
    bag_of_features = np.concatenate(bag_of_features, axis=0).astype('float32')
    #pdb.set_trace()
    print("Compute vocab")
    start_time = time()
    vocab = kmeans(bag_of_features, vocab_size, initialization="PLUSPLUS")        
    end_time = time()
    print("It takes ", (start_time - end_time), " to compute vocab.")
    return vocab

def get_bags_of_words(image_paths):
    '''
    This function should take in a list of image paths and calculate a bag of
    words histogram for each image, then return those histograms in an array.
    Inputs:
        image_paths: A Python list of strings, where each string is a complete
                     path to one image on the disk.
    Outputs:
        An nxd numpy matrix, where n is the number of images in image_paths and
        d is size of the histogram built for each image.
    Use the same hog function to extract feature vectors as before (see
    build_vocabulary). It is important that you use the same hog settings for
    both build_vocabulary and get_bags_of_words! Otherwise, you will end up
    with different feature representations between your vocab and your test
    images, and you won't be able to match anything at all!
    After getting the feature vectors for an image, you will build up a
    histogram that represents what words are contained within the image.
    For each feature, find the closest vocab word, then add 1 to the histogram
    at the index of that word. For example, if the closest vector in the vocab
    is the 103rd word, then you should add 1 to the 103rd histogram bin. Your
    histogram should have as many bins as there are vocabulary words.
    Suggested functions: scipy.spatial.distance.cdist, np.argsort,
                         np.linalg.norm, skimage.feature.hog
    '''

    # vocab = np.load('vocab.npy')
    # print('Loaded vocab from file.')

    # #TODO: Implement this function!
    # vocab_size = len(image_paths)
    # tree = KDTree(vocab)
    # cluster_SIFT_features = []
    # sift = cv2.xfeatures2d.SIFT_create()
    # for image_path in tqdm(image_paths, desc='SIFT'):
    #     image_bag = [0] * vocab_size
    #     image = cv2.imread(image_path)
    #     gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    #     locations, SIFT_features = sift.detectAndCompute(gray, None)
    #     temp = SIFT_features.tolist()
    #     nearest_dist, nearest_ind = tree.query(temp, k=1)
    #     for index in nearest_ind:
    #         image_bag[int(index)] += 1
    #     cluster_SIFT_features.append(image_bag)
    # return np.array(cluster_SIFT_features)


    with open('vocab.pkl', 'rb') as v:
        vocab = pickle.load(v)
        image_feats = np.zeros((len(image_paths),len(vocab)))
        
    for i, path in tqdm(enumerate(image_paths), desc='get_bags_of_words'):
        
        image = np.asarray(Image.open(path), dtype = 'float32')
        frames, descriptors = dsift(image, step=[9,9], fast=True)
        
        dist = distance.cdist(vocab, descriptors, 'euclidean')
        mdist = np.argmin(dist, axis = 0)
        histo, bins = np.histogram(mdist, range(len(vocab)+1))
        if np.linalg.norm(histo) == 0:
            image_feats[i, :] = histo
        else:
            image_feats[i, :] = histo / np.linalg.norm(histo)
    return image_feats

def svm_classify(train_image_feats, train_labels, test_image_feats):
    '''
    This function will predict a category for every test image by training
    15 many-versus-one linear SVM classifiers on the training data, then
    using those learned classifiers on the testing data.
    Inputs:
        train_image_feats: An nxd numpy array, where n is the number of training
                           examples, and d is the image descriptor vector size.
        train_labels: An nx1 Python list containing the corresponding ground
                      truth labels for the training data.
        test_image_feats: An mxd numpy array, where m is the number of test
                          images and d is the image descriptor vector size.
    Outputs:
        An mx1 numpy array of strings, where each string is the predicted label
        for the corresponding image in test_image_feats
    We suggest you look at the sklearn.svm module, including the LinearSVC
    class. With the right arguments, you can get a 15-class SVM as described
    above in just one call! Be sure to read the documentation carefully.
    '''

    # TODO: Implement this function!
    clf = svm.SVC(C=100, gamma='scale', decision_function_shape="ovr")
    clf.fit(train_image_feats, train_labels)
    predicted_categories = clf.predict(test_image_feats)
    return np.array(predicted_categories)

    # svc = svm.SVC(random_state=0)
    # param_C = [0.001 , 0.01 , 0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0]
    # param_gamma = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1.0]
    # param_grid = [{'C': param_C,
    #                'gamma': param_gamma,
    #                'kernel': ['rbf']}]

    # gs = GridSearchCV(estimator = svc,
    #                   param_grid= param_grid,
    #                   scoring='accuracy',
    #                  )
    
    # gs = gs.fit(train_image_feats, train_labels)
    
    # print(f'Best Training Score = {gs.best_score_:.3f} with parameters {gs.best_params_}')
    
    # classifier = gs.best_estimator_
    # classifier.fit(train_image_feats, train_labels)
    
    
    # pred_label = classifier.predict(test_image_feats)
    # return  np.array(pred_label)


def nearest_neighbor_classify(train_image_feats, train_labels, test_image_feats):
    '''
    This function will predict the category for every test image by finding
    the training image with most similar features. You will complete the given
    partial implementation of k-nearest-neighbors such that for any arbitrary
    k, your algorithm finds the closest k neighbors and then votes among them
    to find the most common category and returns that as its prediction.
    Inputs:
        train_image_feats: An nxd numpy array, where n is the number of training
                           examples, and d is the image descriptor vector size.
        train_labels: An nx1 Python list containing the corresponding ground
                      truth labels for the training data.
        test_image_feats: An mxd numpy array, where m is the number of test
                          images and d is the image descriptor vector size.
    Outputs:
        An mx1 numpy list of strings, where each string is the predicted label
        for the corresponding image in test_image_feats
    The simplest implementation of k-nearest-neighbors gives an even vote to
    all k neighbors found - that is, each neighbor in category A counts as one
    vote for category A, and the result returned is equivalent to finding the
    mode of the categories of the k nearest neighbors. A more advanced version
    uses weighted votes where closer matches matter more strongly than far ones.
    This is not required, but may increase performance.
    Be aware that increasing k does not always improve performance - even
    values of k may require tie-breaking which could cause the classifier to
    arbitrarily pick the wrong class in the case of an even split in votes.
    Additionally, past a certain threshold the classifier is considering so
    many neighbors that it may expand beyond the local area of logical matches
    and get so many garbage votes from a different category that it mislabels
    the data. Play around with a few values and see what changes.
    Useful functions:
        scipy.spatial.distance.cdist, np.argsort, scipy.stats.mode
    '''


    # Gets the distance between each test image feature and each train image feature
    # e.g., cdist

    #TODO:
    # 1) Find the k closest features to each test image feature in euclidean space
    # 2) Determine the labels of those k features
    # 3) Pick the most common label from the k
    # 4) Store that label in a list

    k = 7
    distances = cdist(test_image_feats, train_image_feats, 'euclidean')
    predicted_categories = []
    for i in range(len(distances)):
        min_distance_index = distances[i].argsort()
        k_neighbor = min_distance_index[:k]
        labels = [train_labels[x] for x in k_neighbor]
        label = max(labels, key=labels.count)
        predicted_categories.append(label)
    return np.array(predicted_categories)

    # use sklearn
    # classifier = KNeighborsClassifier(n_neighbors=k, metric="manhattan")
    # classifier.fit(train_image_feats, train_labels)
    # predicted_categories = classifier.predict(test_image_feats)
    # return np.array([predicted_categories])