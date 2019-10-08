import numpy as np
import math

UP = np.array([1, 1, 1, 1])
RIGHT = np.array([1, -1, -1, 1])
ROTATE_CLOCKWISE = np.array([1, -1, 1, -1])
COS45 = math.cos(math.pi / 4)


def get_pwm(vertical, horizontal, rotation):
    # up = apply_rot(rotation, UP.copy())
    v = UP * vertical
    # print(v)
    h = RIGHT * horizontal
    # apply_rot(h)
    # print(h)
    vh = v + h
    # print(vh)
    scale = vh.min()
    scale = scale if abs(scale) > vh.max() else vh.max()

    hypot = math.hypot(horizontal, vertical)
    angle = math.atan(vertical / horizontal)  # todo check if it outputs angle > 90

    if angle < math.pi / 4:
        l_coeff = math.hypot(1, vertical)
        speed = hypot / l_coeff
    elif angle > math.pi / 4:
        l_coeff = math.hypot(1, horizontal)
        speed = hypot / l_coeff
    elif angle == math.pi / 4:
        speed = horizontal  # horizontal = vertical
    else:
        speed = 0
        print(f"angle should be bet. 0 n 90 bruh {math.degrees(angle)}")
    return vh / abs(scale) * speed


# def apply_rot(rotation, arr):
#     # caret ^ is xor operation if sign is similar hytala3 +ve
#     for i in range(3):
#         if arr[i] ^ ROTATE_CLOCKWISE[i] > 0:
#             arr[i] +=


tup = get_pwm(-0.5, -0.8, 0)
print(f"motors: {tup}")

xcomp = tup[0] * COS45 * 2 + tup[1] * COS45 * 2
ycomp = tup[0] * COS45 * 2 - tup[1] * COS45 * 2

print(f"forces: {xcomp}, {ycomp}")
print(f"resultant force: {math.hypot(xcomp, ycomp)}")
print(f"resultant angle: {math.degrees(math.atan(xcomp / ycomp))}")
