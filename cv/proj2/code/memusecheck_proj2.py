import os, memory_profiler
from skimage import io, filters, feature, img_as_float32
from skimage.transform import rescale
from skimage.color import rgb2gray
from helpers import cheat_interest_points, evaluate_correspondence
import student

def memfunc():
    
    # Note: these files default to notre dame, unless otherwise specified
    image1_file = "../data/NotreDame/NotreDame1.jpg"
    image2_file = "../data/NotreDame/NotreDame2.jpg"
    eval_file = "../data/NotreDame/NotreDameEval.mat"
    
    scale_factor = 0.5
    feature_width = 16

    image1 = img_as_float32(rescale(rgb2gray(io.imread(image1_file)),scale_factor))
    image2 = img_as_float32(rescale(rgb2gray(io.imread(image2_file)),scale_factor))
    
    (x1, y1) = student.get_interest_points(image1, feature_width)
    (x2, y2) = student.get_interest_points(image2, feature_width)
    
    image1_features = student.get_features(image1, x1, y1, feature_width)
    image2_features = student.get_features(image2, x2, y2, feature_width)
        
    matches, confidences = student.match_features(image1_features, image2_features)

    evaluate_correspondence(image1, image2, eval_file, scale_factor,
        x1, y1, x2, y2, matches, confidences, 0)

if __name__ == "__main__":
    memuse = max(memory_profiler.memory_usage(proc=memfunc))
    print("Your program memory use: " + str(memuse) + " MiB")