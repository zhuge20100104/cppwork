; Auto-generated. Do not edit!


(cl:in-package study_msgs-msg)


;//! \htmlinclude StudyMsg.msg.html

(cl:defclass <StudyMsg> (roslisp-msg-protocol:ros-message)
  ((detail
    :reader detail
    :initarg :detail
    :type cl:string
    :initform "")
   (id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0))
)

(cl:defclass StudyMsg (<StudyMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StudyMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StudyMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name study_msgs-msg:<StudyMsg> is deprecated: use study_msgs-msg:StudyMsg instead.")))

(cl:ensure-generic-function 'detail-val :lambda-list '(m))
(cl:defmethod detail-val ((m <StudyMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader study_msgs-msg:detail-val is deprecated.  Use study_msgs-msg:detail instead.")
  (detail m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StudyMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader study_msgs-msg:id-val is deprecated.  Use study_msgs-msg:id instead.")
  (id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StudyMsg>) ostream)
  "Serializes a message object of type '<StudyMsg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'detail))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'detail))
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StudyMsg>) istream)
  "Deserializes a message object of type '<StudyMsg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'detail) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'detail) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StudyMsg>)))
  "Returns string type for a message object of type '<StudyMsg>"
  "study_msgs/StudyMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StudyMsg)))
  "Returns string type for a message object of type 'StudyMsg"
  "study_msgs/StudyMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StudyMsg>)))
  "Returns md5sum for a message object of type '<StudyMsg>"
  "7f5528a9204f8b31c9206fc97a4a07bb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StudyMsg)))
  "Returns md5sum for a message object of type 'StudyMsg"
  "7f5528a9204f8b31c9206fc97a4a07bb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StudyMsg>)))
  "Returns full string definition for message of type '<StudyMsg>"
  (cl:format cl:nil "string detail~%int32 id~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StudyMsg)))
  "Returns full string definition for message of type 'StudyMsg"
  (cl:format cl:nil "string detail~%int32 id~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StudyMsg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'detail))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StudyMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'StudyMsg
    (cl:cons ':detail (detail msg))
    (cl:cons ':id (id msg))
))
