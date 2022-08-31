;; Auto-generated. Do not edit!


(when (boundp 'person_msg::Person)
  (if (not (find-package "PERSON_MSG"))
    (make-package "PERSON_MSG"))
  (shadow 'Person (find-package "PERSON_MSG")))
(unless (find-package "PERSON_MSG::PERSON")
  (make-package "PERSON_MSG::PERSON"))

(in-package "ROS")
;;//! \htmlinclude Person.msg.html


(defclass person_msg::Person
  :super ros::object
  :slots (_name _age _height ))

(defmethod person_msg::Person
  (:init
   (&key
    ((:name __name) "")
    ((:age __age) 0)
    ((:height __height) 0.0)
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _age (round __age))
   (setq _height (float __height))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:age
   (&optional __age)
   (if __age (setq _age __age)) _age)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; uint16 _age
    2
    ;; float64 _height
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; uint16 _age
       (write-word _age s)
     ;; float64 _height
       (sys::poke _height (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint16 _age
     (setq _age (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float64 _height
     (setq _height (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get person_msg::Person :md5sum-) "81ccf2097ef38ca6466e5a60ea1f8e49")
(setf (get person_msg::Person :datatype-) "person_msg/Person")
(setf (get person_msg::Person :definition-)
      "string name
uint16 age
float64 height
")



(provide :person_msg/Person "81ccf2097ef38ca6466e5a60ea1f8e49")


