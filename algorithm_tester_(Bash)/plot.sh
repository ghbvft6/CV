#!/bin/bash

#    Copyright (c) 2012 Grzegorz Chuchro <ghbvft6@gmail.com>
#    All rights reserved.

#    You are allowed to use, modify, copy, and share this program
#    for not commercial purposes only, provided that the above copyright notice
#    and this license appears in all copies of this program.
#    IN NO EVENT SHALL THE AUTHOR OF THIS PROGRAM BE LIABLE
#    FOR ANY FORM OF DAMAGE RESULTING FROM USING THIS PROGRAM.
#    THE AUTHOR DOES NOT PROVIDE ANY WARRANTY FOR THIS PROGRAM, including,
#    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

########################################
#ARGS
########################################
if [ -z $1 ]; then #no alg_name passed
	echo "algorithm_name test_name"
	exit
fi
if [ -z $2 ]; then #no alg_name passed
	echo "algorithm_name test_name"
	exit
fi

########################################
#CONSTS
########################################
DIR=`pwd`
STATDIR=$DIR/stat #MUST MATCH WITH CHK
TESTFOLDER=$STATDIR/$1/$2
DATDIR=$DIR/dat
STATSFILE=$DATDIR/_laststats.txt
mkdir -p $DATDIR
DATFILE=$DATDIR/$1_$2.dat

########################################
#CREATE DAT FILE
########################################
rm -f $STATSFILE
echo "[TYPE]"
for type in $TESTFOLDER/*; do
	echo ${type#$TESTFOLDER/}
	min_real=0
	sec_real=0.0
	mem_all=0
	mem_avg=0
	sec_usr=0.0
	sec_sys=0.0
	id_num=0
	cmps=0
	for id in $type/*; do
		let "id_num += 1"
		i=0
		while read arr[$i]; do
			let "i += 1"
		done < $id
		min_real=`echo $min_real + ${arr[0]%:*} | bc`
		sec_real=`echo $sec_real + ${arr[0]#*:} | bc`
		let "mem_all += arr[1]"
		let "mem_avg += arr[2]"
		sec_usr=`echo $sec_usr + ${arr[3]#*:} | bc`
		sec_sys=`echo $sec_sys + ${arr[4]#*:} | bc`
		let "cmps += arr[5]"
	done
	let "min_real *= 60"
	sec_real=`echo $sec_real + $min_real | bc`
	sec_real=`echo $sec_real / $id_num | bc -l`
	mem_all=`echo $mem_all / $id_num | bc -l`
	mem_avg=`echo $mem_avg / $id_num | bc -l`
	sec_usr=`echo $sec_usr / $id_num | bc -l`
	sec_sys=`echo $sec_sys / $id_num | bc -l`
	cmps=`echo $cmps / $id_num | bc -l`
	if [ -z ${sec_real%.*} ]; then sec_real=0$sec_real; #changes .1 to 0.1
	elif [ "$sec_real" == "0" ]; then sec_real=0.0 #changes 0 to 0.0
	fi
	if [ -z ${mem_max%.*} ]; then mem_max=0$mem_max;
	elif [ "$mem_max" == "0" ]; then mem_max=0.0
	fi
	if [ -z ${mem_avg%.*} ]; then mem_avg=0$mem_avg;
	elif [ "$mem_avg" == "0" ]; then mem_avg=0.0
	fi
	if [ -z ${sec_usr%.*} ]; then sec_usr=0$sec_usr;
	elif [ "$sec_usr" == "0" ]; then sec_usr=0.0
	fi
	if [ -z ${sec_sys%.*} ]; then sec_sys=0$sec_sys;
	elif [ "$sec_sys" == "0" ]; then sec_sys=0.0
	fi
	if [ -z ${cmps%.*} ]; then cmps=0$cmps;
	elif [ "$cmps" == "0" ]; then cmps=0.0
	fi
	echo "${type#$TESTFOLDER/} `expr match "$sec_real" '\([0-9]*...\)'` `expr match "$mem_all" '\([0-9]*...\)'` `expr match "$mem_avg" '\([0-9]*...\)'` `expr match "$sec_usr" '\([0-9]*...\)'` `expr match "$sec_sys" '\([0-9]*...\)'`" >> $STATSFILE
done
sort -n $STATSFILE > $DATFILE


########################################
#PLOT DAT FILE
########################################
echo "plot \"$DATFILE\" using 1:2 title 'STATS' with lines" | gnuplot -persist
