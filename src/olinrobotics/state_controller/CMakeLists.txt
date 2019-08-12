cmake_minimum_required(VERSION 2.8.11)
project(state_controller)

# Compile as C++11, supported in ROS Kinetic and newer
set(CMAKE_CXX_FLAGS "-std=c++11")

# Find catkin macros and libraries
# if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
# is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  std_msgs
  message_generation
)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
	FILES
  PoseLabeled.msg
)

# Generate messages in the 'msg' folder
add_message_files(
	FILES
	TwistLabeled.msg
  PoseLabeled.msg
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

###################################
## catkin specific configuration ##
###################################
# The catkin_package macro generates cmake config files for your package
# Declare things to be passed to dependent projects
# INCLUDE_DIRS: uncomment this if your package contains header files
# LIBRARIES: libraries you create in this project that dependent projects also need
# CATKIN_DEPENDS: catkin_packages dependent projects also need
# DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
	INCLUDE_DIRS /usr/include/boost/algorithm include
	LIBRARIES state_controller
#  DEPENDS system_lib
	CATKIN_DEPENDS message_runtime geometry_msgs roscpp std_msgs
)

###########
## Build ##
###########

# Specify additional locations of header files
# Your package locations should be listed before other locations
include_directories(
  include
	${catkin_INCLUDE_DIRS}
)

# Declare a C++ library
add_library(state_controller src/BehaviorLib.cpp )

# Declare a C++ executable
# With catkin_make all packages are built within a single CMake context
# The recommended prefix ensures that target names across packages don't collide
add_executable( MainState src/MainState/MainState.cpp src/BehaviorLib.cpp)
add_executable( BehaviorEx src/BehaviorEx/BehaviorEx.cpp)
add_executable( Teleop src/Teleop/Teleop.cpp src/BehaviorLib.cpp)

# Specify libraries to link a library or executable target against
target_link_libraries( MainState ${catkin_LIBRARIES} )
target_link_libraries( BehaviorEx ${catkin_LIBRARIES} )
target_link_libraries( Teleop ${catkin_LIBRARIES} )

# Add cmake target dependencies of the executable
# same as for the library above
add_dependencies( MainState ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
add_dependencies( BehaviorEx ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
add_dependencies( Teleop ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
add_dependencies( state_controller  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )

#############
## Install ##
#############

#############
## Testing ##
#############
