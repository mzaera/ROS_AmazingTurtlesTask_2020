# Amazing_turtles pkg

## 1. Installation

You can obtain the package form [GitHub](https://github.com/mzaera/RobotCraft_ROS_Task). Or using terminal:
```bash
cd ~/catkin_ws/src
git clone https://github.com/mzaera/RobotCraft_ROS_Task.git
cd ~/catkin_ws
catkin_make
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
roslaunch amazing_turtles normal_Part1.launch
```


## 4. Normal_Part2

Normal_Part2.launch runs the turtlesim_node.cpp from turtlesim.pkg and Normal_Part2.cpp programs.

Normal_Part2.cpp creates a triangular path using the turtlebot simulator.


### Usage

Terminal, in the catkin folder:
```bash
roslaunch amazing_turtles normal_Part2.launch
```

## 5. Ninja

Ninja.launch runs the turtlesim_node.cpp from turtlesim.pkg and ninja_service.cpp programs.

Ninja_service.cpp creates a service that allows you to control the turtle with teleop_twist_keyboard when you send TRUE and stops the turtle when he recives a FALSE.


### Usage

Terminal 1, in the catkin folder:
```bash
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
## 6. Race

Race.launch runs the turtlesim_node.cpp from turtlesim.pkg and race_service.cpp programs.

Race_service.cpp creates a service that creates a race between turtles when you send TRUE and stops it  when he recives a FALSE. Itprints the results on the terminal. If you don't send FALSE to the service it will automatically end after 20 sec.


### Usage

Terminal 1, in the catkin folder:
```bash
roslaunch amazing_turtles race.launch
```
Terminal 2:
```bash
rosservice call /race_service "data: false"
```
```bash
rosservice call /race_service "data: true"
```

## 7. Rotation

Rotation.launch runs the turtlesim_node.cpp from turtlesim.pkg and rotation_act.cpp programs.

Rotation_act.cpp creates an action server that is waitting for a max velocity. The turtle starts to increase his velocity and prints the current velocity into /rotation/feedback topic, when the mzx_vel is reach the turtle stops and print the final velocity into /rotation/result topic. The order can be canceled sending a msg into /rotation/cancel topic.

### Usage
Besure that you have done:

```bash
source devel/setup.bash
```

In all the terminals that you are going to use.


Terminal 1, in the catkin folder:
```bash
roslaunch amazing_turtles rotation.launch
```
Extra terminals:

- To see the final vel
```bash
rostopic echo /rotation/result
```
- To see the current vel 
```bash
rostopic echo /rotation/feedback
```

- To cancel the order
```bash
rostopic pub /rotation/cancel actionlib_msgs/GoalID "stamp:
  secs: 0
  nsecs: 0
id: ''"
```
- To send the max vel 
```bash
rostopic pub /rotation/goal amazing_turtles/MaxvelActionGoal "header:
  seq: 0
  stamp:
    secs: 0
    nsecs: 0
  frame_id: ''
goal_id:
  stamp:
    secs: 0
    nsecs: 0
  id: ''
  max_vel: 0.0" 
```
## 8. Action_race

Action_race.launch runs the turtlesim_node.cpp from turtlesim.pkg and action_race.cpp programs.

Action_race.cpp creates an action server that is waitting for a final position. Once sended a final pose to the goal topic, Action_race.cpp kills the main turtle and generates a race between four turtles. The velocity of each turtle will be generated randomly. During the race the current winner will be published in /race/feedback topic. The final winner will be published in /race/result ros topic.

Usually Turtle number 4 will  have more winning probability due a code problem. That can be fixed using difernts threats when the program checks the current position of each turtle.  

### Usage
Besure that you have done:

```bash
source devel/setup.bash
```

In all the terminals that you are going to use.


Terminal 1, in the catkin folder:
```bash
roslaunch amazing_turtles action_race.launch
```
Extra terminals:

- To see the final winner
```bash
rostopic echo /race/result
```
- To see the current winner 
```bash
rostopic echo /race/feedback
```

- To cancel the race
```bash
rostopic pub /race/cancel actionlib_msgs/GoalID "stamp:
  secs: 0
  nsecs: 0
id: ''"
```
- To start modify the final_pos and send it 
```bash
rostopic pub /race/goal amazing_turtles/RaceActionGoal "header:
  seq: 0
  stamp:
    secs: 0
    nsecs: 0
  frame_id: ''
goal_id:
  stamp:
    secs: 0
    nsecs: 0
  id: ''
goal:
  final_pos: 0.0" 
```

## 9. Contributing
Corrections are welcome. For major changes, please contact Marti Zaera (martizaera99@gmail.com).


## 10. License
[RobotCraft](https://robotcraft.ingeniarius.pt/)


