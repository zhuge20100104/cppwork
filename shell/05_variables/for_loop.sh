#! /bin/bash
echo "first rnd of print skills..."
for skill in Ada Coffee Action Java
do 
    echo "I am good at ${skill}Script"
done

echo ""
echo ""
echo "second rnd of print skills..."
arr_skills=("Ada" "Coffee" "Action" "Java")
# 引用array的所有元素必须要这么写 ${arr_skills[@]}
for skill_1 in ${arr_skills[@]}
do 
    echo "I am also good at ${skill_1}Script"
done