cmake_minimum_required(VERSION 2.8.3)
project(gps_package)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs tf sensor_msgs geometry_msgs message_generation)

add_message_files(FILES gps_message.msg)
generate_messages(DEPENDENCIES std_msgs sensor_msgs)
catkin_package(CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs geometry_msgs tf message_runtime)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(gps_pub src/gps_entryfile.cpp src/convert.cpp src/operation.cpp src/parsing.cpp src/reading.cpp src/socket.cpp)
target_link_libraries(gps_pub ${catkin_LIBRARIES})
add_dependencies(gps_pub gps_package_generate_messages_cpp)

#GPS is the sole tf broadcaster
#add_executable(gps_position_tf src/gps_position_tf.cpp)
#target_link_libraries(gps_position_tf ${catkin_LIBRARIES})
#add_dependencies(gps_position_tf gps_package_generate_messages_cpp)
