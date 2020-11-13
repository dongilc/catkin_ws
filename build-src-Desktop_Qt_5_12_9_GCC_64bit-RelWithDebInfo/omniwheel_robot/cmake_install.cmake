# Install script for directory: /home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/omniwheel_robot

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/omniwheel_robot/cmake" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/omniwheel_robot/catkin_generated/installspace/omniwheel_robot-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/share/roseus/ros/omniwheel_robot")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/omniwheel_robot")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/omniwheel_robot")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/omniwheel_robot/catkin_generated/installspace/omniwheel_robot.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/omniwheel_robot/cmake" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/omniwheel_robot/catkin_generated/installspace/omniwheel_robot-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/omniwheel_robot/cmake" TYPE FILE FILES
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/omniwheel_robot/catkin_generated/installspace/omniwheel_robotConfig.cmake"
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/omniwheel_robot/catkin_generated/installspace/omniwheel_robotConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/omniwheel_robot" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/omniwheel_robot/package.xml")
endif()

