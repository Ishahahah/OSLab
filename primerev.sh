#!/bin/bash

echo "Enter a number:"
read num

reverse=0
temp=$num

# Check if the number is prime or not
if [ $num -lt 2 ]; then
    echo "$num is not a prime number"
else
    for (( i=2; i<$num; i++ ))
    do
        if [ $(($num % $i)) -eq 0 ]; then
            echo "$num is not a prime number"
            exit
        fi
    done
    echo "$num is a prime number"
fi

# Reverse the number
while [ $temp -gt 0 ]
do
    remainder=$(( $temp % 10 ))
    reverse=$(( $reverse * 10 + $remainder ))
    temp=$(( $temp / 10 ))
done

echo "Reverse of $num is $reverse"
