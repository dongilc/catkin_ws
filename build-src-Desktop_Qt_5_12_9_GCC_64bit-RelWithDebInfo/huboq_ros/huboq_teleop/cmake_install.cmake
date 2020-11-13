# Install script for directory: /home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/huboq_ros/huboq_teleop

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/huboq_teleop/cmake" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/huboq_ros/huboq_teleop/catkin_generated/installspace/huboq_teleop-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/share/roseus/ros/huboq_teleop")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/huboq_teleop")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/huboq_teleop")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/huboq_ros/huboq_teleop/catkin_generated/installspace/huboq_teleop.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/huboq_teleop/cmake" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/huboq_ros/huboq_teleop/catkin_generated/installspace/huboq_teleop-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/huboq_teleop/cmake" TYPE FILE FILES
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/huboq_ros/huboq_teleop/catkin_generated/installspace/huboq_teleopConfig.cmake"
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/huboq_ros/huboq_teleop/catkin_generated/installspace/huboq_teleopConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/huboq_teleop" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/huboq_ros/huboq_teleop/package.xml")
endif()

