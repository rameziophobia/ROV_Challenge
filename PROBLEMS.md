# Problems & Solutions

 1. qtcreator could not find roscpp package
Add `/opt/ros/kinetic` to `CMAKE_PREFIX_PATH` in **Project -> build**
If you are using melodic ros
Add `/opt/ros/melodic` to `CMAKE_PREFIX_PATH`

 2. Qt can't connect to Ros or Qt receives nothing from Ros
Sometimes Ros Master can't detect the ip of its host. To solve this problem, open ~/.bashrc file on device that ros master is running on (in our case is Raspberry PI) and type the following command `export ROS_IP=\<MASTER_HOST_IP\>`
Where `MASTER_HOST_IP` is ip of device that ros master is running on, then save ~/.bashrc file and type the following command in terminal
    `source ~/.bashrc`

