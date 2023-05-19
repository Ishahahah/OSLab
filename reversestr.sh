#!/bin/bash

# Prompt user to enter a string
echo "Please enter a string:"
read input_string

# Reverse the string using a for loop
reverse_string=""
for (( i=${#input_string}-1; i>=0; i-- )); do
  reverse_string="$reverse_string${input_string:$i:1}"
done

# Print the reversed string
echo "The reversed string is: $reverse_string"
