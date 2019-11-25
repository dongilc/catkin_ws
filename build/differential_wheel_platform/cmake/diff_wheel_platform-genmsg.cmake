# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "diff_wheel_platform: 1 messages, 0 services")

set(MSG_I_FLAGS "-Idiff_wheel_platform:/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(diff_wheel_platform_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" NAME_WE)
add_custom_target(_diff_wheel_platform_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "diff_wheel_platform" "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(diff_wheel_platform
  "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diff_wheel_platform
)

### Generating Services

### Generating Module File
_generate_module_cpp(diff_wheel_platform
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diff_wheel_platform
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(diff_wheel_platform_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(diff_wheel_platform_generate_messages diff_wheel_platform_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" NAME_WE)
add_dependencies(diff_wheel_platform_generate_messages_cpp _diff_wheel_platform_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diff_wheel_platform_gencpp)
add_dependencies(diff_wheel_platform_gencpp diff_wheel_platform_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diff_wheel_platform_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(diff_wheel_platform
  "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/diff_wheel_platform
)

### Generating Services

### Generating Module File
_generate_module_eus(diff_wheel_platform
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/diff_wheel_platform
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(diff_wheel_platform_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(diff_wheel_platform_generate_messages diff_wheel_platform_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" NAME_WE)
add_dependencies(diff_wheel_platform_generate_messages_eus _diff_wheel_platform_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diff_wheel_platform_geneus)
add_dependencies(diff_wheel_platform_geneus diff_wheel_platform_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diff_wheel_platform_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(diff_wheel_platform
  "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diff_wheel_platform
)

### Generating Services

### Generating Module File
_generate_module_lisp(diff_wheel_platform
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diff_wheel_platform
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(diff_wheel_platform_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(diff_wheel_platform_generate_messages diff_wheel_platform_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" NAME_WE)
add_dependencies(diff_wheel_platform_generate_messages_lisp _diff_wheel_platform_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diff_wheel_platform_genlisp)
add_dependencies(diff_wheel_platform_genlisp diff_wheel_platform_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diff_wheel_platform_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(diff_wheel_platform
  "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/diff_wheel_platform
)

### Generating Services

### Generating Module File
_generate_module_nodejs(diff_wheel_platform
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/diff_wheel_platform
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(diff_wheel_platform_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(diff_wheel_platform_generate_messages diff_wheel_platform_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" NAME_WE)
add_dependencies(diff_wheel_platform_generate_messages_nodejs _diff_wheel_platform_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diff_wheel_platform_gennodejs)
add_dependencies(diff_wheel_platform_gennodejs diff_wheel_platform_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diff_wheel_platform_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(diff_wheel_platform
  "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diff_wheel_platform
)

### Generating Services

### Generating Module File
_generate_module_py(diff_wheel_platform
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diff_wheel_platform
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(diff_wheel_platform_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(diff_wheel_platform_generate_messages diff_wheel_platform_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cdi/SynologyDrive/workspace/catkin_ws/src/differential_wheel_platform/msg/CTM_Message.msg" NAME_WE)
add_dependencies(diff_wheel_platform_generate_messages_py _diff_wheel_platform_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diff_wheel_platform_genpy)
add_dependencies(diff_wheel_platform_genpy diff_wheel_platform_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diff_wheel_platform_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diff_wheel_platform)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diff_wheel_platform
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(diff_wheel_platform_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/diff_wheel_platform)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/diff_wheel_platform
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(diff_wheel_platform_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diff_wheel_platform)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diff_wheel_platform
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(diff_wheel_platform_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/diff_wheel_platform)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/diff_wheel_platform
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(diff_wheel_platform_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diff_wheel_platform)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diff_wheel_platform\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diff_wheel_platform
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(diff_wheel_platform_generate_messages_py std_msgs_generate_messages_py)
endif()
