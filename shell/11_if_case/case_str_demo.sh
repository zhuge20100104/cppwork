#! /bin/bash

echo "请输入一个字符串[A/B/C/D/E]: "
read str

case $str in
A)
    echo "您输入了字母A"
;;
B)
    echo "您输入了字母B"
;;
C)
    echo "您输入了字母C"
;;
D)
    echo "您输入了字母D"
;;
E)
    echo "您输入了字母E"
;;
*)
    echo "您没有输入A-E之间的字母"
;;
esac