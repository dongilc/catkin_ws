; Auto-generated. Do not edit!


(cl:in-package vesc_msgs-msg)


;//! \htmlinclude VescGetCustomApp.msg.html

(cl:defclass <VescGetCustomApp> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (send_mode_index1
    :reader send_mode_index1
    :initarg :send_mode_index1
    :type cl:integer
    :initform 0)
   (fw_ver_major
    :reader fw_ver_major
    :initarg :fw_ver_major
    :type cl:integer
    :initform 0)
   (fw_ver_minor
    :reader fw_ver_minor
    :initarg :fw_ver_minor
    :type cl:integer
    :initform 0)
   (fault_code
    :reader fault_code
    :initarg :fault_code
    :type cl:integer
    :initform 0)
   (app_status_code
    :reader app_status_code
    :initarg :app_status_code
    :type cl:integer
    :initform 0)
   (send_mode_index2
    :reader send_mode_index2
    :initarg :send_mode_index2
    :type cl:integer
    :initform 0)
   (can_devs_num
    :reader can_devs_num
    :initarg :can_devs_num
    :type cl:integer
    :initform 0)
   (can_id
    :reader can_id
    :initarg :can_id
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (custom_status
    :reader custom_status
    :initarg :custom_status
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (enc_rps
    :reader enc_rps
    :initarg :enc_rps
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (enc_rad
    :reader enc_rad
    :initarg :enc_rad
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (current
    :reader current
    :initarg :current
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (duty
    :reader duty
    :initarg :duty
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass VescGetCustomApp (<VescGetCustomApp>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VescGetCustomApp>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VescGetCustomApp)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vesc_msgs-msg:<VescGetCustomApp> is deprecated: use vesc_msgs-msg:VescGetCustomApp instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:header-val is deprecated.  Use vesc_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'send_mode_index1-val :lambda-list '(m))
(cl:defmethod send_mode_index1-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:send_mode_index1-val is deprecated.  Use vesc_msgs-msg:send_mode_index1 instead.")
  (send_mode_index1 m))

(cl:ensure-generic-function 'fw_ver_major-val :lambda-list '(m))
(cl:defmethod fw_ver_major-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:fw_ver_major-val is deprecated.  Use vesc_msgs-msg:fw_ver_major instead.")
  (fw_ver_major m))

(cl:ensure-generic-function 'fw_ver_minor-val :lambda-list '(m))
(cl:defmethod fw_ver_minor-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:fw_ver_minor-val is deprecated.  Use vesc_msgs-msg:fw_ver_minor instead.")
  (fw_ver_minor m))

(cl:ensure-generic-function 'fault_code-val :lambda-list '(m))
(cl:defmethod fault_code-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:fault_code-val is deprecated.  Use vesc_msgs-msg:fault_code instead.")
  (fault_code m))

(cl:ensure-generic-function 'app_status_code-val :lambda-list '(m))
(cl:defmethod app_status_code-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:app_status_code-val is deprecated.  Use vesc_msgs-msg:app_status_code instead.")
  (app_status_code m))

(cl:ensure-generic-function 'send_mode_index2-val :lambda-list '(m))
(cl:defmethod send_mode_index2-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:send_mode_index2-val is deprecated.  Use vesc_msgs-msg:send_mode_index2 instead.")
  (send_mode_index2 m))

(cl:ensure-generic-function 'can_devs_num-val :lambda-list '(m))
(cl:defmethod can_devs_num-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:can_devs_num-val is deprecated.  Use vesc_msgs-msg:can_devs_num instead.")
  (can_devs_num m))

(cl:ensure-generic-function 'can_id-val :lambda-list '(m))
(cl:defmethod can_id-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:can_id-val is deprecated.  Use vesc_msgs-msg:can_id instead.")
  (can_id m))

(cl:ensure-generic-function 'custom_status-val :lambda-list '(m))
(cl:defmethod custom_status-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:custom_status-val is deprecated.  Use vesc_msgs-msg:custom_status instead.")
  (custom_status m))

(cl:ensure-generic-function 'enc_rps-val :lambda-list '(m))
(cl:defmethod enc_rps-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:enc_rps-val is deprecated.  Use vesc_msgs-msg:enc_rps instead.")
  (enc_rps m))

(cl:ensure-generic-function 'enc_rad-val :lambda-list '(m))
(cl:defmethod enc_rad-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:enc_rad-val is deprecated.  Use vesc_msgs-msg:enc_rad instead.")
  (enc_rad m))

(cl:ensure-generic-function 'current-val :lambda-list '(m))
(cl:defmethod current-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:current-val is deprecated.  Use vesc_msgs-msg:current instead.")
  (current m))

(cl:ensure-generic-function 'duty-val :lambda-list '(m))
(cl:defmethod duty-val ((m <VescGetCustomApp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vesc_msgs-msg:duty-val is deprecated.  Use vesc_msgs-msg:duty instead.")
  (duty m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VescGetCustomApp>) ostream)
  "Serializes a message object of type '<VescGetCustomApp>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'send_mode_index1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'fw_ver_major)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'fw_ver_minor)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'fault_code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'app_status_code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'send_mode_index2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'can_devs_num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'can_id))))
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
   (cl:slot-value msg 'can_id))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'custom_status))))
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
   (cl:slot-value msg 'custom_status))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'enc_rps))))
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
   (cl:slot-value msg 'enc_rps))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'enc_rad))))
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
   (cl:slot-value msg 'enc_rad))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'current))))
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
   (cl:slot-value msg 'current))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'duty))))
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
   (cl:slot-value msg 'duty))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VescGetCustomApp>) istream)
  "Deserializes a message object of type '<VescGetCustomApp>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'send_mode_index1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'fw_ver_major) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'fw_ver_minor) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'fault_code) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'app_status_code) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'send_mode_index2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'can_devs_num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'can_id) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'can_id)))
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
  (cl:setf (cl:slot-value msg 'custom_status) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'custom_status)))
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
  (cl:setf (cl:slot-value msg 'enc_rps) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'enc_rps)))
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
  (cl:setf (cl:slot-value msg 'enc_rad) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'enc_rad)))
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
  (cl:setf (cl:slot-value msg 'current) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'current)))
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
  (cl:setf (cl:slot-value msg 'duty) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'duty)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VescGetCustomApp>)))
  "Returns string type for a message object of type '<VescGetCustomApp>"
  "vesc_msgs/VescGetCustomApp")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VescGetCustomApp)))
  "Returns string type for a message object of type 'VescGetCustomApp"
  "vesc_msgs/VescGetCustomApp")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VescGetCustomApp>)))
  "Returns md5sum for a message object of type '<VescGetCustomApp>"
  "daa4967cc5ef43655bd186c327b3176d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VescGetCustomApp)))
  "Returns md5sum for a message object of type 'VescGetCustomApp"
  "daa4967cc5ef43655bd186c327b3176d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VescGetCustomApp>)))
  "Returns full string definition for message of type '<VescGetCustomApp>"
  (cl:format cl:nil "# VESCuino CDI CUSTOM_APP RX Messages~%~%Header  header~%~%# FW Version Data~%int32 send_mode_index1~%int32 fw_ver_major~%int32 fw_ver_minor~%~%# Original Get Value Data~%#float64 voltage_input        # input voltage (volt)~%#float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)~%#float64 current_motor        # motor current (ampere)~%#float64 current_input        # input current (ampere)~%#float64 speed                # motor electrical speed (revolutions per minute) ~%#float64 duty_cycle           # duty cycle (0 to 1)~%#float64 charge_drawn         # electric charge drawn from input (ampere-hour)~%#float64 charge_regen         # electric charge regenerated to input (ampere-hour)~%#float64 energy_drawn         # energy drawn from input (watt-hour)~%#float64 energy_regen         # energy regenerated to input (watt-hour)~%#float64 displacement         # net tachometer (counts)~%#float64 distance_traveled    # total tachnometer (counts)~%int32   fault_code~%#float64 pid_pos_now    		 # pid position now (deg) 0~~360~%~%int32 app_status_code        # application status code~%~%# CAN Status Data ~%int32 send_mode_index2~%int32 can_devs_num~%int32[] can_id~%int32[] custom_status~%~%# Raw Encoder Data~%float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) ~%float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)~%float64[] current			 # can status - current~%float64[] duty			     # can status - duty~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VescGetCustomApp)))
  "Returns full string definition for message of type 'VescGetCustomApp"
  (cl:format cl:nil "# VESCuino CDI CUSTOM_APP RX Messages~%~%Header  header~%~%# FW Version Data~%int32 send_mode_index1~%int32 fw_ver_major~%int32 fw_ver_minor~%~%# Original Get Value Data~%#float64 voltage_input        # input voltage (volt)~%#float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)~%#float64 current_motor        # motor current (ampere)~%#float64 current_input        # input current (ampere)~%#float64 speed                # motor electrical speed (revolutions per minute) ~%#float64 duty_cycle           # duty cycle (0 to 1)~%#float64 charge_drawn         # electric charge drawn from input (ampere-hour)~%#float64 charge_regen         # electric charge regenerated to input (ampere-hour)~%#float64 energy_drawn         # energy drawn from input (watt-hour)~%#float64 energy_regen         # energy regenerated to input (watt-hour)~%#float64 displacement         # net tachometer (counts)~%#float64 distance_traveled    # total tachnometer (counts)~%int32   fault_code~%#float64 pid_pos_now    		 # pid position now (deg) 0~~360~%~%int32 app_status_code        # application status code~%~%# CAN Status Data ~%int32 send_mode_index2~%int32 can_devs_num~%int32[] can_id~%int32[] custom_status~%~%# Raw Encoder Data~%float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) ~%float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)~%float64[] current			 # can status - current~%float64[] duty			     # can status - duty~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VescGetCustomApp>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'can_id) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'custom_status) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'enc_rps) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'enc_rad) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'current) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'duty) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VescGetCustomApp>))
  "Converts a ROS message object to a list"
  (cl:list 'VescGetCustomApp
    (cl:cons ':header (header msg))
    (cl:cons ':send_mode_index1 (send_mode_index1 msg))
    (cl:cons ':fw_ver_major (fw_ver_major msg))
    (cl:cons ':fw_ver_minor (fw_ver_minor msg))
    (cl:cons ':fault_code (fault_code msg))
    (cl:cons ':app_status_code (app_status_code msg))
    (cl:cons ':send_mode_index2 (send_mode_index2 msg))
    (cl:cons ':can_devs_num (can_devs_num msg))
    (cl:cons ':can_id (can_id msg))
    (cl:cons ':custom_status (custom_status msg))
    (cl:cons ':enc_rps (enc_rps msg))
    (cl:cons ':enc_rad (enc_rad msg))
    (cl:cons ':current (current msg))
    (cl:cons ':duty (duty msg))
))
