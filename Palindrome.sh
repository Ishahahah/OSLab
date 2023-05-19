#!/bin/bash

echo "Enter a Number:"
read n

temp=$n
reverse=0

while ((temp > 0))
do
   mod=$((temp%10))
   reverse=$((reverse*10 + mod))
   temp=$((temp/10))
done

if (($n == $reverse))
then
   echo "$n is a Palindrome Number"
else
   echo "$n is not a Palindrome Number"
fi
