# USAGE
# python cat_detector.py --image images/cat_01.jpg
# credit to pyimagesearch

# import the necessary packages
import argparse
# remove ros py2 path for opencv 
# import sys 
# sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')
import cv2
 
# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("--image", required=True,
	help="path to the input image")
ap.add_argument("--cascade",
	default="haarcascade_frontalcatface.xml",
	help="path to cat detector haar cascade")
args = vars(ap.parse_args())

# load the input image and convert it to grayscale
image = cv2.imread(args["image"])
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# A scaleFactor  of our image pyramid used when detecting cat faces. 
# A larger scale factor will increase the speed of the detector, 
# but could harm our true-positive detection accuracy. Conversely, 
# a smaller scale will slow down the detection process, 
# but increase true-positive detections. However, 
# this smaller scale can also increase the false-positive detection rate as well. See the “A note on Haar cascades” section of this blog post for more information.

# The minNeighbors  parameter controls the minimum number of detected 
# bounding boxes in a given area for the region to be considered a “cat face”. 
# This parameter is very helpful in pruning false-positive detections.

# load the cat detector Haar cascade, then detect cat faces
# in the input image
detector = cv2.CascadeClassifier(args["cascade"])
rects = detector.detectMultiScale(gray, scaleFactor=1.3,
	minNeighbors=10, minSize=(75, 75))

# loop over the cat faces and draw a rectangle surrounding each
for (i, (x, y, w, h)) in enumerate(rects):
	cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2)
	cv2.putText(image, "Cat #{}".format(i + 1), (x, y - 10),
		cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 0, 255), 2)

# show the detected cat faces
cv2.imshow("Cat Faces", image)
cv2.waitKey(0)
print(len(rects))