;; Auto-generated. Do not edit!


(when (boundp 'diff_wheel_platform::CTM_Message)
  (if (not (find-package "DIFF_WHEEL_PLATFORM"))
    (make-package "DIFF_WHEEL_PLATFORM"))
  (shadow 'CTM_Message (find-package "DIFF_WHEEL_PLATFORM")))
(unless (find-package "DIFF_WHEEL_PLATFORM::CTM_MESSAGE")
  (make-package "DIFF_WHEEL_PLATFORM::CTM_MESSAGE"))

(in-package "ROS")
;;//! \htmlinclude CTM_Message.msg.html


(defclass diff_wheel_platform::CTM_Message
  :super ros::object
  :slots (_stamp _target_vel _current_vel _target_pos _current_pos ))

(defmethod diff_wheel_platform::CTM_Message
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:target_vel __target_vel) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:current_vel __current_vel) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:target_pos __target_pos) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:current_pos __current_pos) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _target_vel __target_vel)
   (setq _current_vel __current_vel)
   (setq _target_pos __target_pos)
   (setq _current_pos __current_pos)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:target_vel
   (&optional __target_vel)
   (if __target_vel (setq _target_vel __target_vel)) _target_vel)
  (:current_vel
   (&optional __current_vel)
   (if __current_vel (setq _current_vel __current_vel)) _current_vel)
  (:target_pos
   (&optional __target_pos)
   (if __target_pos (setq _target_pos __target_pos)) _target_pos)
  (:current_pos
   (&optional __current_pos)
   (if __current_pos (setq _current_pos __current_pos)) _current_pos)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64[] _target_vel
    (* 8    (length _target_vel)) 4
    ;; float64[] _current_vel
    (* 8    (length _current_vel)) 4
    ;; float64[] _target_pos
    (* 8    (length _target_pos)) 4
    ;; float64[] _current_pos
    (* 8    (length _current_pos)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64[] _target_vel
     (write-long (length _target_vel) s)
     (dotimes (i (length _target_vel))
       (sys::poke (elt _target_vel i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _current_vel
     (write-long (length _current_vel) s)
     (dotimes (i (length _current_vel))
       (sys::poke (elt _current_vel i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _target_pos
     (write-long (length _target_pos) s)
     (dotimes (i (length _target_pos))
       (sys::poke (elt _target_pos i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _current_pos
     (write-long (length _current_pos) s)
     (dotimes (i (length _current_pos))
       (sys::poke (elt _current_pos i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _target_vel
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target_vel (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _target_vel i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _current_vel
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _current_vel (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _current_vel i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _target_pos
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target_pos (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _target_pos i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _current_pos
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _current_pos (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _current_pos i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get diff_wheel_platform::CTM_Message :md5sum-) "ed2ad4965391603c3242af0f3ef56859")
(setf (get diff_wheel_platform::CTM_Message :datatype-) "diff_wheel_platform/CTM_Message")
(setf (get diff_wheel_platform::CTM_Message :definition-)
      "time stamp
float64[] target_vel
float64[] current_vel
float64[] target_pos
float64[] current_pos
")



(provide :diff_wheel_platform/CTM_Message "ed2ad4965391603c3242af0f3ef56859")


