#!/bin/bash
set -e
make ex17
./ex17 db.dat 512 100 c
./ex17 db.dat 512 100 s 1 zed zed@zed.com
./ex17 db.dat 512 100 s 2 frank frank@frank.com
./ex17 db.dat 512 100 s 3 joe joe@joe.com

./ex17 db.dat 512 100 l
./ex17 db.dat 512 100 d 3 

./ex17 db.dat 512 100 l
./ex17 db.dat 512 100 g 2

