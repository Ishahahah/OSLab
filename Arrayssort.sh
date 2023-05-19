#!/bin/bash

# Accept user input for array
echo "Enter the elements of the array, separated by spaces:"
read -a arr

# Get the length of the array
n=${#arr[@]}

# Bubble sort algorithm
for ((i=0; i<$n-1; i++))
do
    for ((j=0; j<$n-i-1; j++))
    do
        if [ ${arr[j]} -gt ${arr[$((j+1))]} ]
        then
            # Swap the two elements
            temp=${arr[j]}
            arr[j]=${arr[$((j+1))]}
            arr[$((j+1))]=$temp
        fi
    done
done

# Print the sorted array
echo "Sorted array:"
for ((i=0; i<$n; i++))
do
    echo -n "${arr[$i]} "
done
echo ""
