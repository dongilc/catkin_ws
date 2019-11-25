;; Auto-generated. Do not edit!


(when (boundp 'amg_p1::MP_Message)
  (if (not (find-package "AMG_P1"))
    (make-package "AMG_P1"))
  (shadow 'MP_Message (find-package "AMG_P1")))
(unless (find-package "AMG_P1::MP_MESSAGE")
  (make-package "AMG_P1::MP_MESSAGE"))

(in-package "ROS")
;;//! \htmlinclude MP_Message.msg.html


(defclass amg_p1::MP_Message
  :super ros::object
  :slots (_stamp _x _th _x_input _vel_out _theta_out ))

(defmethod amg_p1::MP_Message
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:x __x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:th __th) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:x_input __x_input) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:vel_out __vel_out) 0.0)
    ((:theta_out __theta_out) 0.0)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _x __x)
   (setq _th __th)
   (setq _x_input __x_input)
   (setq _vel_out (float __vel_out))
   (setq _theta_out (float __theta_out))
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:th
   (&optional __th)
   (if __th (setq _th __th)) _th)
  (:x_input
   (&optional __x_input)
   (if __x_input (setq _x_input __x_input)) _x_input)
  (:vel_out
   (&optional __vel_out)
   (if __vel_out (setq _vel_out __vel_out)) _vel_out)
  (:theta_out
   (&optional __theta_out)
   (if __theta_out (setq _theta_out __theta_out)) _theta_out)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64[] _x
    (* 8    (length _x)) 4
    ;; float64[] _th
    (* 8    (length _th)) 4
    ;; float64[] _x_input
    (* 8    (length _x_input)) 4
    ;; float64 _vel_out
    8
    ;; float64 _theta_out
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64[] _x
     (write-long (length _x) s)
     (dotimes (i (length _x))
       (sys::poke (elt _x i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _th
     (write-long (length _th) s)
     (dotimes (i (length _th))
       (sys::poke (elt _th i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _x_input
     (write-long (length _x_input) s)
     (dotimes (i (length _x_input))
       (sys::poke (elt _x_input i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _vel_out
       (sys::poke _vel_out (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta_out
       (sys::poke _theta_out (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _th
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _th (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _th i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _x_input
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x_input (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x_input i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64 _vel_out
     (setq _vel_out (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta_out
     (setq _theta_out (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get amg_p1::MP_Message :md5sum-) "79bb341ec382fab4793fae5691c7faf8")
(setf (get amg_p1::MP_Message :datatype-) "amg_p1/MP_Message")
(setf (get amg_p1::MP_Message :definition-)
      "time stamp
float64[] x
float64[] th
float64[] x_input

float64 vel_out
float64 theta_out
")



(provide :amg_p1/MP_Message "79bb341ec382fab4793fae5691c7faf8")


