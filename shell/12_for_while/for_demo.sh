#! /bin/bash

echo "Print ints..."
arr=(1 2 3 4 5)
for ele in ${arr[@]}
do
    echo "The value is ${ele}"
done 

IFS=$'\n'
echo "Print strs..."
strs=('This is a string' 'Hello moto')
for str in ${strs[@]}
do 
    echo "${str}"
done 
unset IFS