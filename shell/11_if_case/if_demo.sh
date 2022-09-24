#! /bin/bash

a=10
b=20

if [ $a == $b ]
then
    echo "${a}==${b}"
elif [ $a -gt $b ]
then  
    echo "${a} > ${b}"
elif [ $a -lt $b ] 
then 
    echo "${a} < ${b}"
else 
    echo "No matched conditions"
fi 