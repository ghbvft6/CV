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
	echo "algorithm_name [test_names - default reads from ./cfg/alg_name if empty reads ]"
	exit
fi

########################################
#CONSTS
########################################
DIR=`pwd`
TMPDIR=$DIR
OUTFILE=$TMPDIR/_OUTFILE.tmp
ERRORSFILE=$TMPDIR/errors.txt
IODIR=$DIR/io #MUST MATCH BETWEEN [CHK GOUT GIN RUN]
STATDIR=$DIR/stat
CFGDIR=$DIR/cfg
TESTSFILE=$CFGDIR/$1 #SHOULD MATCH WITH [RUN]
if [ ! -e $TESTSFILE ]; then
	mkdir -p $CFGDIR
	touch $TESTSFILE
fi
TESTS=`cat $TESTSFILE`
ALG=$DIR/alg/$1/$1 #SHOULD MATCH WITH [RUN]
if [ ! -e $ALG ]; then
	echo "Algorithm not found!"
	exit
fi

########################################
#VARS
########################################
min_real=0
sec_real=0.0
mem_all=0
mem_avg=0
sec_usr=0.0
sec_sys=0.0


########################################
function alg_chk(){
########################################
	#0. real time in m:s
	#1. maximum memory in KB
	#2. average memory in KB
	#3. user time in secs
	#4. system time in secs
	/usr/bin/time -o $STATDIR/$1${id#$IODIR} -f "%E\n%M\n%t\n%U\n%S" $ALG < $id/i > $OUTFILE
	i=0
	while read arr[$i]; do
		let "i += 1"
	done < $STATDIR/$1${id#$IODIR}
	#read -r cmps < $DIR/file.txt
	#echo $cmps >> $STATDIR/$1${id#$IODIR}
	min_real=`echo $min_real + ${arr[0]%:*} | bc`
	sec_real=`echo $sec_real + ${arr[0]#*:} | bc`
	let "mem_all += arr[1]"
	let "mem_avg += arr[2]"
	sec_usr=`echo $sec_usr + ${arr[3]#*:} | bc`
	sec_sys=`echo $sec_sys + ${arr[4]#*:} | bc`
	if ! diff $id/o $OUTFILE > /dev/null;  then echo "${id#$IODIR/}" >> $ERRORSFILE
	fi
}

########################################
#CHECK SETS OF INPUTS
########################################
rm -f $ERRORSFILE
echo "[TESTS]"
if [ -z $2 ]; then #tests names not passed
	if [ -z "$TESTS" ]; then #default set of tests is blank
		for io in $IODIR/$1*; do
			echo ${io#$IODIR/}
			for type in $io/*; do
				mkdir -p $STATDIR/$1${type#$IODIR} #creates path for [time -o]
				for id in $type/*; do
					alg_chk $1
				done
			done
		done
	else
		for io in $TESTS; do
			echo $io
			for type in $IODIR/$io/*; do
				mkdir -p $STATDIR/$1${type#$IODIR} #creates path for [time -o]
				for id in $type/*; do
					alg_chk $1
				done
			done
		done
	fi
else
	for io in ${@:2}; do
		if [[ ! $TESTS =~ $io  ]]; then echo $io >> $TESTSFILE #adds tests to default list
		fi
		for type in $IODIR/$io/*; do
			mkdir -p $STATDIR/$1${type#$IODIR} #creates path for [time -o]
			for id in $type/*; do
				alg_chk $1
			done
		done
	done
fi
#rm -f $OUTFILE

########################################
#ERRORS
########################################
if [ -e $ERRORSFILE ]; then
	echo "
[ERROS]"
	cat $ERRORSFILE
fi

########################################
#STATS
########################################
if [ -z ${sec_real%.*} ]; then sec_real=0$sec_real; #changes .1 to 0.1
fi
if [ -z ${sec_usr%.*} ]; then sec_usr=0$sec_usr;
fi
if [ -z ${sec_sys%.*} ]; then sec_sys=0$sec_sys;
fi
echo "
[STATS]
real: $min_real""m"" $sec_real""s""
all:  $mem_all""KB""
	avg: $mem_avg""KB""
	usr: $sec_usr""s""
	sys: $sec_sys""s"
