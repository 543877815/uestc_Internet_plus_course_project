import numpy as np
from skimage import io, filters, feature, img_as_float32
from skimage.transform import rescale
from skimage.color import rgb2gray

import student
import visualize
from main import load_data
from helpers import evaluate_correspondence


# Brown CSCI 1430 - James Tompkin, Jamie DeMaria, Brendan Walsh, Anna Sabel
# Our evaluation function to compute your accuracies

# setup variables
scale_factor = 0.5
max_pts_eval = 100 
feature_width = 16

def find_matches( student, image1, image2, eval_file ):

    (x1, y1) = student.get_interest_points(image1, feature_width)
    (x2, y2) = student.get_interest_points(image2, feature_width)

    image1_features = student.get_features(image1, x1, y1, feature_width)
    image2_features = student.get_features(image2, x2, y2, feature_width)

    matches, confidences = student.match_features(image1_features, image2_features)

    return x1, y1, x2, y2, matches, confidences


def averageAccuracy( student ):
    ###### ###### ###### ###### ###### ###### ###### ###### ###### ###### ######
    print("Notre Dame de Paris")
    image1, image2, eval_file = load_data('notre_dame')
    image1 = rgb2gray(rescale(image1, scale_factor))
    image2 = rgb2gray(rescale(image2, scale_factor))

    x1, y1, x2, y2, matches, confidences = find_matches( student, image1, image2, eval_file )

    num_pts_to_visualize = matches.shape[0]
    acc100ND = evaluate_correspondence(image1, image2, eval_file, scale_factor,
        x1, y1, x2, y2, matches, confidences, num_pts_to_visualize, "Notre_Dame.jpg")


    ###### ###### ###### ###### ###### ###### ###### ###### ###### ###### ######
    print("Mount Rushmore")
    image1, image2, eval_file = load_data('mt_rushmore')
    image1 = rgb2gray(rescale(image1, scale_factor))
    image2 = rgb2gray(rescale(image2, scale_factor))

    x1, y1, x2, y2, matches, confidences = find_matches( student, image1, image2, eval_file )

    num_pts_to_visualize = matches.shape[0]
    acc100MR = evaluate_correspondence(image1, image2, eval_file, scale_factor,
        x1, y1, x2, y2, matches, confidences, num_pts_to_visualize, "Mt_Rushmore.jpg")


    ###### ###### ###### ###### ###### ###### ###### ###### ###### ###### ######
    print("Episcopal Guadi")
    image1, image2, eval_file = load_data('e_gaudi')
    image1 = rgb2gray(rescale(image1, scale_factor))
    image2 = rgb2gray(rescale(image2, scale_factor))
    
    x1, y1, x2, y2, matches, confidences = find_matches( student, image1, image2, eval_file )

    num_pts_to_visualize = matches.shape[0]
    acc100EG = evaluate_correspondence(image1, image2, eval_file, scale_factor,
        x1, y1, x2, y2, matches, confidences, num_pts_to_visualize, "e_gaudi.jpg")


    ###### ###### ###### ###### ###### ###### ###### ###### ###### ###### ######
    acc100Avg = (acc100ND + acc100MR + acc100EG) / 3.0
    print("Average Accuracy: " + str(acc100Avg))

    return acc100ND, acc100MR, acc100EG, acc100Avg

if __name__ == "__main__":
    averageAccuracy( student )