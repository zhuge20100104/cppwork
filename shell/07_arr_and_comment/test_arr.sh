#! /bin/bash
# 定义数组，括号用来表示数组，数组中的元素用空格分隔开
favs=("足球" "篮球" "乒乓球" "保龄球")

# 读取数组， ${数组名[下标]}
fav=${favs[1]}
# 数组索引从0开始，应该输出 篮球
echo "第一个元素是: ${fav}"

# 使用@符号可以获取数组中的所有元素
echo ${favs[@]}
# 使用*符号也可以获取数组中的所有元素
echo ${favs[*]}

# 获取数组元素的长度
len1=${#favs[@]}
len2=${#favs[*]}

echo "获取数组元素个数的第一种方法: ${len1}"
echo "获取数组元素个数的第二种方法: ${len2}"

# 遍历数组中的所有元素
for fav in ${favs[@]}
do
    echo "当前元素: ${fav}" 
done
