#!/bin/sh

#for each number n, use a thread output it after sleep n seconds, all of the threads will start sleeping almost at the same time, and the thread present smaller number will wake up ealier and output the number


function sleep_sort {
	sleep "$1"
	echo "$1"
}

for val in "$@";do
	sleep_sort "$val" &
done

wait
