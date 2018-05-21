cmake_minimum_required(VERSION 2.8.3)
project(buggy_bot)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
)

catkin_python_setup()
