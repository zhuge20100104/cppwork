#! /bin/bash
echo "first rnd of print files..."
for file_n in `ls /etc`
do 
    echo $file_n
done

# echo "" 可以打印行 
echo ""
echo ""

echo "second rnd of print files..."
for file in $(ls /etc)
do
    echo $file
done 