cmake_minimum_required(VERSION 2.8.3)
project(ngimu_ros)

find_package(catkin REQUIRED COMPONENTS)
catkin_package(DEPENDS CATKIN DEPENDS)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

catkin_install_python(PROGRAMS 
	      nodes/ngimu_node.py
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/nodes
)
