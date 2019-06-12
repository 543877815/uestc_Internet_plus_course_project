import os
import glob

def get_image_paths(data_path, categories, num_train_per_cat):
    '''
    This function returns lists containing the file path for each train
    and test image, as well as lists with the label of each train and
    test image. By default both lists will be 1500x1, where each
    entry is a char array (or string).
    '''

    num_categories = len(categories) # number of scene categories.

    # This paths for each training and test image. By default it will have 1500
    # entries (15 categories * 100 training and test examples each)
    train_image_paths = [None] * (num_categories * num_train_per_cat)
    test_image_paths  = [None] * (num_categories * num_train_per_cat)

    # The name of the category for each training and test image. With the
    # default setup, these arrays will actually be the same, but they are built
    # independently for clarity and ease of modification.
    train_labels = [None] * (num_categories * num_train_per_cat)
    test_labels  = [None] * (num_categories * num_train_per_cat)

    for i,cat in enumerate(categories):
        images = glob.glob(os.path.join(data_path, 'train', cat, '*.jpg'))

        for j in range(num_train_per_cat):
            train_image_paths[i * num_train_per_cat + j] = images[j]
            train_labels[i * num_train_per_cat + j] = cat

        images = glob.glob(os.path.join(data_path, 'test', cat, '*.jpg'))
        for j in range(num_train_per_cat):
            test_image_paths[i * num_train_per_cat + j] = images[j]
            test_labels[i * num_train_per_cat + j] = cat

    return (train_image_paths, test_image_paths, train_labels, test_labels)
