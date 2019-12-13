# Install script for directory: /home/nvidia/workspace/catkin_ws/src/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_robots/kitech_robots_sims

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/nvidia/workspace/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/nvidia/workspace/catkin_ws/build/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_robots/kitech_robots_sims/catkin_generated/installspace/kitech_robots_sims.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kitech_robots_sims/cmake" TYPE FILE FILES
    "/home/nvidia/workspace/catkin_ws/build/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_robots/kitech_robots_sims/catkin_generated/installspace/kitech_robots_simsConfig.cmake"
    "/home/nvidia/workspace/catkin_ws/build/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_robots/kitech_robots_sims/catkin_generated/installspace/kitech_robots_simsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kitech_robots_sims" TYPE FILE FILES "/home/nvidia/workspace/catkin_ws/src/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_robots/kitech_robots_sims/package.xml")
endif()

