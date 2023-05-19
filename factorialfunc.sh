#!/bin/bash

# find factorial using recurrence method
function factorial_recurrence {
    if [ $1 -eq 1 ]; then
        echo 1
    else
        echo $(( $1 * $(factorial_recurrence $(( $1 - 1 ))) ))
    fi
}

# prompt user to enter a number
echo "Enter a number:"
read num

# calculate factorial using recurrence method
result_recurrence=$(factorial_recurrence $num)

# print the result
echo "Factorial of $num using recurrence method is: $result_recurrence"
