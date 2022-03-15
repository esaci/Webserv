#!/bin/bash
cp type.cpp t1
cp ctype.cpp t2
rm _test_.cpp

for l in {1..79}
do
	echo -e $(sed '1!d' t1)","$(sed '1!d' t2) >> _test_.cpp
	sed -i '1d' t1
	sed -i '1d' t2
	echo $l
done
rm t1 t2