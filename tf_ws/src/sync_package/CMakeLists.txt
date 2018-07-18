cmake_minimum_required(VERSION 2.8.3)
project(sync_package)

find_package(catkin REQUIRED COMPONENTS geometry_msgs roscpp sensor_msgs std_msgs tf)

catkin_package(CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs std_msgs tf)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(synchroniser src/synchroniser.cpp)
target_link_libraries(synchroniser ${catkin_LIBRARIES})
