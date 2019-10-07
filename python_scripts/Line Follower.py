import cv2
import numpy as np

def extreme_points(contour): #Gets the extreme values of the contours, used for getting error and width
    contour = contour[0]
    leftmost = contour[contour[:,:,0].argmin()][0][0]
    rightmost = contour[contour[:,:,0].argmax()][0][0]
    topmost = contour[contour[:,:,1].argmin()][0][1]
    bottommost = contour[contour[:,:,1].argmax()][0][1]
    return leftmost, rightmost, topmost, bottommost

def GetDirection(img): #Gets the initial direction for the ROV
    img = cv2.resize(img, (40, 40))
    # get the red line
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower_red_0 = np.array([0, 50, 0])
    upper_red_0 = np.array([10, 255, 255])
    lower_red = np.array([160, 150, 0])
    upper_red = np.array([180, 255, 255])
    mask1 = cv2.inRange(hsv, lower_red, upper_red)
    mask2 = cv2.inRange(hsv, lower_red_0, upper_red_0)
    mask = mask1 + mask2
    # using ROI set the center of image (80% of image) to 0
    y1 = img.shape[0] // 10
    y2 = img.shape[0] * 9 // 10
    x1 = img.shape[1] // 10
    x2 = img.shape[1] * 9 // 10
    mask[y1:y2, x1:x2] = np.zeros((y2 - y1, x2 - x1), dtype=int)

    # get red_line contour, extreme points
    _, thresh = cv2.threshold(res, 127, 255, 0)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contour = sorted(contours, key=cv2.contourArea, reverse=True)[:1]
    leftmost, rightmost, topmost, bottommost = extreme_points(contour)

    # finds the extreme point on image border to determine the dir
    if leftmost < 3:
        direction = "Left"
        width = abs(topmost - bottommost)
    elif rightmost > frame.shape[1] - 3:
        direction = "Right"
        width = abs(topmost - bottommost)
    elif topmost < 3:
        direction = "Up"
        width = abs(leftmost - rightmost)
    elif bottommost > frame.shape[0] - 3:
        direction = "Down"
        width = abs(leftmost - rightmost)
    return direction,width

def init(img): #getting contours of each frame
    # Filter Image
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    lower_red_0 = np.array([0, 50, 0])
    upper_red_0 = np.array([10, 255, 255])
    lower_red = np.array([160, 150, 0])
    upper_red = np.array([180, 255, 255])
    mask1 = cv2.inRange(hsv, lower_red, upper_red)
    mask2 = cv2.inRange(hsv, lower_red_0, upper_red_0)
    res = mask1 + mask2
    final = cv2.bitwise_and(img, img, mask = res)
    # Get Edges
    Frame = cv2.Canny(res, 100, 100)
    blur5 = cv2.GaussianBlur(Frame, (5, 5), 0)
    blur3 = cv2.GaussianBlur(Frame, (1, 1), 0)
    edges = blur5 - blur3

    # find the contours
    cnts, _ = cv2.findContours(edges, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    cnts = sorted(cnts, key=cv2.contourArea, reverse=True)[:1]

    peri = cv2.arcLength(cnts[0], True)
    # Approximates the Contor we have to one with less vertices
    approx = cv2.approxPolyDP(cnts[0], 0.02 * peri, True)

    # get the verticies
    vertices = cv2.convexHull(approx, clockwise=False)
    color = 100
    # getting each specific vertex
    for corner in vertices:
        x, y = corner[0].ravel()
        cv2.circle(frame, (x, y), 5, (color/2, color/4, color/6), -1)
        color += 40
    return cnts,res

cap = cv2.VideoCapture("video-1570433064.mp4")
_, frame = cap.read() #Used to capture a frame from the video
frame = cv2.resize(frame, (1280, 720))
#img = cv2.imread()

cnts,res = init(frame) #res is the mask returned
row, col = res.shape
center_row = int(row / 2)
center_col = int(col / 2)
direction = "None"
prevdirection = "None" #Was going to be used to set direction in case of the ROV is mislead, but not functional yet
error = 0
width = 0 #Width of the line followed
leftmost, rightmost, topmost, bottommost = extreme_points(cnts)
direction,width = GetDirection(frame)
print(width)
while 1:
    _, frame = cap.read()
    frame = cv2.resize(frame, (1280, 720))
  # img = cv2.imread("img2.jpg")
    frame = cv2.medianBlur(frame, 3)
    cnts, res = init(frame)
    leftmost, rightmost, topmost, bottommost = extreme_points(cnts)
    #Checks in the direction it's moving in the red pixels, if no red pixels exist at distance of 2/3 from the width, we change the direction
    if direction == "Up":
        if res[center_row - int(2*width/3)][center_col] == 0:
            if res[center_row][center_col + int(2*width/3)] != 0:
                direction = "Right"
                prevdirection = "Up"
                # Move Right
            elif res[center_row][center_col - int(2*width/3)] != 0:
                direction = "Left"
                prevdirection = "Up"
                # Move Left
        error = abs(center_row - topmost)
    elif direction == "Down":
        if res[center_row + int(2*width/3)][center_col] == 0:
            if res[center_row][center_col + int(2*width/3)] != 0:
                direction = "Right"
                prevdirection = "Down"
                # Move Right
            elif res[center_row][center_col - int(2*width/3)] != 0:
                direction = "Left"
                prevdirection = "Down"
                # Move Left
        error = abs(center_row - bottommost)
    elif direction == "Left":
        if res[center_row][center_col - int(2*width/3)] == 0:
            if res[center_row - int(2*width/3)][center_col] != 0:
                direction = "Up"
                prevdirection = "Left"
                # Move up
            elif res[center_row + int(2*width/3)][center_col] != 0:
                direction = "Down"
                prevdirection = "Left"
                # Move Down
        error = abs(center_col - leftmost)
    elif direction == "Right":
        if res[center_row][center_col + int(2*width/3)] == 0:
            if res[center_row - int(2*width/3)][center_col] != 0:
                direction = "Up"
                prevdirection = "Right"
                # Move up
            elif res[center_row + int(2*width/3)][center_col] != 0:
                direction = "Down"
                prevdirection = "Right"
                # Move Down
        error = abs(center_col - rightmost)
    print("error: " + str(error) + " To the " + direction)
    cv2.imshow("image", frame)
    cv2.waitKey(20)