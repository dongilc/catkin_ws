;; Auto-generated. Do not edit!


(when (boundp 'amg_p1::LA_Message)
  (if (not (find-package "AMG_P1"))
    (make-package "AMG_P1"))
  (shadow 'LA_Message (find-package "AMG_P1")))
(unless (find-package "AMG_P1::LA_MESSAGE")
  (make-package "AMG_P1::LA_MESSAGE"))

(in-package "ROS")
;;//! \htmlinclude LA_Message.msg.html


(defclass amg_p1::LA_Message
  :super ros::object
  :slots (_stamp _deg_total_target _deg_total_now ))

(defmethod amg_p1::LA_Message
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:deg_total_target __deg_total_target) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:deg_total_now __deg_total_now) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _deg_total_target __deg_total_target)
   (setq _deg_total_now __deg_total_now)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:deg_total_target
   (&optional __deg_total_target)
   (if __deg_total_target (setq _deg_total_target __deg_total_target)) _deg_total_target)
  (:deg_total_now
   (&optional __deg_total_now)
   (if __deg_total_now (setq _deg_total_now __deg_total_now)) _deg_total_now)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64[] _deg_total_target
    (* 8    (length _deg_total_target)) 4
    ;; float64[] _deg_total_now
    (* 8    (length _deg_total_now)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64[] _deg_total_target
     (write-long (length _deg_total_target) s)
     (dotimes (i (length _deg_total_target))
       (sys::poke (elt _deg_total_target i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _deg_total_now
     (write-long (length _deg_total_now) s)
     (dotimes (i (length _deg_total_now))
       (sys::poke (elt _deg_total_now i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _deg_total_target
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _deg_total_target (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _deg_total_target i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _deg_total_now
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _deg_total_now (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _deg_total_now i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get amg_p1::LA_Message :md5sum-) "7905fa336d4f2fe4db8c49c8192c0986")
(setf (get amg_p1::LA_Message :datatype-) "amg_p1/LA_Message")
(setf (get amg_p1::LA_Message :definition-)
      "time stamp

float64[] deg_total_target
float64[] deg_total_now
")



(provide :amg_p1/LA_Message "7905fa336d4f2fe4db8c49c8192c0986")


