# Amazing_turtles pkg

## 1. Installation

You can obtain the package form [GitHub](https://github.com/mzaera/RobotCraft_ROS_Task). Or using terminal:

```bash
git clone https://github.com/mzaera/RobotCraft_ROS_Task.git
```

## 2. Beginner

Beginner_launcher runs the beginner.cpp

Beginner.cpp will print the name "MARTI" in a ROS topic called name_topic.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roscore
```

Terminal 2:
```bash
roslaunch amazing_turtles beginner_launch.launch
```

Terminal 3:
```bash
rostopic echo /name_topic
```

## 3. Normal1

Normal1_launcher runs the beginner.cpp and Normal1.cpp programs.

Normal1.cpp reads the ROS topic called name_topic, and will print its info to the ROS terminal.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roscore
```

Terminal 2:
```bash
roslaunch amazing_turtles normal1_launch.launch
```

## 4. Contributing
Corrections are welcome. For major changes, please contact Marti Zaera.


## 5. License
[RobotCraft](https://robotcraft.ingeniarius.pt/)