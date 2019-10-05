# ROV Challenge Software

## Setup

 1. Clone the repo into {catkin_workspace}/src

    cd ~/catkin_ws/src
    git clone https://github.com/rameziophobia/ROV_Challenge.git

 2. To open project from Qt Creator

> File -> Open File or Project

 3. Choose file

> ~/catkin_ws/src/CMakeLists.txt

## stream RTSP on localhost
in terminal

> cvlc -vvv v4l2:///dev/video0 --sout '#transcode{vcodec=mp4v,vb=800,scale=Auto,acodec=none}:rtp{sdp=rtsp://:8554/}

