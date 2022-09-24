#! /bin/bash
echo "请输入1到4之间的数字"
echo "您输入的数字为:"
read num

case $num in 
1)
    echo "您输入的数字是 1"
;;
2)
    echo "您输入的数字是 2"
;;
3)
    echo "您输入的数字是 3"
;;
4)
    echo "您输入的数字是 4"
;;
*)
    echo "您没有输入 1到4 之间的数字"
;;
esac