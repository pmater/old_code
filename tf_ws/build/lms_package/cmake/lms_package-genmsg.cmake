# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "lms_package: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ilms_package:/home/calvon/tf_ws/src/lms_package/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(lms_package_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" NAME_WE)
add_custom_target(_lms_package_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "lms_package" "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(lms_package
  "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lms_package
)

### Generating Services

### Generating Module File
_generate_module_cpp(lms_package
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lms_package
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(lms_package_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(lms_package_generate_messages lms_package_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" NAME_WE)
add_dependencies(lms_package_generate_messages_cpp _lms_package_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lms_package_gencpp)
add_dependencies(lms_package_gencpp lms_package_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lms_package_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(lms_package
  "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lms_package
)

### Generating Services

### Generating Module File
_generate_module_eus(lms_package
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lms_package
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(lms_package_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(lms_package_generate_messages lms_package_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" NAME_WE)
add_dependencies(lms_package_generate_messages_eus _lms_package_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lms_package_geneus)
add_dependencies(lms_package_geneus lms_package_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lms_package_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(lms_package
  "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lms_package
)

### Generating Services

### Generating Module File
_generate_module_lisp(lms_package
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lms_package
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(lms_package_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(lms_package_generate_messages lms_package_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" NAME_WE)
add_dependencies(lms_package_generate_messages_lisp _lms_package_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lms_package_genlisp)
add_dependencies(lms_package_genlisp lms_package_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lms_package_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(lms_package
  "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lms_package
)

### Generating Services

### Generating Module File
_generate_module_nodejs(lms_package
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lms_package
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(lms_package_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(lms_package_generate_messages lms_package_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" NAME_WE)
add_dependencies(lms_package_generate_messages_nodejs _lms_package_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lms_package_gennodejs)
add_dependencies(lms_package_gennodejs lms_package_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lms_package_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(lms_package
  "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lms_package
)

### Generating Services

### Generating Module File
_generate_module_py(lms_package
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lms_package
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(lms_package_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(lms_package_generate_messages lms_package_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/calvon/tf_ws/src/lms_package/msg/lms_message.msg" NAME_WE)
add_dependencies(lms_package_generate_messages_py _lms_package_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lms_package_genpy)
add_dependencies(lms_package_genpy lms_package_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lms_package_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lms_package)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lms_package
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(lms_package_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(lms_package_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lms_package)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lms_package
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(lms_package_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(lms_package_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lms_package)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lms_package
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(lms_package_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(lms_package_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lms_package)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lms_package
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(lms_package_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(lms_package_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lms_package)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lms_package\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lms_package
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(lms_package_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(lms_package_generate_messages_py sensor_msgs_generate_messages_py)
endif()
