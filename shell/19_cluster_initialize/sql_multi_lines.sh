#! /bin/bash
mysql -u root -proot << EOF
show databases;
use test;
show tables;
select * from tb;
quit;
EOF

