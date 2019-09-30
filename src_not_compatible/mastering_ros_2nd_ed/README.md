# **Mastering ROS for robotics programming** _2nd edition_
#### Design, build and simulate complex robots using Robot Operating System.


[Book](https://www.packtpub.com/hardware-and-creative/mastering-ros-robotics-programming-second-edition) source code main repository.

![book_cover](http://wpage.unina.it/jonathan.cacace/Media/book_cover.png "mastering_ros_for_robotics_programming")

## **Author**
[Jonathan Cacace](http://wpage.unina.it/jonathan.cacace), PhD.

First edition of the book by Dr. [Josep Lentin](https://www.linkedin.com/in/lentinjoseph/): [Mastering ROS for robotics programming](http://mastering-ros.com/).

### **About the book**
Todays era is gaining a lot of traction towards robotics in various industries where consistency and perfection is mattered the most. Automation is playing a major role today, and most of it is achieved with robotic applications and various platforms that support robotics. The Robot Operating System (ROS) is a modular software platform to develop generic robotic applications. This book will be focusing on the most stable release of ROS (Kinetic Kame) and will discuss the advanced concepts in robotics and how to program using ROS.

_Paperback_: 660 pages.  
_Publisher_: Packt Publishing - ebooks Account.  
_Language_: English.  
_ISBN-10_: 1788478959.  
_ISBN-13_: 978-1788478953.  

### **Difference between first and second edition**
The first edition was based on ROS Indigo and Jade. In this edition we update concepts and source codes eventually deprecated or outdated. New fundamental topics for robotic applications and two completely new chapters have been added in this _2nd_ edition. 

## **Description**
This repository contains one sub-module for each chapter source code, in this way you can directly clone and pull repository to be updated with the last version of the software of the whole book.

Click on the repository name to directly get the code use in the chapters.

- **Chapter 1**: _Introduction to ROS_

- **Chapter 2**: _Introduction to ROS - Part 2_:
  - [mastering\_ros\_demo\_pkg](https://github.com/jocacace/mastering_ros_demo_pkg)  

- **Chapter 3**: _Working with 3D Robot Modeling in ROS_
  - [mastering\_ros\_robot\_description\_pkg](https://github.com/jocacace/mastering_ros_robot_description_pkg)  

- **Chapter 4**: _Simulating Robots Using ROS and Gazebo_
  - [seven\_dof\_arm\_gazebo](https://github.com/jocacace/seven_dof_arm_gazebo)
  - [diff\_wheeled\_robot\_gazebo](https://github.com/jocacace/diff_wheeled_robot_gazebo)
  - [diff\_wheeled\_robot\_control](https://github.com/jocacace/diff_wheeled_robot_control)  
- **Chapter 5**: _Simulating Robots Using ROS and V-REP_ 
  - [vrep\_plugin](https://github.com/jocacace/vrep_plugin/)
  - [vrep\_common](https://github.com/jocacace/vrep_common/)
  - [vrep\_demo\_pkg](https://github.com/jocacace/vrep_demo_pkg)

- **Chapter 6**: _Using ROS MoveIt! and Navigation stack_  
  - [seven\_dof\_arm\_config](https://github.com/jocacace/seven_dof_arm_config)

- **Chapter 7**: _Working with Pluginlib, Nodelets and Gazebo plugins_ 
  - [gazebo\_basic\_world\_plugin](https://github.com/jocacace/gazebo_basic_world_plugin)
  - [plugin\_calculator](https://github.com/jocacace/plugin_calculator)
  - [nodelet\_hello\_world](https://github.com/jocacace/nodelet_hello_world)

- **Chapter 8**: _Writing ROS Controllers and Visualization plugins_
  - [my\_controller](https://github.com/jocacace/my_controller)
  - [rviz\_teleop\_commander](https://github.com/jocacace/rviz_teleop_commander)

- **Chapter 9**: _Interfacing I/O boards, sensors and actuators to ROS_  
(check book source code)

- **Chapter 10**: _Programming Vision sensors using ROS, Open-CV and PCL_
  - [cv\_bridge\_tutorial\_pkg](https://github.com/jocacace/cv_bridge_tutorial_pkg)
  - [pcl\_ros\_tutorial](https://github.com/jocacace/pcl_ros_tutorial)
  - [apriltags\_ros\_demo](https://github.com/jocacace/apriltags_ros_demo)


- **Chapter 11**: _Building and interfacing a differential drive mobile robot hardware in ROS_  
(check book source code)

- **Chapter 12**: _Exploring advanced capabilities of ROS-MoveIt!_
  - [seven\_dof\_arm\_test](https://github.com/jocacace/seven_dof_arm_test)
 
- **Chapter 13**: _Using ROS in Matlab and Simulink_ 
	- [ros\_matlab\_test](https://github.com/jocacace/ros_matlab_test)

- **Chapter 14**: _ROS for Industrial Robots_  
(check book source code)

- **Chapter 15**: _Troubleshooting and best 
practices in ROS_



### **Installation** 
Download all the submodules in the _src_ directory of your ROS workspace:

```git clone --recursive https://github.com/jocacace/mastering_ros_2nd_ed```

To pull the submodules in case of remote repository update, run the following command in the mastering\_ros\_2nd\_ed directory:
 
```git submodule update --init --recursive```  
```git pull```

## **Compilation**
```catkin_make -j1```

#### **Dependencies** 
To compile the workspace with this meta-package you should installa the following dependencies  
```sudo apt-get install ros-kinetic-controller-manager ros-kinetic-joint-state-controller ros-kinetic-joy ros-kinetic-gazebo-ros-control ros-kinetic-moveit-*```
### **Get this book** (in pre-order)
- [Packt Publishing](https://www.packtpub.com/hardware-and-creative/mastering-ros-robotics-programming-second-edition) 
- [Amazon](https://www.amazon.com/Mastering-ROS-Robotics-Programming-Second/dp/1788478959)
