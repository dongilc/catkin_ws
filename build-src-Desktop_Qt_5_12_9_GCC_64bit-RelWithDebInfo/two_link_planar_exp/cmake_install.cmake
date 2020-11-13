# Install script for directory: /home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/two_link_planar_exp

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/two_link_planar_exp/catkin_generated/installspace/two_link_planar_exp.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/two_link_planar_exp/cmake" TYPE FILE FILES
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/two_link_planar_exp/catkin_generated/installspace/two_link_planar_expConfig.cmake"
    "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/two_link_planar_exp/catkin_generated/installspace/two_link_planar_expConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/two_link_planar_exp" TYPE FILE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/src/two_link_planar_exp/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp" TYPE EXECUTABLE FILES "/home/cdi/Dropbox/Workspace_CDI/workspace_prog/catkin_ws/build-src-Desktop_Qt_5_12_9_GCC_64bit-RelWithDebInfo/devel/lib/two_link_planar_exp/two_link_planar_exp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp"
         OLD_RPATH "/opt/ros/melodic/lib:/usr/local/qwt-6.1.5/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/two_link_planar_exp/two_link_planar_exp")
    endif()
  endif()
endif()

