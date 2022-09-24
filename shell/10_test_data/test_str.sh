#! /bin/bash
s1="Hello"
s2="World"

if test $s1 = $s2 
then
    echo "${s1} == ${s2}"
else 
    echo "${s1} != ${s2}"
fi 

if test ${s1} != ${s2}
then
    echo "${s1} != ${s2}"
else 
    echo "${s1} == ${s2}"
fi 

if test -z $s1; then
    echo "${s1} is empty"
else 
    echo "${s1} is not empty"
fi 

if test -n $s1; then
    echo "${s1} is not empty"
else 
    echo "${s1} is empty"
fi 