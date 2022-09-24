#! /bin/bash

a=10
b=20
if [ $a -eq $b ]; then
    echo "$a -eq $b a等于b"
else 
    echo "$a -eq $b a不等于b"
fi

if [ $a -ne $b ]; then
    echo "$a -ne $b a不等于b"
else
    echo "$a -ne $b a等于b"
fi 

if [ $a -gt $b ]; then
    echo "$a -gt $b a大于b"
else 
    echo "$a -gt $b a不大于b"
fi 

if [ $a -lt $b ]; then 
    echo "$a -lt $b a小于b"
else 
    echo "$a -lt $b a不小于b"
fi 

if [ $a -ge $b ]; then 
    echo "$a -ge $b a大于等于b"
else 
    echo "$a -ge $b a小于b"
fi 

if [ $a -le $b ]; then 
    echo "$a -le $b a小于等于b" 
else 
    echo "$a -le $b a大于b"
fi 



