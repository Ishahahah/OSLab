#!/bin/bash

echo "Enter a binary number: "
read binary

decimal=0
i=0

while [ $binary -ne 0 ]
do
    digit=$(( binary % 10 ))
    decimal=$(( decimal + digit * 2**i ))
    binary=$(( binary / 10 ))
    i=$(( i + 1 ))
done

echo "Decimal number is: $decimal"
