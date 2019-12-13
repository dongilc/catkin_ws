;; Auto-generated. Do not edit!


(when (boundp 'vesc_msgs::VescGetCustomApp)
  (if (not (find-package "VESC_MSGS"))
    (make-package "VESC_MSGS"))
  (shadow 'VescGetCustomApp (find-package "VESC_MSGS")))
(unless (find-package "VESC_MSGS::VESCGETCUSTOMAPP")
  (make-package "VESC_MSGS::VESCGETCUSTOMAPP"))

(in-package "ROS")
;;//! \htmlinclude VescGetCustomApp.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vesc_msgs::VescGetCustomApp
  :super ros::object
  :slots (_header _send_mode_index1 _fw_ver_major _fw_ver_minor _fault_code _app_status_code _send_mode_index2 _can_devs_num _can_id _custom_status _enc_rps _enc_rad _current _duty ))

(defmethod vesc_msgs::VescGetCustomApp
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:send_mode_index1 __send_mode_index1) 0)
    ((:fw_ver_major __fw_ver_major) 0)
    ((:fw_ver_minor __fw_ver_minor) 0)
    ((:fault_code __fault_code) 0)
    ((:app_status_code __app_status_code) 0)
    ((:send_mode_index2 __send_mode_index2) 0)
    ((:can_devs_num __can_devs_num) 0)
    ((:can_id __can_id) (make-array 0 :initial-element 0 :element-type :integer))
    ((:custom_status __custom_status) (make-array 0 :initial-element 0 :element-type :integer))
    ((:enc_rps __enc_rps) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:enc_rad __enc_rad) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:current __current) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:duty __duty) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _send_mode_index1 (round __send_mode_index1))
   (setq _fw_ver_major (round __fw_ver_major))
   (setq _fw_ver_minor (round __fw_ver_minor))
   (setq _fault_code (round __fault_code))
   (setq _app_status_code (round __app_status_code))
   (setq _send_mode_index2 (round __send_mode_index2))
   (setq _can_devs_num (round __can_devs_num))
   (setq _can_id __can_id)
   (setq _custom_status __custom_status)
   (setq _enc_rps __enc_rps)
   (setq _enc_rad __enc_rad)
   (setq _current __current)
   (setq _duty __duty)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:send_mode_index1
   (&optional __send_mode_index1)
   (if __send_mode_index1 (setq _send_mode_index1 __send_mode_index1)) _send_mode_index1)
  (:fw_ver_major
   (&optional __fw_ver_major)
   (if __fw_ver_major (setq _fw_ver_major __fw_ver_major)) _fw_ver_major)
  (:fw_ver_minor
   (&optional __fw_ver_minor)
   (if __fw_ver_minor (setq _fw_ver_minor __fw_ver_minor)) _fw_ver_minor)
  (:fault_code
   (&optional __fault_code)
   (if __fault_code (setq _fault_code __fault_code)) _fault_code)
  (:app_status_code
   (&optional __app_status_code)
   (if __app_status_code (setq _app_status_code __app_status_code)) _app_status_code)
  (:send_mode_index2
   (&optional __send_mode_index2)
   (if __send_mode_index2 (setq _send_mode_index2 __send_mode_index2)) _send_mode_index2)
  (:can_devs_num
   (&optional __can_devs_num)
   (if __can_devs_num (setq _can_devs_num __can_devs_num)) _can_devs_num)
  (:can_id
   (&optional __can_id)
   (if __can_id (setq _can_id __can_id)) _can_id)
  (:custom_status
   (&optional __custom_status)
   (if __custom_status (setq _custom_status __custom_status)) _custom_status)
  (:enc_rps
   (&optional __enc_rps)
   (if __enc_rps (setq _enc_rps __enc_rps)) _enc_rps)
  (:enc_rad
   (&optional __enc_rad)
   (if __enc_rad (setq _enc_rad __enc_rad)) _enc_rad)
  (:current
   (&optional __current)
   (if __current (setq _current __current)) _current)
  (:duty
   (&optional __duty)
   (if __duty (setq _duty __duty)) _duty)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _send_mode_index1
    4
    ;; int32 _fw_ver_major
    4
    ;; int32 _fw_ver_minor
    4
    ;; int32 _fault_code
    4
    ;; int32 _app_status_code
    4
    ;; int32 _send_mode_index2
    4
    ;; int32 _can_devs_num
    4
    ;; int32[] _can_id
    (* 4    (length _can_id)) 4
    ;; int32[] _custom_status
    (* 4    (length _custom_status)) 4
    ;; float64[] _enc_rps
    (* 8    (length _enc_rps)) 4
    ;; float64[] _enc_rad
    (* 8    (length _enc_rad)) 4
    ;; float64[] _current
    (* 8    (length _current)) 4
    ;; float64[] _duty
    (* 8    (length _duty)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _send_mode_index1
       (write-long _send_mode_index1 s)
     ;; int32 _fw_ver_major
       (write-long _fw_ver_major s)
     ;; int32 _fw_ver_minor
       (write-long _fw_ver_minor s)
     ;; int32 _fault_code
       (write-long _fault_code s)
     ;; int32 _app_status_code
       (write-long _app_status_code s)
     ;; int32 _send_mode_index2
       (write-long _send_mode_index2 s)
     ;; int32 _can_devs_num
       (write-long _can_devs_num s)
     ;; int32[] _can_id
     (write-long (length _can_id) s)
     (dotimes (i (length _can_id))
       (write-long (elt _can_id i) s)
       )
     ;; int32[] _custom_status
     (write-long (length _custom_status) s)
     (dotimes (i (length _custom_status))
       (write-long (elt _custom_status i) s)
       )
     ;; float64[] _enc_rps
     (write-long (length _enc_rps) s)
     (dotimes (i (length _enc_rps))
       (sys::poke (elt _enc_rps i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _enc_rad
     (write-long (length _enc_rad) s)
     (dotimes (i (length _enc_rad))
       (sys::poke (elt _enc_rad i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _current
     (write-long (length _current) s)
     (dotimes (i (length _current))
       (sys::poke (elt _current i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _duty
     (write-long (length _duty) s)
     (dotimes (i (length _duty))
       (sys::poke (elt _duty i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _send_mode_index1
     (setq _send_mode_index1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _fw_ver_major
     (setq _fw_ver_major (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _fw_ver_minor
     (setq _fw_ver_minor (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _fault_code
     (setq _fault_code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _app_status_code
     (setq _app_status_code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _send_mode_index2
     (setq _send_mode_index2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _can_devs_num
     (setq _can_devs_num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32[] _can_id
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _can_id (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _can_id i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32[] _custom_status
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _custom_status (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _custom_status i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; float64[] _enc_rps
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _enc_rps (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _enc_rps i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _enc_rad
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _enc_rad (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _enc_rad i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _current
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _current (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _current i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _duty
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _duty (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _duty i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get vesc_msgs::VescGetCustomApp :md5sum-) "daa4967cc5ef43655bd186c327b3176d")
(setf (get vesc_msgs::VescGetCustomApp :datatype-) "vesc_msgs/VescGetCustomApp")
(setf (get vesc_msgs::VescGetCustomApp :definition-)
      "# VESCuino CDI CUSTOM_APP RX Messages

Header  header

# FW Version Data
int32 send_mode_index1
int32 fw_ver_major
int32 fw_ver_minor

# Original Get Value Data
#float64 voltage_input        # input voltage (volt)
#float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)
#float64 current_motor        # motor current (ampere)
#float64 current_input        # input current (ampere)
#float64 speed                # motor electrical speed (revolutions per minute) 
#float64 duty_cycle           # duty cycle (0 to 1)
#float64 charge_drawn         # electric charge drawn from input (ampere-hour)
#float64 charge_regen         # electric charge regenerated to input (ampere-hour)
#float64 energy_drawn         # energy drawn from input (watt-hour)
#float64 energy_regen         # energy regenerated to input (watt-hour)
#float64 displacement         # net tachometer (counts)
#float64 distance_traveled    # total tachnometer (counts)
int32   fault_code
#float64 pid_pos_now    		 # pid position now (deg) 0~360

int32 app_status_code        # application status code

# CAN Status Data 
int32 send_mode_index2
int32 can_devs_num
int32[] can_id
int32[] custom_status

# Raw Encoder Data
float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) 
float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)
float64[] current			 # can status - current
float64[] duty			     # can status - duty

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :vesc_msgs/VescGetCustomApp "daa4967cc5ef43655bd186c327b3176d")


