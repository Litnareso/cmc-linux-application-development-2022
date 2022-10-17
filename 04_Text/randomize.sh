#!/bin/sh

y=0
delay="0.03"
if [ "$#" -eq 1 ]; then
    delay=$1
fi

clear
tr ' ' '\01' | \
while read str ; do
    x=0
    for i in $(echo $str | od -v -t x1 -A n); do
        if [ "$i" != "01" ]; then
            echo $i $x $y
        fi
        x=$((x+1))
    done
    y=$((y+1))
done | \
shuf | \
while read code x y ; do
    tput cup $y $x
    echo -ne "\x$code"
    sleep $delay
done

tput cup $(tput lines) $x
