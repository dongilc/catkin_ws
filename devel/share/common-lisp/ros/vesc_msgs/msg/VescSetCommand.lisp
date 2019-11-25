; Auto-generated. Do not edit!


(cl:in-package vesc_msgs-msg)


;//! \htmlinclude VescSetCommand.msg.html

(cl:defclass <VescSetCommand> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:float
    :initform 0.0)
   (send_can
    :reader send_can
    :initarg :send_can
    :type cl:boolean
    :initform cl:nil)
   (can_id
    :reader can_id
    :initarg :can_id
    :type cl:fixnum
    :initform 0))
)

(cl:defclass VescSetCommand (<VescSetCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VescSetCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VescSetCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vesc_msgs-msg:<VescSetCommand> is deprecated: use vesc_msgs-msg:VescSetCommand instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <VescSetCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:data-val is deprecated.  Use vesc_msgs-msg:data instead.")
  (data m))

(cl:ensure-generic-function 'send_can-val :lambda-list '(m))
(cl:defmethod send_can-val ((m <VescSetCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:send_can-val is deprecated.  Use vesc_msgs-msg:send_can instead.")
  (send_can m))

(cl:ensure-generic-function 'can_id-val :lambda-list '(m))
(cl:defmethod can_id-val ((m <VescSetCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:can_id-val is deprecated.  Use vesc_msgs-msg:can_id instead.")
  (can_id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VescSetCommand>) ostream)
  "Serializes a message object of type '<VescSetCommand>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'send_can) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'can_id)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VescSetCommand>) istream)
  "Deserializes a message object of type '<VescSetCommand>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'data) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:slot-value msg 'send_can) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'can_id)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VescSetCommand>)))
  "Returns string type for a message object of type '<VescSetCommand>"
  "vesc_msgs/VescSetCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VescSetCommand)))
  "Returns string type for a message object of type 'VescSetCommand"
  "vesc_msgs/VescSetCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VescSetCommand>)))
  "Returns md5sum for a message object of type '<VescSetCommand>"
  "9cffe44297165322576d6c2378fd0593")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VescSetCommand)))
  "Returns md5sum for a message object of type 'VescSetCommand"
  "9cffe44297165322576d6c2378fd0593")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VescSetCommand>)))
  "Returns full string definition for message of type '<VescSetCommand>"
  (cl:format cl:nil "float64 data~%bool  send_can~%uint8 can_id~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VescSetCommand)))
  "Returns full string definition for message of type 'VescSetCommand"
  (cl:format cl:nil "float64 data~%bool  send_can~%uint8 can_id~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VescSetCommand>))
  (cl:+ 0
     8
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VescSetCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'VescSetCommand
    (cl:cons ':data (data msg))
    (cl:cons ':send_can (send_can msg))
    (cl:cons ':can_id (can_id msg))
))
