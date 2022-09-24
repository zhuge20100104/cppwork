#! /bin/bash
a="abc"
b="def"

if [ $a == $b ]; then
    echo "$a = $b: a等于b"
else 
    echo "$a = $b: a不等于b"
fi

if [ $a != $b ]; then 
    echo "$a != $b: a不等于b"
else 
    echo "$a != $b: a等于b"
fi 

if [ -z $a ]; then 
    echo "-z $a: 字符串长度为0"
else 
    echo "-z $a: 字符串长度不为0"
fi 

if [ -n $a ]; then 
    echo "-n $a: 字符串长度不为0"
else 
    echo "-n $a: 字符串长度为0"
fi 

if [ $a ]; then
    echo "$a: 字符串不为空"
else 
    echo "$a: 字符串为空"
fi 


