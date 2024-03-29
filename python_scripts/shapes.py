import argparse 
import json 
import pprint
# remove ros py2 path for opencv 
# import sys 
# sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages') 
import cv2 
import imutils as imutils 
# construct the argument parser and parse the arguments 

parser = argparse.ArgumentParser() 

parser.add_argument("--box", required=True, 
                    help="Box number") 

parser.add_argument("--image", required=True, 
                    help="Path to the image")

parser.add_argument("--kernal", required=True, 
                    help="Kernal size for gaussian blur") 
 
args = parser.parse_args() 
 
img = cv2.imread(args.image) 
 
# convert the image to grayscale for speed 
# blur image to remove images 
# todo resize image 
# todo blur sometimes removes lines 
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) 

kernal_size = int(args.kernal)
gray = cv2.GaussianBlur(gray, (kernal_size, kernal_size), 0) 
 
# find the contours in the gray blurred image to find shapes 
cnts = cv2.findContours(gray, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE) 
cnts = imutils.grab_contours(cnts)

contour_dict = {} 
# loop over the contours 
for c in cnts: 
    # approximate the contour 
    peri = cv2.arcLength(c, True) 
    approx = cv2.approxPolyDP(c, 0.02 * peri, True) 
 
    # add contour to dictionary 
    # assume circle if there are more than 6 points 
    key = len(approx) if len(approx) < 7 else 7 
    contour_dict[key] = contour_dict.get(key, 0) + 1
    cv2.drawContours(img, [approx], -1, (255,0,0), 5)

# show image for debugging
cv2.imshow("win", img) 
cv2.waitKey() 

with open("output_" + args.box + ".json", "w") as fp: 
    json.dump(contour_dict, fp) 

# pp = pprint.pformat(contour_dict, indent=4,compact=False)
print(contour_dict, end="", flush=True) 
