#!/bin/bash
../etc/largest_file.conf

cd ..
make clean
make
./largest_file $1