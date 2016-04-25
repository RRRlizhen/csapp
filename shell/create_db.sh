#########################################################################
# File Name: create_db.sh
# Author: lizhen
# mail: lizhen_ok@163.com
# Created Time: Mon 25 Apr 2016 04:48:18 PM CST
#########################################################################
#!/bin/bash
Username="root"
Password="lz123"

mysql -u $Username -p$Password <<EOF 2> /dev/null
create database students;
EOF

if [ $? -eq 0 ];
then
	echo Created DB
else
	echo DB already exist
fi

mysql -u $Username -p$Password students <<EOF 2> /dev/null
CREATE TABLE stu(
id int,
name varchar(100),
mark int,
dept varchar(4),
primary key(id)
);
EOF

[ $? -eq 0 ] && echo Created table students || echo Table students already exist

mysql -u $Username -p$Password students <<EOF 2> /dev/null
DELETE FROM stu;
EOF
echo "finished! ok"
