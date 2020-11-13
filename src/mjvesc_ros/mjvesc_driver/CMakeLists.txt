cmake_minimum_required(VERSION 2.8.3)
project(mjvesc_driver)

find_package(catkin REQUIRED COMPONENTS
  nodelet
  pluginlib
  roscpp
  std_msgs
  mjvesc_msgs
  serial
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS nodelet pluginlib roscpp std_msgs mjvesc_msgs serial
)

###########
## Build ##
###########

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

# node executable
add_executable(mjvesc_driver_node src/mjvesc_driver_node.cpp
                                src/mjvesc_driver.cpp
                                src/mjvesc_interface.cpp
                                src/mjvesc_packet.cpp
                                src/mjvesc_packet_factory.cpp)
add_dependencies(mjvesc_driver_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(mjvesc_driver_node
  ${catkin_LIBRARIES}
)

# nodelet library
add_library(mjvesc_driver_nodelet src/mjvesc_driver_nodelet.cpp
                                  src/mjvesc_driver.cpp
                                  src/mjvesc_interface.cpp
                                  src/mjvesc_packet.cpp
                                  src/mjvesc_packet_factory.cpp)
add_dependencies(mjvesc_driver_nodelet ${catkin_EXPORTED_TARGETS})
target_link_libraries(mjvesc_driver_nodelet
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

install(TARGETS mjvesc_driver_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(TARGETS mjvesc_driver_nodelet
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
install(FILES mjvesc_driver_nodelet.xml
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(DIRECTORY launch/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)

#############
## Testing ##
#############

# TODO