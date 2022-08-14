
(cl:in-package :asdf)

(defsystem "study_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "StudyMsg" :depends-on ("_package_StudyMsg"))
    (:file "_package_StudyMsg" :depends-on ("_package"))
  ))