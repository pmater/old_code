;; Auto-generated. Do not edit!


(when (boundp 'lms_package::lms_message)
  (if (not (find-package "LMS_PACKAGE"))
    (make-package "LMS_PACKAGE"))
  (shadow 'lms_message (find-package "LMS_PACKAGE")))
(unless (find-package "LMS_PACKAGE::LMS_MESSAGE")
  (make-package "LMS_PACKAGE::LMS_MESSAGE"))

(in-package "ROS")
;;//! \htmlinclude lms_message.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass lms_package::lms_message
  :super ros::object
  :slots (_header _angle_min _angle_max _angle_inc _time_inc _range_min _range_max _angles _ranges ))

(defmethod lms_package::lms_message
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:angle_min __angle_min) 0.0)
    ((:angle_max __angle_max) 0.0)
    ((:angle_inc __angle_inc) 0.0)
    ((:time_inc __time_inc) 0.0)
    ((:range_min __range_min) 0.0)
    ((:range_max __range_max) 0.0)
    ((:angles __angles) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:ranges __ranges) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _angle_min (float __angle_min))
   (setq _angle_max (float __angle_max))
   (setq _angle_inc (float __angle_inc))
   (setq _time_inc (float __time_inc))
   (setq _range_min (float __range_min))
   (setq _range_max (float __range_max))
   (setq _angles __angles)
   (setq _ranges __ranges)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:angle_min
   (&optional __angle_min)
   (if __angle_min (setq _angle_min __angle_min)) _angle_min)
  (:angle_max
   (&optional __angle_max)
   (if __angle_max (setq _angle_max __angle_max)) _angle_max)
  (:angle_inc
   (&optional __angle_inc)
   (if __angle_inc (setq _angle_inc __angle_inc)) _angle_inc)
  (:time_inc
   (&optional __time_inc)
   (if __time_inc (setq _time_inc __time_inc)) _time_inc)
  (:range_min
   (&optional __range_min)
   (if __range_min (setq _range_min __range_min)) _range_min)
  (:range_max
   (&optional __range_max)
   (if __range_max (setq _range_max __range_max)) _range_max)
  (:angles
   (&optional __angles)
   (if __angles (setq _angles __angles)) _angles)
  (:ranges
   (&optional __ranges)
   (if __ranges (setq _ranges __ranges)) _ranges)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _angle_min
    4
    ;; float32 _angle_max
    4
    ;; float32 _angle_inc
    4
    ;; float32 _time_inc
    4
    ;; float32 _range_min
    4
    ;; float32 _range_max
    4
    ;; float32[] _angles
    (* 4    (length _angles)) 4
    ;; float32[] _ranges
    (* 4    (length _ranges)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _angle_min
       (sys::poke _angle_min (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _angle_max
       (sys::poke _angle_max (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _angle_inc
       (sys::poke _angle_inc (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _time_inc
       (sys::poke _time_inc (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _range_min
       (sys::poke _range_min (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _range_max
       (sys::poke _range_max (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32[] _angles
     (write-long (length _angles) s)
     (dotimes (i (length _angles))
       (sys::poke (elt _angles i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _ranges
     (write-long (length _ranges) s)
     (dotimes (i (length _ranges))
       (sys::poke (elt _ranges i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _angle_min
     (setq _angle_min (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _angle_max
     (setq _angle_max (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _angle_inc
     (setq _angle_inc (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _time_inc
     (setq _time_inc (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _range_min
     (setq _range_min (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _range_max
     (setq _range_max (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32[] _angles
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angles (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _angles i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _ranges
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ranges (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _ranges i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get lms_package::lms_message :md5sum-) "dd7ebeab7b320dfe78d01b3e1ac4d506")
(setf (get lms_package::lms_message :datatype-) "lms_package/lms_message")
(setf (get lms_package::lms_message :definition-)
      "Header header
float32 angle_min
float32 angle_max
float32 angle_inc
float32 time_inc
float32 range_min
float32 range_max
float32[] angles
float32[] ranges

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :lms_package/lms_message "dd7ebeab7b320dfe78d01b3e1ac4d506")


