#!/bin/bash

VAR=200
ET=5

./philo $VAR 410 200 200 $ET > output.txt
for i in $(seq 1 $VAR); do
	OUT=$(cat output.txt | grep -e "[0-9]* $i is eating" | wc -l)
	if [[ $OUT -eq $ET ]]
	then
		echo "$i ate $ET times!"
	else
		echo "$i FAIL only ate $OUT times!"
	fi
done
