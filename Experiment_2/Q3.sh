echo "Enter a number: "
read num

temp=$num
temp1=$num
min=9
max=0

while [ $temp -ne 0 ]
do
    dig=$(($temp%10))
    if [ $dig -le $min ]
    then
        min=$dig
    fi
    if [ $dig -gt $max ]
    then
        max=$dig
    fi
    temp=$(($temp/10))
done

temp=$num;
smin=9
smax=0

while [ $temp -ne 0 ]
do
    dig=$(($temp%10))
    if [ $dig -ne $min ] && [ $dig -le $smin ]
    then
        smin=$dig
    fi
    temp=$(($temp/10))
done

while [ $temp1 -ne 0 ]
do
    dig=$(($temp1%10))
    if [ $dig -ne $max ] && [ $dig -ge $smax ]
    then
        smax=$dig
    fi
    temp1=$(($temp1/10))
done

echo "Second minimum is: $smin"
echo "Second maximum is: $smax"
sum=$(($smax+$smin))
echo "The sum is: $sum"