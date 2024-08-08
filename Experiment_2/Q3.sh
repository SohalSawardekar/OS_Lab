#!/bin/bash

echo "Enter a number: "
read number
digits=($(echo $number | grep -o . | sort -n))
unique_digits=($(echo "${digits[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' '))

if [ ${#unique_digits[@]} -lt 2 ]; then
echo "Not enough unique digits to find second smallest and second largest."
return
fi

second_smallest=${unique_digits[1]}
second_largest=${unique_digits[-2]}

echo "Second smallest digit: $second_smallest"
echo "Second largest digit: $second_largest"

sum=$((second_smallest + second_largest))
echo "Sum of second smallest and second largest digit: $sum"


