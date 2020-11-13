# Install script for directory: /home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kitech_controllers/cmake" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/catkin_generated/installspace/kitech_controllers-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/share/roseus/ros/kitech_controllers")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/kitech_controllers")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/python2.7/dist-packages/kitech_controllers")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/catkin_generated/installspace/kitech_controllers.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kitech_controllers/cmake" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/catkin_generated/installspace/kitech_controllers-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kitech_controllers/cmake" TYPE FILE FILES
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/catkin_generated/installspace/kitech_controllersConfig.cmake"
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/catkin_generated/installspace/kitech_controllersConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kitech_controllers" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/kitech_controllers" TYPE DIRECTORY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/kitech_legged_segway_robot_v0.2/kitech_legged_segway_robot/kitech_controllers/include/kitech_controllers/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/libkitech_controllers.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so"
         OLD_RPATH "/opt/ros/melodic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libkitech_controllers.so")
    endif()
  endif()
endif()

