; Auto-generated. Do not edit!


(cl:in-package vesc_msgs-msg)


;//! \htmlinclude VescSetCustomApp.msg.html

(cl:defclass <VescSetCustomApp> (roslisp-msg-protocol:ros-message)
  ((num_of_id
    :reader num_of_id
    :initarg :num_of_id
    :type cl:integer
    :initform 0)
   (id_set
    :reader id_set
    :initarg :id_set
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (comm_set
    :reader comm_set
    :initarg :comm_set
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (can_forward_set
    :reader can_forward_set
    :initarg :can_forward_set
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil))
   (value_set
    :reader value_set
    :initarg :value_set
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (data_bytes
    :reader data_bytes
    :initarg :data_bytes
    :type cl:integer
    :initform 0))
)

(cl:defclass VescSetCustomApp (<VescSetCustomApp>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VescSetCustomApp>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VescSetCustomApp)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vesc_msgs-msg:<VescSetCustomApp> is deprecated: use vesc_msgs-msg:VescSetCustomApp instead.")))

(cl:ensure-generic-function 'num_of_id-val :lambda-list '(m))
(cl:defmethod num_of_id-val ((m <VescSetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:num_of_id-val is deprecated.  Use vesc_msgs-msg:num_of_id instead.")
  (num_of_id m))

(cl:ensure-generic-function 'id_set-val :lambda-list '(m))
(cl:defmethod id_set-val ((m <VescSetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:id_set-val is deprecated.  Use vesc_msgs-msg:id_set instead.")
  (id_set m))

(cl:ensure-generic-function 'comm_set-val :lambda-list '(m))
(cl:defmethod comm_set-val ((m <VescSetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:comm_set-val is deprecated.  Use vesc_msgs-msg:comm_set instead.")
  (comm_set m))

(cl:ensure-generic-function 'can_forward_set-val :lambda-list '(m))
(cl:defmethod can_forward_set-val ((m <VescSetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:can_forward_set-val is deprecated.  Use vesc_msgs-msg:can_forward_set instead.")
  (can_forward_set m))

(cl:ensure-generic-function 'value_set-val :lambda-list '(m))
(cl:defmethod value_set-val ((m <VescSetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:value_set-val is deprecated.  Use vesc_msgs-msg:value_set instead.")
  (value_set m))

(cl:ensure-generic-function 'data_bytes-val :lambda-list '(m))
(cl:defmethod data_bytes-val ((m <VescSetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:data_bytes-val is deprecated.  Use vesc_msgs-msg:data_bytes instead.")
  (data_bytes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VescSetCustomApp>) ostream)
  "Serializes a message object of type '<VescSetCustomApp>"
  (cl:let* ((signed (cl:slot-value msg 'num_of_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'id_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'id_set))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'comm_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'comm_set))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'can_forward_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'can_forward_set))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'value_set))))
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
   (cl:slot-value msg 'value_set))
  (cl:let* ((signed (cl:slot-value msg 'data_bytes)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VescSetCustomApp>) istream)
  "Deserializes a message object of type '<VescSetCustomApp>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num_of_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'id_set) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'id_set)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'comm_set) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'comm_set)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'can_forward_set) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'can_forward_set)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'value_set) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'value_set)))
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
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data_bytes) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VescSetCustomApp>)))
  "Returns string type for a message object of type '<VescSetCustomApp>"
  "vesc_msgs/VescSetCustomApp")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VescSetCustomApp)))
  "Returns string type for a message object of type 'VescSetCustomApp"
  "vesc_msgs/VescSetCustomApp")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VescSetCustomApp>)))
  "Returns md5sum for a message object of type '<VescSetCustomApp>"
  "c46f4ff65abd5670780793173869e6b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VescSetCustomApp)))
  "Returns md5sum for a message object of type 'VescSetCustomApp"
  "c46f4ff65abd5670780793173869e6b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VescSetCustomApp>)))
  "Returns full string definition for message of type '<VescSetCustomApp>"
  (cl:format cl:nil "# VESCuino CDI CUSTOM_APP TX Messages~%~%int32       num_of_id~%int32[]     id_set~%int32[]     comm_set~%bool[]      can_forward_set~%float64[]   value_set~%int32       data_bytes~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VescSetCustomApp)))
  "Returns full string definition for message of type 'VescSetCustomApp"
  (cl:format cl:nil "# VESCuino CDI CUSTOM_APP TX Messages~%~%int32       num_of_id~%int32[]     id_set~%int32[]     comm_set~%bool[]      can_forward_set~%float64[]   value_set~%int32       data_bytes~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VescSetCustomApp>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'id_set) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'comm_set) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'can_forward_set) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'value_set) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VescSetCustomApp>))
  "Converts a ROS message object to a list"
  (cl:list 'VescSetCustomApp
    (cl:cons ':num_of_id (num_of_id msg))
    (cl:cons ':id_set (id_set msg))
    (cl:cons ':comm_set (comm_set msg))
    (cl:cons ':can_forward_set (can_forward_set msg))
    (cl:cons ':value_set (value_set msg))
    (cl:cons ':data_bytes (data_bytes msg))
))
