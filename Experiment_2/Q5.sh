#!/bin/bash

while true; do
    echo "Menu:"
    echo "1. Reverse a number"
    echo "2. Factorial of a number"
    echo "3. Fibonacci series"
    echo "4. Exit"
    echo "Enter your choice:"
    read choice

    case $choice in
        1)
	echo "Enter a number to reverse:"
    	read num
    	reverse=0
    	while [ $num -gt 0 ]; do
        	remainder=$((num % 10))
        	reverse=$((reverse * 10 + remainder))
        	num=$((num / 10))
    	done
    	echo "Reversed number: $reverse"
        	    ;;
        2)
	echo "Enter a number to calculate its factorial:"
    	read num
    	fact=1
    	for ((i = 1; i <= num; i++)); do
        	fact=$((fact * i))
    	done
    	echo "Factorial of $num is: $fact"
            ;;
        3)
	echo "Enter the number of terms:"
    	read terms
    	a=0
    	b=1
    	echo "Fibonacci series up to $terms terms:"
    	for ((i = 0; i < terms; i++)); do
        	echo -n "$a "
        	fib=$((a + b))
        	a=$b
        	b=$fib
    	done
    	echo ""
            ;;
        4)
            echo "Exiting the program."
            break
            ;;
        *)
            echo "Invalid choice. Please choose again."
            ;;
    esac
    echo ""
done

