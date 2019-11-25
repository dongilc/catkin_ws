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
  :slots (_header _send_mode_index1 _fw_ver_major _fw_ver_minor _voltage_input _temperature_pcb _current_motor _current_input _speed _duty_cycle _charge_drawn _charge_regen _energy_drawn _energy_regen _displacement _distance_traveled _fault_code _pid_pos_now _enc_rps _enc_rad _app_status_code _send_mode_index2 _can_dev_num _can_id ))

(defmethod vesc_msgs::VescGetCustomApp
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:send_mode_index1 __send_mode_index1) 0)
    ((:fw_ver_major __fw_ver_major) 0)
    ((:fw_ver_minor __fw_ver_minor) 0)
    ((:voltage_input __voltage_input) 0.0)
    ((:temperature_pcb __temperature_pcb) 0.0)
    ((:current_motor __current_motor) 0.0)
    ((:current_input __current_input) 0.0)
    ((:speed __speed) 0.0)
    ((:duty_cycle __duty_cycle) 0.0)
    ((:charge_drawn __charge_drawn) 0.0)
    ((:charge_regen __charge_regen) 0.0)
    ((:energy_drawn __energy_drawn) 0.0)
    ((:energy_regen __energy_regen) 0.0)
    ((:displacement __displacement) 0.0)
    ((:distance_traveled __distance_traveled) 0.0)
    ((:fault_code __fault_code) 0)
    ((:pid_pos_now __pid_pos_now) 0.0)
    ((:enc_rps __enc_rps) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:enc_rad __enc_rad) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:app_status_code __app_status_code) 0)
    ((:send_mode_index2 __send_mode_index2) 0)
    ((:can_dev_num __can_dev_num) 0)
    ((:can_id __can_id) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _header __header)
   (setq _send_mode_index1 (round __send_mode_index1))
   (setq _fw_ver_major (round __fw_ver_major))
   (setq _fw_ver_minor (round __fw_ver_minor))
   (setq _voltage_input (float __voltage_input))
   (setq _temperature_pcb (float __temperature_pcb))
   (setq _current_motor (float __current_motor))
   (setq _current_input (float __current_input))
   (setq _speed (float __speed))
   (setq _duty_cycle (float __duty_cycle))
   (setq _charge_drawn (float __charge_drawn))
   (setq _charge_regen (float __charge_regen))
   (setq _energy_drawn (float __energy_drawn))
   (setq _energy_regen (float __energy_regen))
   (setq _displacement (float __displacement))
   (setq _distance_traveled (float __distance_traveled))
   (setq _fault_code (round __fault_code))
   (setq _pid_pos_now (float __pid_pos_now))
   (setq _enc_rps __enc_rps)
   (setq _enc_rad __enc_rad)
   (setq _app_status_code (round __app_status_code))
   (setq _send_mode_index2 (round __send_mode_index2))
   (setq _can_dev_num (round __can_dev_num))
   (setq _can_id __can_id)
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
  (:voltage_input
   (&optional __voltage_input)
   (if __voltage_input (setq _voltage_input __voltage_input)) _voltage_input)
  (:temperature_pcb
   (&optional __temperature_pcb)
   (if __temperature_pcb (setq _temperature_pcb __temperature_pcb)) _temperature_pcb)
  (:current_motor
   (&optional __current_motor)
   (if __current_motor (setq _current_motor __current_motor)) _current_motor)
  (:current_input
   (&optional __current_input)
   (if __current_input (setq _current_input __current_input)) _current_input)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:duty_cycle
   (&optional __duty_cycle)
   (if __duty_cycle (setq _duty_cycle __duty_cycle)) _duty_cycle)
  (:charge_drawn
   (&optional __charge_drawn)
   (if __charge_drawn (setq _charge_drawn __charge_drawn)) _charge_drawn)
  (:charge_regen
   (&optional __charge_regen)
   (if __charge_regen (setq _charge_regen __charge_regen)) _charge_regen)
  (:energy_drawn
   (&optional __energy_drawn)
   (if __energy_drawn (setq _energy_drawn __energy_drawn)) _energy_drawn)
  (:energy_regen
   (&optional __energy_regen)
   (if __energy_regen (setq _energy_regen __energy_regen)) _energy_regen)
  (:displacement
   (&optional __displacement)
   (if __displacement (setq _displacement __displacement)) _displacement)
  (:distance_traveled
   (&optional __distance_traveled)
   (if __distance_traveled (setq _distance_traveled __distance_traveled)) _distance_traveled)
  (:fault_code
   (&optional __fault_code)
   (if __fault_code (setq _fault_code __fault_code)) _fault_code)
  (:pid_pos_now
   (&optional __pid_pos_now)
   (if __pid_pos_now (setq _pid_pos_now __pid_pos_now)) _pid_pos_now)
  (:enc_rps
   (&optional __enc_rps)
   (if __enc_rps (setq _enc_rps __enc_rps)) _enc_rps)
  (:enc_rad
   (&optional __enc_rad)
   (if __enc_rad (setq _enc_rad __enc_rad)) _enc_rad)
  (:app_status_code
   (&optional __app_status_code)
   (if __app_status_code (setq _app_status_code __app_status_code)) _app_status_code)
  (:send_mode_index2
   (&optional __send_mode_index2)
   (if __send_mode_index2 (setq _send_mode_index2 __send_mode_index2)) _send_mode_index2)
  (:can_dev_num
   (&optional __can_dev_num)
   (if __can_dev_num (setq _can_dev_num __can_dev_num)) _can_dev_num)
  (:can_id
   (&optional __can_id)
   (if __can_id (setq _can_id __can_id)) _can_id)
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
    ;; float64 _voltage_input
    8
    ;; float64 _temperature_pcb
    8
    ;; float64 _current_motor
    8
    ;; float64 _current_input
    8
    ;; float64 _speed
    8
    ;; float64 _duty_cycle
    8
    ;; float64 _charge_drawn
    8
    ;; float64 _charge_regen
    8
    ;; float64 _energy_drawn
    8
    ;; float64 _energy_regen
    8
    ;; float64 _displacement
    8
    ;; float64 _distance_traveled
    8
    ;; int32 _fault_code
    4
    ;; float64 _pid_pos_now
    8
    ;; float64[] _enc_rps
    (* 8    (length _enc_rps)) 4
    ;; float64[] _enc_rad
    (* 8    (length _enc_rad)) 4
    ;; int32 _app_status_code
    4
    ;; int32 _send_mode_index2
    4
    ;; int32 _can_dev_num
    4
    ;; int32[] _can_id
    (* 4    (length _can_id)) 4
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
     ;; float64 _voltage_input
       (sys::poke _voltage_input (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _temperature_pcb
       (sys::poke _temperature_pcb (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _current_motor
       (sys::poke _current_motor (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _current_input
       (sys::poke _current_input (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _duty_cycle
       (sys::poke _duty_cycle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _charge_drawn
       (sys::poke _charge_drawn (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _charge_regen
       (sys::poke _charge_regen (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _energy_drawn
       (sys::poke _energy_drawn (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _energy_regen
       (sys::poke _energy_regen (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _displacement
       (sys::poke _displacement (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _distance_traveled
       (sys::poke _distance_traveled (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _fault_code
       (write-long _fault_code s)
     ;; float64 _pid_pos_now
       (sys::poke _pid_pos_now (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
     ;; int32 _app_status_code
       (write-long _app_status_code s)
     ;; int32 _send_mode_index2
       (write-long _send_mode_index2 s)
     ;; int32 _can_dev_num
       (write-long _can_dev_num s)
     ;; int32[] _can_id
     (write-long (length _can_id) s)
     (dotimes (i (length _can_id))
       (write-long (elt _can_id i) s)
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
   ;; float64 _voltage_input
     (setq _voltage_input (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _temperature_pcb
     (setq _temperature_pcb (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _current_motor
     (setq _current_motor (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _current_input
     (setq _current_input (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed
     (setq _speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _duty_cycle
     (setq _duty_cycle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _charge_drawn
     (setq _charge_drawn (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _charge_regen
     (setq _charge_regen (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _energy_drawn
     (setq _energy_drawn (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _energy_regen
     (setq _energy_regen (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _displacement
     (setq _displacement (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _distance_traveled
     (setq _distance_traveled (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _fault_code
     (setq _fault_code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _pid_pos_now
     (setq _pid_pos_now (sys::peek buf ptr- :double)) (incf ptr- 8)
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
   ;; int32 _app_status_code
     (setq _app_status_code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _send_mode_index2
     (setq _send_mode_index2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _can_dev_num
     (setq _can_dev_num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32[] _can_id
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _can_id (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _can_id i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get vesc_msgs::VescGetCustomApp :md5sum-) "90215f495cfc9bdca67860d224bb3fe7")
(setf (get vesc_msgs::VescGetCustomApp :datatype-) "vesc_msgs/VescGetCustomApp")
(setf (get vesc_msgs::VescGetCustomApp :definition-)
      "# VESCuino CDI CUSTOM_APP RX Messages

Header  header

# FW Version Data
int32 send_mode_index1
int32 fw_ver_major
int32 fw_ver_minor

# Original Get Value Data
float64 voltage_input        # input voltage (volt)
float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)
float64 current_motor        # motor current (ampere)
float64 current_input        # input current (ampere)
float64 speed                # motor electrical speed (revolutions per minute) 
float64 duty_cycle           # duty cycle (0 to 1)
float64 charge_drawn         # electric charge drawn from input (ampere-hour)
float64 charge_regen         # electric charge regenerated to input (ampere-hour)
float64 energy_drawn         # energy drawn from input (watt-hour)
float64 energy_regen         # energy regenerated to input (watt-hour)
float64 displacement         # net tachometer (counts)
float64 distance_traveled    # total tachnometer (counts)
int32   fault_code
float64 pid_pos_now    		 # pid position now (deg) 0~360

# Raw Encoder Data
float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) 
float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)
int32 app_status_code        # application status code

# CAN Status Data 
int32 send_mode_index2
int32 can_dev_num
int32[] can_id
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



(provide :vesc_msgs/VescGetCustomApp "90215f495cfc9bdca67860d224bb3fe7")


