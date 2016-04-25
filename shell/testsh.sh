#########################################################################
# File Name: testsh.sh
# Author: lizhen
# mail: lizhen_ok@163.com
# Created Time: Mon 25 Apr 2016 05:32:34 PM CST
#########################################################################
#!/bin/bash
echo "is it morning? please answer yes or no"
read timeofday
if [ "$timeofday" = "yes" ]
then
	echo "good morning"
elif [ "$timeofday" = "no"  ]
then
	echo "good afternon"
else
	echo "xxxxx"
fi
##############
for foo in bar fud 43
do
	echo $foo
done
###############3
echo "enter password"
read trythis
while [ "$trythis" != "lz123" ];
do
	echo "sorry, try agin"
	read trythis
done
trythis="xx"
#######################
until [ "$trythis"="lz123"  ]
do
	echo "sorry,try agin"
	read trythis
done
##########
echo "do case"
read timeofday
case "$timeofday" in
	yes) echo "good";;
	no) echo "bad";;
	y) echo "good";;
	n) echo "bad";;
	*) echo "sorry,answer not recognized";;
esac


exit 0
