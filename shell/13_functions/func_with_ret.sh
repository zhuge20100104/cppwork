#! /bin/bash

# Shell的变量都是全局的，外面不声明sum也可以
sum=0
func_sum() {
    echo "求两数之和"
    echo "输入第一个数字:"
    read num1
    echo "输入第二个数字:"
    read num2
    echo "两个数字分别为 ${num1} 和 ${num2}!"
    sum=`expr ${num1} + ${num2}`
}

func_sum
echo "输入的两个数字之和为: $sum"