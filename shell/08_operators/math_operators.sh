#! /bin/bash
a=10
b=20
# expr 是一款表达式计算工具，使用它能完成表达式的求值工作
val=`expr $a + $b`
echo "a + b: ${val}"

val=`expr $a - $b`
echo "a - b: ${val}"

val=`expr $a \* $b`
echo "a * b: ${val}"

val=`expr $b / $a`
echo "b / a: ${val}"

val=`expr $b % $a`
echo "b % a: ${val}"

if [ $a == $b ]
then
    echo "a等于b" 
fi

if [ $a != $b ]
then
    echo "a不等于b"
fi