;; Auto-generated. Do not edit!


(when (boundp 'vesc_msgs::VescSetCustomApp)
  (if (not (find-package "VESC_MSGS"))
    (make-package "VESC_MSGS"))
  (shadow 'VescSetCustomApp (find-package "VESC_MSGS")))
(unless (find-package "VESC_MSGS::VESCSETCUSTOMAPP")
  (make-package "VESC_MSGS::VESCSETCUSTOMAPP"))

(in-package "ROS")
;;//! \htmlinclude VescSetCustomApp.msg.html


(defclass vesc_msgs::VescSetCustomApp
  :super ros::object
  :slots (_num_of_id _id_set _comm_set _can_forward_set _value_set _data_bytes ))

(defmethod vesc_msgs::VescSetCustomApp
  (:init
   (&key
    ((:num_of_id __num_of_id) 0)
    ((:id_set __id_set) (make-array 0 :initial-element 0 :element-type :integer))
    ((:comm_set __comm_set) (make-array 0 :initial-element 0 :element-type :integer))
    ((:can_forward_set __can_forward_set) (let (r) (dotimes (i 0) (push nil r)) r))
    ((:value_set __value_set) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:data_bytes __data_bytes) 0)
    )
   (send-super :init)
   (setq _num_of_id (round __num_of_id))
   (setq _id_set __id_set)
   (setq _comm_set __comm_set)
   (setq _can_forward_set __can_forward_set)
   (setq _value_set __value_set)
   (setq _data_bytes (round __data_bytes))
   self)
  (:num_of_id
   (&optional __num_of_id)
   (if __num_of_id (setq _num_of_id __num_of_id)) _num_of_id)
  (:id_set
   (&optional __id_set)
   (if __id_set (setq _id_set __id_set)) _id_set)
  (:comm_set
   (&optional __comm_set)
   (if __comm_set (setq _comm_set __comm_set)) _comm_set)
  (:can_forward_set
   (&optional __can_forward_set)
   (if __can_forward_set (setq _can_forward_set __can_forward_set)) _can_forward_set)
  (:value_set
   (&optional __value_set)
   (if __value_set (setq _value_set __value_set)) _value_set)
  (:data_bytes
   (&optional __data_bytes)
   (if __data_bytes (setq _data_bytes __data_bytes)) _data_bytes)
  (:serialization-length
   ()
   (+
    ;; int32 _num_of_id
    4
    ;; int32[] _id_set
    (* 4    (length _id_set)) 4
    ;; int32[] _comm_set
    (* 4    (length _comm_set)) 4
    ;; bool[] _can_forward_set
    (* 1    (length _can_forward_set)) 4
    ;; float64[] _value_set
    (* 8    (length _value_set)) 4
    ;; int32 _data_bytes
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _num_of_id
       (write-long _num_of_id s)
     ;; int32[] _id_set
     (write-long (length _id_set) s)
     (dotimes (i (length _id_set))
       (write-long (elt _id_set i) s)
       )
     ;; int32[] _comm_set
     (write-long (length _comm_set) s)
     (dotimes (i (length _comm_set))
       (write-long (elt _comm_set i) s)
       )
     ;; bool[] _can_forward_set
     (write-long (length _can_forward_set) s)
     (dotimes (i (length _can_forward_set))
       (if (elt _can_forward_set i) (write-byte -1 s) (write-byte 0 s))
       )
     ;; float64[] _value_set
     (write-long (length _value_set) s)
     (dotimes (i (length _value_set))
       (sys::poke (elt _value_set i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; int32 _data_bytes
       (write-long _data_bytes s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _num_of_id
     (setq _num_of_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32[] _id_set
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _id_set (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _id_set i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32[] _comm_set
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _comm_set (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _comm_set i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; bool[] _can_forward_set
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _can_forward_set (make-list n))
     (dotimes (i n)
     (setf (elt _can_forward_set i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;; float64[] _value_set
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _value_set (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _value_set i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; int32 _data_bytes
     (setq _data_bytes (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get vesc_msgs::VescSetCustomApp :md5sum-) "c46f4ff65abd5670780793173869e6b9")
(setf (get vesc_msgs::VescSetCustomApp :datatype-) "vesc_msgs/VescSetCustomApp")
(setf (get vesc_msgs::VescSetCustomApp :definition-)
      "# VESCuino CDI CUSTOM_APP TX Messages

int32       num_of_id
int32[]     id_set
int32[]     comm_set
bool[]      can_forward_set
float64[]   value_set
int32       data_bytes
")



(provide :vesc_msgs/VescSetCustomApp "c46f4ff65abd5670780793173869e6b9")


