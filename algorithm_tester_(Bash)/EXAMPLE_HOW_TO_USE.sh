#!/bin/bash

echo "

Generate some tests:
"
./gin.sh first_gen test_name 1 100
./gin.sh first_gen test_name2 10
./gin.sh first_gen test_namex 100 10
./gin.sh first_gen alg_test1 100 10
./gin.sh first_gen alg_test2 100 10
./gin.sh first_gen alg_test3 100 10
./gin.sh first_gen alg_testALL 1 10
./gin.sh first_gen alg_testALL 10 10
./gin.sh first_gen alg_testALL 100 10
./gin.sh first_gen alg_testALL 1000 5
./gin.sh first_gen alg_testALL 10000 5
./gin.sh first_gen alg_testALL 100000 2
./gin.sh first_gen alg_testALL 1000000 2
./gin.sh first_gen alg_testALL 10000000 2
echo "

Generate output for these tests:
"
./run.sh perfect_alg alg_* test*
echo "

Check alg_test:
"
./chk.sh alg_test
echo "

Check wrong_alg:
"
./chk.sh wrong_alg test_namex test_name2
echo "

Plot alg_test 
"
./plot.sh alg_test alg_testALL

echo "


Generate inputs for sorting algorithms: 
"
i=100000

while [ $i -lt 1000000 ]; do
	./gin.sh ri_arr+1 sort $i
	let "i += 100000"
done

echo "

Generate output: 
"
./run.sh sort
echo "

Check algorithms: 
"
./chk.sh sort sort
./chk.sh sort_merge sort
./chk.sh sort_quick sort
./chk.sh sort_heap sort
echo "

Plot: 
"
./plot.sh sort sort
./plot.sh sort_merge sort
./plot.sh sort_quick sort
./plot.sh sort_heap sort
echo "

Compare: 
"
echo "plot \"`pwd`/dat/sort_sort.dat\" using 1:2 title 'built-in_quick' with lines, \
\"`pwd`/dat/sort_merge_sort.dat\" using 1:2 title 'merge' with lines, \
\"`pwd`/dat/sort_quick_sort.dat\" using 1:2 title 'quick' with lines, \
\"`pwd`/dat/sort_heap_sort.dat\" using 1:2 title 'heap' with lines" | gnuplot -persist
