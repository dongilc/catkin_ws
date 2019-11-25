
(cl:in-package :asdf)

(defsystem "amg_p1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "CTM_Message" :depends-on ("_package_CTM_Message"))
    (:file "_package_CTM_Message" :depends-on ("_package"))
    (:file "LA_Message" :depends-on ("_package_LA_Message"))
    (:file "_package_LA_Message" :depends-on ("_package"))
    (:file "MP_Message" :depends-on ("_package_MP_Message"))
    (:file "_package_MP_Message" :depends-on ("_package"))
  ))