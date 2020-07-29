# Beginner.cpp

Beginner is a cpp file from "amazing_turtles" ROS package for printing the name "MARTI" in a specific ROS topic.

## Installation

You can obtain the package form [GitHub](https://github.com/mzaera/RobotCraft_ROS_Task). Or using terminal:

```bash
git clone https://github.com/mzaera/RobotCraft_ROS_Task.git
```

## Usage

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

## Contributing
Corrections are welcome. For major changes, please contact Marti Zaera.


## License
[RobotCraft](https://robotcraft.ingeniarius.pt/)