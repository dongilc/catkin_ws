; Auto-generated. Do not edit!


(cl:in-package amg_p1-msg)


;//! \htmlinclude LA_Message.msg.html

(cl:defclass <LA_Message> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (deg_total_target
    :reader deg_total_target
    :initarg :deg_total_target
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (deg_total_now
    :reader deg_total_now
    :initarg :deg_total_now
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass LA_Message (<LA_Message>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LA_Message>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LA_Message)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name amg_p1-msg:<LA_Message> is deprecated: use amg_p1-msg:LA_Message instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <LA_Message>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader amg_p1-msg:stamp-val is deprecated.  Use amg_p1-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'deg_total_target-val :lambda-list '(m))
(cl:defmethod deg_total_target-val ((m <LA_Message>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader amg_p1-msg:deg_total_target-val is deprecated.  Use amg_p1-msg:deg_total_target instead.")
  (deg_total_target m))

(cl:ensure-generic-function 'deg_total_now-val :lambda-list '(m))
(cl:defmethod deg_total_now-val ((m <LA_Message>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader amg_p1-msg:deg_total_now-val is deprecated.  Use amg_p1-msg:deg_total_now instead.")
  (deg_total_now m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LA_Message>) ostream)
  "Serializes a message object of type '<LA_Message>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'deg_total_target))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'deg_total_target))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'deg_total_now))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'deg_total_now))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LA_Message>) istream)
  "Deserializes a message object of type '<LA_Message>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'deg_total_target) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'deg_total_target)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'deg_total_now) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'deg_total_now)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LA_Message>)))
  "Returns string type for a message object of type '<LA_Message>"
  "amg_p1/LA_Message")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LA_Message)))
  "Returns string type for a message object of type 'LA_Message"
  "amg_p1/LA_Message")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LA_Message>)))
  "Returns md5sum for a message object of type '<LA_Message>"
  "7905fa336d4f2fe4db8c49c8192c0986")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LA_Message)))
  "Returns md5sum for a message object of type 'LA_Message"
  "7905fa336d4f2fe4db8c49c8192c0986")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LA_Message>)))
  "Returns full string definition for message of type '<LA_Message>"
  (cl:format cl:nil "time stamp~%~%float64[] deg_total_target~%float64[] deg_total_now~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LA_Message)))
  "Returns full string definition for message of type 'LA_Message"
  (cl:format cl:nil "time stamp~%~%float64[] deg_total_target~%float64[] deg_total_now~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LA_Message>))
  (cl:+ 0
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'deg_total_target) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'deg_total_now) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LA_Message>))
  "Converts a ROS message object to a list"
  (cl:list 'LA_Message
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':deg_total_target (deg_total_target msg))
    (cl:cons ':deg_total_now (deg_total_now msg))
))
