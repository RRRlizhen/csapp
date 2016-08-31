#########################################################################
# File Name: test.sh
# Author: lizhen
# mail: lizhen_ok@163.com
# Created Time: Mon 25 Apr 2016 07:15:13 PM CST
#########################################################################
#!/bin/bash
read str1
IFS=,
str=($str1)

echo ${str[0]}
echo ${#str[*]}
exit 0
