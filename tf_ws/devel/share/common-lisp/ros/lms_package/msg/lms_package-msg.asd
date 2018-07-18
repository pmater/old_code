
(cl:in-package :asdf)

(defsystem "lms_package-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "lms_message" :depends-on ("_package_lms_message"))
    (:file "_package_lms_message" :depends-on ("_package"))
  ))