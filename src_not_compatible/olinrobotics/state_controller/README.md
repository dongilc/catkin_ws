# Overview
The state controller is designed to act as the midbrain of a robot - facilitating easy integration of and switching between safety protocols, remote control, and fully autonomous behaviors. The controller can be configured to collect commands from an arbitrary number of nodes and send the appropriate messages through to the hindbrain. The state controller also handles activating/disactivating the robot and interacts with the softestop.

# ROS Structure
([Diagram of the ROS Nodes](https://photos.app.goo.gl/ZgS1Ykb9EHDQ4bWTA))

_graphic created using_ `rosrun rqt_graph rqt_graph`

- Topics
  - Subscribers (namespace `/state_controller`)
    - `/cmd_state`: Changes behavior being passed through the state controller (String)
    - `/cmd_activated`: Activates/disactivates robot (Bool)
    - `/cmd_behavior`: Receives control messages (TwistLabeled)
  - Publishers
    - `/cmd_twist`: Outputs control message corresponding to current behavior (Twist)
    - `/cmd_hitch`: Outputs control message corresponding to current behavior for hitch (Pose) - use z position value for height (meters off of ground, limited to -0.3 to 0.3), use y orientation for angle (degrees, limited to -45 to 45)
    - `/state`: Outputs current state controller selected state (String)

# Writing a Behavior Node
See Wiki Page ([link](https://github.com/olinrobotics/state_controller/wiki/Tutorial:WritingBehaviorNode(Cpp)))
