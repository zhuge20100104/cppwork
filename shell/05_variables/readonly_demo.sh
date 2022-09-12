#! /bin/bash

readonly url="http://www.baidu.com"
echo "Url is: ${url}"
# 此句发生错误，只读变量不能写
# url="http://www.google.com"

url1="http://www.google.com"
readonly url1 
echo "Url is: ${url1}"
# 此句发生错误，url1只读变量，不能写
# url1="http://www.facebook.com"
