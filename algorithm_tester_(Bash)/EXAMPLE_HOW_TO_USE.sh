#!/bin/bash

echo "@@@@@@@@@@@@@@@@@@@@0

"
./gin first_gen test_name 1 100
./gin first_gen test_name2 10
./gin first_gen test_namex 100 10
echo "@@@@@@@@@@@@@@@@@@@@1

"
./gin first_gen alg_test1 100 10
./gin first_gen alg_test2 100 10
./gin first_gen alg_test3 100 10
echo "@@@@@@@@@@@@@@@@@@@@2

"
./gin first_gen alg_testALL 1 10
./gin first_gen alg_testALL 10 10
./gin first_gen alg_testALL 100 10
./gin first_gen alg_testALL 1000 5
./gin first_gen alg_testALL 10000 5
./gin first_gen alg_testALL 100000 2
./gin first_gen alg_testALL 1000000 2
./gin first_gen alg_testALL 10000000 2
echo "@@@@@@@@@@@@@@@@@@@@3

"
./run perfect_alg alg_* test*
echo "@@@@@@@@@@@@@@@@@@@@4

"
./chk alg_test
echo "@@@@@@@@@@@@@@@@@@@@5

"
./plot alg_test alg_testALL
echo "@@@@@@@@@@@@@@@@@@@@6

"
./chk wrong_alg test_namex test_name2
