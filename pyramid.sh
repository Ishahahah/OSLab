#!/bin/bash

# Prompt user to enter the number of rows
#echo "Please enter the number of rows:"
num_rows=5

# Loop through the rows
for (( i=1; i<=num_rows; i++ )); do
  # Print spaces for the current row
  for (( j=1; j<=num_rows-i; j++ )); do
    echo -n " "
  done
  # Print asterisks for the current row
  for (( j=1; j<=2*i-1; j++ )); do
    echo -n "*"
  done
  # Move to the next line
  echo ""
done
