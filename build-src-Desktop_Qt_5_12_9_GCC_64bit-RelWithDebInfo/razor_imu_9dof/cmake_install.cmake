# Install script for directory: /home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/razor_imu_9dof" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/include/razor_imu_9dof/imuConfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/razor_imu_9dof" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/razor_imu_9dof/__init__.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/razor_imu_9dof/cfg")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/razor_imu_9dof" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/razor_imu_9dof/cfg")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/razor_imu_9dof/catkin_generated/installspace/razor_imu_9dof.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof/cmake" TYPE FILE FILES
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/razor_imu_9dof/catkin_generated/installspace/razor_imu_9dofConfig.cmake"
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/razor_imu_9dof/catkin_generated/installspace/razor_imu_9dofConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof/launch")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof/config")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof/cfg")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof/src")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/razor_imu_9dof/magnetometer_calibration")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof/nodes" TYPE PROGRAM FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/razor_imu_9dof/catkin_generated/installspace/imu_node.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/razor_imu_9dof/nodes" TYPE PROGRAM FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/razor_imu_9dof/catkin_generated/installspace/display_3D_visualization.py")
endif()

