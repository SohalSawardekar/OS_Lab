#!/bin/bash

for i in {1..50}
do
  if [ $((i % 2)) -ne 0 ]
  then
    cube=$((i * i * i))
    echo "The cube of $i is $cube"
  fi
done

