cmake_minimum_required(VERSION 3.0.2)
project(amazing_turtles)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(

)

include_directories(

  ${catkin_INCLUDE_DIRS}
)

##V1_Files Ros_Task start here -->

add_executable(beginner src/beginner.cpp)

target_link_libraries(beginner 
${catkin_LIBRARIES}
)

add_executable(normal_Part1 src/normal_Part1.cpp)

target_link_libraries(normal_Part1 
${catkin_LIBRARIES}
)

add_executable(normal_Part2 src/normal_Part2.cpp)

target_link_libraries(normal_Part2
${catkin_LIBRARIES}
)

add_executable(ninja_service src/ninja_service.cpp)

target_link_libraries(ninja_service
${catkin_LIBRARIES}
)


