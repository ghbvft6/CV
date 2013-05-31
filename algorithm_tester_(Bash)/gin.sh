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
if [ -z $1 ]; then #no gen_name passed
	echo "generator_name test_name \"input for the generator\" [amount_of_tests_to_create - default 1]"
	exit
fi
if [ -z $2 ]; then #no test_name passed
	echo "generator_name test_name \"input for the generator\" [amount_of_tests_to_create - default 1]"
	exit
fi
if [ -z $3 ]; then #no input passed
	echo "generator_name test_name \"input for the generator\" [amount_of_tests_to_create - default 1]"
	exit
fi
if [ -z $4 ]; then #no amount passed
	i=1
else
	i=$4
fi

########################################
#CONSTS
########################################
DIR=`pwd`
TMPDIR=$DIR
INFILE=$TMPDIR/gen_in.tmp
IODIR=$DIR/io #MUST MATCH BETWEEN [CHK GOUT GIN RUN]
GEN=$DIR/gen/$1
if [ ! -e $GEN ]; then
	echo "Generator not found!"
	exit
fi
TESTFOLDER=$IODIR/$2/$3

########################################
#CREATE INPUTS
########################################
echo $3 >> $INFILE
echo "[OVERWRITTEN]"
while [ $i -gt 0 ] ; do
	mkdir -p $TESTFOLDER/$i #creates path for the input file
	if [ -e $TESTFOLDER/$i/i ]; then
		echo $i
	fi
	$GEN < $INFILE > $TESTFOLDER/$i/i
	let "i -= 1"
done
rm -f $INFILE
