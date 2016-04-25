#########################################################################
# File Name: read_db.sh
# Author: lizhen
# mail: lizhen_ok@163.com
# Created Time: Mon 25 Apr 2016 08:36:34 PM CST
#########################################################################
#!/bin/bash
Username="root"
Password="lz123"
depts=`mysql -u $Username -p$Password students <<EOF | tail -n+2
select distinct dept from stu;
EOF`

for d in $depts;
do
	echo Department : $d

	result="`mysql -u $Username -p$Password students <<EOF
	SET @i:=0;
	select @i:=@i+1 as rank,name,mark from stu where dept="$d" order by mark desc;
EOF`"

echo "$result"
echo
done
echo "select ok!"
