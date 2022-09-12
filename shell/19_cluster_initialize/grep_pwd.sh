#! /bin/bash
# NF: 一条记录的字段数目  1,2,3,4
# $NF就是最后一条 
grep "A temporary password" ./tmp_pwd | awk '{ print $NF}'