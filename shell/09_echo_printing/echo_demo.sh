#! /bin/bash

# 显示普通字符串
echo "Hello World"
# 显示转义字符
echo "\"Hello World\""
# 显示变量
name="zhangsan"
echo "$name Hello World"
# 显示换行
# -e 允许解析反斜杠转义
echo -e "OK! \n"
echo "Hello World"

# 显示不换行
echo -e "OK! \c"
echo -n "OK! "

# 显示结果重定向到文件
echo "Hello World" > myfile.txt
# 原样输出字符串
echo '$name\"'
# 显示命令执行结果
echo `date`
echo `pwd`
