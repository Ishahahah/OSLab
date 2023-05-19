#!/bin/bash

# Check if two arguments have been provided
if [ $# -ne 2 ]; then
    echo "Usage: ./script.sh <string> <substring>"
    exit 1
fi

string=$1
substring=$2

# Use grep to find all occurrences of the substring in the string
# -o flag is used to output only the matching parts
# wc -l is used to count the number of lines (i.e. occurrences)
count=$(echo "$string" | grep -o "$substring" | wc -l)

echo "The substring '$substring' occurs $count times in the string '$string'."
