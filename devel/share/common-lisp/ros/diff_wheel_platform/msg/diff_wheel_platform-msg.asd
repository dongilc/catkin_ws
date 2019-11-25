
(cl:in-package :asdf)

(defsystem "diff_wheel_platform-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "CTM_Message" :depends-on ("_package_CTM_Message"))
    (:file "_package_CTM_Message" :depends-on ("_package"))
  ))