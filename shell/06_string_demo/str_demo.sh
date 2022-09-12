#! /bin/bash
# 声明字符串，有空格的字符串必须用引号括起来
str1="hello world1"
str2="hello world2"
echo "str1: ${str1}" 
echo "str2: ${str2}"

# 字符串拼接，双引号，会做转义处理
name='sunwukong'
name1="hello"${name}" !"
name2="hello ${name} !"
echo $name1 
echo $name2 

# 字符串拼接，单引号
passwd='123456'
passwd1='hello, '$passwd' !'
passwd2='hello, $passwd'
echo ${passwd1}
echo ${passwd2}

# 求字符串的长度和substring
email="123456@qq.com"
echo "Length of email: ${#email}"
echo "substring of email ${email:0:6}"
echo "Get the 7th to the end: ${email:7}"

# 求字符串里面的indexof，类似于python的find
at_idx=`expr index ${email} '@'`
echo "Get the suffix of the email: ${email:at_idx}"