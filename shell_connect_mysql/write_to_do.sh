#########################################################################
# File Name: write_to_do.sh
# Author: lizhen
# mail: lizhen_ok@163.com
# Created Time: Mon 25 Apr 2016 05:14:13 PM CST
#########################################################################
#!/bin/bash
Username="root"
Password="lz123"

if [ $# -ne 1 ];
then
	echo "usage: $0 datafile"
	echo 
	exit 2;
fi

datafile=$1
while read line;
do
	oldIFS=$IFS
	IFS=,
	values=($line)
	values[1]="\"`echo ${values[1]} | tr ' ' '#' `\""
#	values[1]="\"`echo ${values[1]}`\""
	values[3]="\"`echo ${values[3]}`\""
	echo ${values[*]}--------2

#	query=`echo ${values[@]} | tr '#' ' ' `
	query=`echo ${values[@]} | tr ' '  ',' | tr '#' ' '`
	IFS=$oldIFS
	echo $query

	mysql -u $Username -p$Password students <<EOF 2> /dev/null
	INSERT INTO stu VALUES($query);
EOF
	[ $? -eq 0 ] && echo insert table stu 1 row || echo insert fail
done< $datafile
echo Wrote data into DB
