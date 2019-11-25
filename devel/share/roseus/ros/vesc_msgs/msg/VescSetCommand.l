;; Auto-generated. Do not edit!


(when (boundp 'vesc_msgs::VescSetCommand)
  (if (not (find-package "VESC_MSGS"))
    (make-package "VESC_MSGS"))
  (shadow 'VescSetCommand (find-package "VESC_MSGS")))
(unless (find-package "VESC_MSGS::VESCSETCOMMAND")
  (make-package "VESC_MSGS::VESCSETCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude VescSetCommand.msg.html


(defclass vesc_msgs::VescSetCommand
  :super ros::object
  :slots (_data _send_can _can_id ))

(defmethod vesc_msgs::VescSetCommand
  (:init
   (&key
    ((:data __data) 0.0)
    ((:send_can __send_can) nil)
    ((:can_id __can_id) 0)
    )
   (send-super :init)
   (setq _data (float __data))
   (setq _send_can __send_can)
   (setq _can_id (round __can_id))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:send_can
   (&optional __send_can)
   (if __send_can (setq _send_can __send_can)) _send_can)
  (:can_id
   (&optional __can_id)
   (if __can_id (setq _can_id __can_id)) _can_id)
  (:serialization-length
   ()
   (+
    ;; float64 _data
    8
    ;; bool _send_can
    1
    ;; uint8 _can_id
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _data
       (sys::poke _data (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _send_can
       (if _send_can (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _can_id
       (write-byte _can_id s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _data
     (setq _data (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _send_can
     (setq _send_can (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _can_id
     (setq _can_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get vesc_msgs::VescSetCommand :md5sum-) "9cffe44297165322576d6c2378fd0593")
(setf (get vesc_msgs::VescSetCommand :datatype-) "vesc_msgs/VescSetCommand")
(setf (get vesc_msgs::VescSetCommand :definition-)
      "float64 data
bool  send_can
uint8 can_id
")



(provide :vesc_msgs/VescSetCommand "9cffe44297165322576d6c2378fd0593")


