num1=100
num2=50
if test $num1 -eq $num2 
then 
    echo "两个数相等"
else
    echo "两个数不相等"
fi


if test $num1 -ne $num2 
then 
    echo "${num1} != ${num2}"
else 
    echo "${num1} == ${num2}"
fi 

if test $num1 -gt $num2 
then
    echo "${num1} > ${num2}"
else 
    echo "${num1} <= ${num2}"
fi 

if test $num1 -ge $num2
then
    echo "${num1} >= ${num2}"
else 
    echo "${num1} < ${num2}"
fi 

if test $num1 -lt $num2 
then
    echo "${num1} < ${num2}"
else 
    echo "${num1} >= ${num2}"
fi 

if test $num1 -le $num2 
then
    echo "${num1} <= ${num2}"
else 
    echo "${num1} > ${num2}"
fi 

