cmake_minimum_required(VERSION 2.8.3)
project(amg_p1)

find_package(catkin REQUIRED COMPONENTS
  joy
  roscpp
  std_msgs
  vesc_msgs
  message_generation
)

add_message_files(
   DIRECTORY msg
   FILES
   CTM_Message.msg
   MP_Message.msg
   LA_Message.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS joy roscpp std_msgs vesc_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp
								    src/computed_torque_control.cpp
								    src/lqr_motion_planner.cpp
								    src/mpc_motion_planner.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})