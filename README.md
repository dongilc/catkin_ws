# catkin_ws_openrobot

## Preparation

Run 

```
catkin_make
```

if there are errors, run rosdep as below

```
rosdep install --from-paths . --ignore-src -r -y
```

if rosdep is not installed then,

```
sudo apt install python-rosdep2
```

after then run

```
sudo rosdep init
rosdep update
rosdep install --from-paths . --ignore-src -r -y
```

After all the dependencies are installed run `catkin_make` again, and then

```
source devel/setup.bash
roslaunch openrobot_control_example openrobot_control_example.launch
```