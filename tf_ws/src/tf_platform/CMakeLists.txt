cmake_minimum_required(VERSION 2.8.3)
project(tf_platform)

find_package(catkin REQUIRED COMPONENTS roscpp rospy sensor_msgs geometry_msgs std_msgs tf)

catkin_package(CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs geometry_msgs tf)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})


