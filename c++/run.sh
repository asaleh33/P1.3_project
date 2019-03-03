#!/bin/bash

code=main

make clean
make

{
for s in 100 500 1000 5000 10000 50000 100000 500000; do
  ./${code}.x $s;
done
} 2> bst_error.txt

exit 0;


