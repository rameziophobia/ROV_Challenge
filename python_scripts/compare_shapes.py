import json

boxes = [{}, {}, {}]
# load all 3 pattern dictionaries
for i in range(1, 4):
    with open("output_b" + str(i) + ".json", "r") as fp: 
        boxes[i - 1] = json.loads(fp.read())

common_1_2 = common_2_3 = common_1_3 = 0
# count the common shapes between each 2 boxes
for k in boxes[0]:
    if k in boxes[1]:
        common_1_2 += min(boxes[0][k], boxes[1][k])
    if k in boxes[2]:
        common_1_3 += min(boxes[0][k], boxes[2][k])

for k in boxes[1]:
    if k in boxes[2]:
        common_2_3 += min(boxes[1][k], boxes[2][k])

# count the number of shapes in each box

def add_shape_count(box):
    for v in list(box.values()):
        box["count"] = box.get("count", 0) + v 

for box in boxes:
    add_shape_count(box)

# reduce the commons by the difference in the count of shapes
common_1_2 -= abs(boxes[0]["count"] - boxes[1]["count"])
common_1_3 -= abs(boxes[0]["count"] - boxes[2]["count"])
common_2_3 -= abs(boxes[1]["count"] - boxes[2]["count"])

odd_box_num = 404
# return the box with the least common shapes
max_common = max(common_1_2, common_1_3, common_2_3)
if max_common == common_1_2:
    odd_box_num = 3
elif max_common == common_1_3:
    odd_box_num = 2
elif max_common == common_2_3:
    odd_box_num = 1

print("b" + str(odd_box_num), end="", flush=True) 
