
(cl:in-package :asdf)

(defsystem "gps_package-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "gps_message" :depends-on ("_package_gps_message"))
    (:file "_package_gps_message" :depends-on ("_package"))
  ))