echo "Enter 1st no: "
read a
echo "Enter 2nd no: "
read b
echo "Enter 3rd no: "
read c

if [ $a -gt $b ]
then 
	if [ $a -gt $c ]
	then 
		echo "$a is greatest"
	else 
		echo "$c is greatest"
	fi 
else 
	if [ $b -gt $c ]
	then 
		echo "$b is greatest"
	else 
		echo "$c is greatest"
	fi
fi




