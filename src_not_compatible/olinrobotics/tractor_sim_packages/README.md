# tractor_sim_packages
Temporary place to keep packages that work together to generate pointclouds

# Dependencies
tractor_sim
gravl 

# Setup


# Usage
+ roslaunch tractor_sim_gazebo tractor_sim.launch
+ roslaunch gravl mainstate.launch
+ roslaunch gravl teleop.launch 
+ roslaunch sim_odom start_odom.launch 
+ roslaunch sim_localization bringup.launch
+ roslaunch laser_to_pcl start.launch
+ roslaunch tractor_sim_description tractor_sim_rviz_amcl.launch


# To Do
+ Make separate rviz files
+ Fix dependencies
+ Make appropriate launch files (bringup_min and bringup)
