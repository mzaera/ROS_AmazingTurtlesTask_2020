# Amazing_turtles pkg

## 1. Installation

You can obtain the package form [GitHub](https://github.com/mzaera/RobotCraft_ROS_Task). Or using terminal:

```bash
git clone https://github.com/mzaera/RobotCraft_ROS_Task.git
```
If you can not use the package, try to source the catkin_ws with the following command:
 
```bash
source devel/setup.bash
```

## 2. Beginner

Beginner.launch runs the beginner.cpp.

Beginner.cpp will print the name "MARTI" in a ROS topic called name_topic.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roslaunch amazing_turtles beginner.launch
```

Terminal 2:
```bash
rostopic echo /name_topic
```

## 3. Normal_Part1

Normal_Part1.launch runs the beginner.cpp and Normal_Part1.cpp programs.

Normal_Part1.cpp reads the ROS topic called name_topic, and will print its info to the ROS terminal.


### Usage

Terminal, in the catkin folder:
```bash
catkin_make
roslaunch amazing_turtles normal_Part1.launch
```


## 4. Normal_Part2

Normal_Part2.launch runs the turtlesim_node.cpp from turtlesim.pkg and Normal_Part2.cpp programs.

Normal_Part2.cpp creates a triangular path using the turtlebot simulator.


### Usage

Terminal, in the catkin folder:
```bash
catkin_make
roslaunch amazing_turtles normal_Part2.launch
```

## 5. Ninja

Ninja.launch runs the turtlesim_node.cpp from turtlesim.pkg and ninja_service.cpp programs.

Ninja_service.cpp creates a service that allows you to control the turtle with teleop_twist_keyboard when you send TRUE and stops the turtle when he recives a FALSE.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roscore
```

Terminal 2:
```bash
roslaunch amazing_turtles ninja.launch
```

Terminal 3:
```bash
rosservice call /ninja_service "data: false"
```
```bash
rosservice call /ninja_service "data: true"
```

Terminal 4:
```bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.py cmd_vel:=keyboard/cmd_vel
```


## 6. Contributing
Corrections are welcome. For major changes, please contact Marti Zaera (martizaera99@gmail.com).


## 7. License
[RobotCraft](https://robotcraft.ingeniarius.pt/)
