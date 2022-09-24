#! /bin/bash

while true
do 
    echo -n "请输入一个1-5之间的数字: "
    read num

    if [ $num -ne 3 ]; then 
        echo "你没有猜中数字...继续努力"
        # 这个continue 没什么用，因为后面没有别的语句了
        continue 
    else
        echo "你猜中了数字，恭喜你，中奖了5000万..."
        break
    fi  
done 