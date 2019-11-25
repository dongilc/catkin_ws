;; Auto-generated. Do not edit!


(when (boundp 'amg_p1::CTM_Message)
  (if (not (find-package "AMG_P1"))
    (make-package "AMG_P1"))
  (shadow 'CTM_Message (find-package "AMG_P1")))
(unless (find-package "AMG_P1::CTM_MESSAGE")
  (make-package "AMG_P1::CTM_MESSAGE"))

(in-package "ROS")
;;//! \htmlinclude CTM_Message.msg.html


(defclass amg_p1::CTM_Message
  :super ros::object
  :slots (_stamp _vel_target _vel_now _pos_target _pos_now _current ))

(defmethod amg_p1::CTM_Message
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:vel_target __vel_target) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:vel_now __vel_now) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:pos_target __pos_target) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:pos_now __pos_now) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:current __current) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _vel_target __vel_target)
   (setq _vel_now __vel_now)
   (setq _pos_target __pos_target)
   (setq _pos_now __pos_now)
   (setq _current __current)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:vel_target
   (&optional __vel_target)
   (if __vel_target (setq _vel_target __vel_target)) _vel_target)
  (:vel_now
   (&optional __vel_now)
   (if __vel_now (setq _vel_now __vel_now)) _vel_now)
  (:pos_target
   (&optional __pos_target)
   (if __pos_target (setq _pos_target __pos_target)) _pos_target)
  (:pos_now
   (&optional __pos_now)
   (if __pos_now (setq _pos_now __pos_now)) _pos_now)
  (:current
   (&optional __current)
   (if __current (setq _current __current)) _current)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64[] _vel_target
    (* 8    (length _vel_target)) 4
    ;; float64[] _vel_now
    (* 8    (length _vel_now)) 4
    ;; float64[] _pos_target
    (* 8    (length _pos_target)) 4
    ;; float64[] _pos_now
    (* 8    (length _pos_now)) 4
    ;; float64[] _current
    (* 8    (length _current)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64[] _vel_target
     (write-long (length _vel_target) s)
     (dotimes (i (length _vel_target))
       (sys::poke (elt _vel_target i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _vel_now
     (write-long (length _vel_now) s)
     (dotimes (i (length _vel_now))
       (sys::poke (elt _vel_now i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _pos_target
     (write-long (length _pos_target) s)
     (dotimes (i (length _pos_target))
       (sys::poke (elt _pos_target i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _pos_now
     (write-long (length _pos_now) s)
     (dotimes (i (length _pos_now))
       (sys::poke (elt _pos_now i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _current
     (write-long (length _current) s)
     (dotimes (i (length _current))
       (sys::poke (elt _current i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _vel_target
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _vel_target (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _vel_target i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _vel_now
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _vel_now (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _vel_now i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _pos_target
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _pos_target (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _pos_target i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _pos_now
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _pos_now (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _pos_now i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _current
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _current (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _current i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get amg_p1::CTM_Message :md5sum-) "b224801613d8b47decc0b74376cfcb04")
(setf (get amg_p1::CTM_Message :datatype-) "amg_p1/CTM_Message")
(setf (get amg_p1::CTM_Message :definition-)
      "time stamp
float64[] vel_target
float64[] vel_now
float64[] pos_target
float64[] pos_now
float64[] current
")



(provide :amg_p1/CTM_Message "b224801613d8b47decc0b74376cfcb04")


