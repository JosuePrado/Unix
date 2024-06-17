#!/bin/bash

a=1
b=3

if [ $a -gt $b ]
then
    echo "Block If"
else
    echo "Block Else"
fi

if [ $a -lt $b ]; then
    echo "$a -lt $b"
elif [ $a -eq $b ]; then
    echo "$a -eq $b"
fi

if [[ a > b ]]
then 
    echo "$a is > $b"
else
    echo "$a is < $b"
fi

if [ ! $b -lt $a ]; then
    echo "negation"
else
    echo "without negation"
fi

if [ -d /etc/dpkg/dpkg.cfg ]; then
    echo "is a directory"
else 
    echo "is not a directory"
fi

if [ -f /etc/dpkg/dpkg.cfg ]; then
    echo "is a file"
else 
    echo "is not a file"
fi

#assignametn write a script that detects if it is a being executed as root
# print a message "you neet to run this script as root" if is not executed as root

if [ $UID -ne 0 ]; then
    echo "You need to run this script as root"
else
    echo "You are root"
fi


a=1
b=2
c=3
if [ $a -lt $b -a $c -gt $b ]
then
    echo "conditions true"
else
    echo "conditions false"
fi

i=0
while [ $i -le 10 ]
do 
    echo "count at $i"
    i=$(( i + 1))
    if [ $i -eq 5 ]; then 
        echo "counter is 5, next round"
        continue 
    fi
    echo "end of iteration"
done 

for j in 1 2 3 4 5 
do
    echo "j is: $j" 
done 

for k in {1..10}; do
    echo "k is: $k"
    if [ $k -eq 7 ]; then 
        echo "k is equails 7"
        break
    fi
done  