#! /bin/bash

func_with_param() {
    echo "第一个参数为: $1"
    echo "第二个参数为: $2"
    echo "参数总共有 $#个"
    echo "作为一个字符串输出所有参数: $*!"
}

func_with_param 1 2 3 4 5 6 7 8 9