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

## 3. Normal_Part1

Normal_Part1_launcher runs the beginner.cpp and Normal_Part1.cpp programs.

Normal_Part1.cpp reads the ROS topic called name_topic, and will print its info to the ROS terminal.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roscore
```

Terminal 2:
```bash
roslaunch amazing_turtles normal_Part1_launch.launch
```

## 4. Normal_Part2

Normal_Part2_launcher runs the turtlesim_node.cpp from turtlesim.pkg and Normal_Part2.cpp programs.

Normal_Part2.cpp creates a triangular path using the turtlebot simulator.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roscore
```

Terminal 2:
```bash
roslaunch amazing_turtles normal_Part2_launch.launch
```

## 5. Contributing
Corrections are welcome. For major changes, please contact Marti Zaera.


## 6. License
[RobotCraft](https://robotcraft.ingeniarius.pt/)