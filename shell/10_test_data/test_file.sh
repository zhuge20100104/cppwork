#! /bin/bash
file="/home/fredric/code/cppwork/shell/10_test_data/test_str.sh"

if test -e ${file}
then
    echo "${file} exists"
else
    echo "${file} does not exist"
fi 

if test -r ${file}
then
    echo "${file} is a readable file"
else 
    echo "${file} is not a readable file"
fi 

if test -w ${file}
then
    echo "${file} is a writable file"
else 
    echo "${file} is not a writable file"
fi 

if test -x ${file} 
then
    echo "${file} is an executable file"
else 
    echo "${file} is not an execuable file"
fi 

if test -s ${file}
then
    echo "${file} has content"
else 
    echo "${file} doesn't have content"
fi 


if test -d ${file}
then
    echo "${file} is a directory"
else 
    echo "${file} is not a directory"
fi 

if test -f ${file}
then
    echo "${file} is a common file"
else 
    echo "${file} is not a common file"
fi 