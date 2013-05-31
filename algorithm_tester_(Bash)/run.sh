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
IODIR=$DIR/io #MUST MATCH BETWEEN [CHK GOUT GIN RUN]
CFGDIR=$DIR/cfg
TESTSFILE=$CFGDIR/$1 #SHOULD MATCH WITH [CHK]
if [ ! -e $TESTSFILE ]; then
	mkdir -p $CFGDIR
	touch $TESTSFILE
fi
TESTS=`cat $TESTSFILE`
ALG=$DIR/alg/$1/$1 #SHOULD MATCH WITH [CHK]
if [ ! -e $ALG ]; then
	echo "Algorithm not found!"
	exit
fi

########################################
#RUN WITH SETS OF INPUTS
########################################
echo "[TESTS]"
if [ -z $2 ]; then #tests names not passed
	if [ -z "$TESTS" ]; then #default set of tests is blank
		for io in $IODIR/$1*; do
			echo ${io#$IODIR/}
			for type in $io/*; do
				for id in $type/*; do
					$ALG < $id/i > $id/o
				done
			done
		done
	else
		for io in $TESTS; do
			echo $io
			for type in $IODIR/$io/*; do
				for id in $type/*; do
					$ALG < $id/i > $id/o
				done
			done
		done
	fi
else
	for io in ${@:2}; do
		echo $io
		if [[ ! $TESTS =~ $io  ]]; then echo $io >> $TESTSFILE #adds tests to default list
		fi
		for type in $IODIR/$io/*; do
			for id in $type/*; do
				$ALG < $id/i > $id/o
			done
		done
	done
fi
