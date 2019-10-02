# circle drawing credits to pyimagesearch
# import the necessary packages
import numpy as np
import argparse
# remove ros py2 path for opencv 
# import sys 
# sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')
import cv2

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("--image", required = True, 
                help = "Path to the image")
ap.add_argument("--kernal", required = True, 
                help = "kernal size for gaussian blur")
args = vars(ap.parse_args())

# load the image, clone it for output, and then convert it to grayscale
image = cv2.imread(args["image"])
output = image.copy()
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
kernal_size = int(args["kernal"])
gray = cv2.GaussianBlur(gray, (kernal_size, kernal_size), 0) 

# detect circles in the image
circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1.3, 70)

# ensure at least some circles were found
if circles is not None:
	# convert the (x, y) coordinates and radius of the circles to integers
	circles = np.round(circles[0, :]).astype("int")

	# loop over the (x, y) coordinates and radius of the circles
	for (x, y, r) in circles:
		# draw the circle in the output image, then draw a rectangle
		# corresponding to the center of the circle
		cv2.circle(output, (x, y), r, (0, 255, 0), 4)
		cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

	# show the output image
	cv2.imshow("output", np.hstack([image, output]))
	cv2.waitKey(0)
print(len(circles), end="", flush=True) 