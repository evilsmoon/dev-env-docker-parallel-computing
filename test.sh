#!/bin/sh
set -e

echo "--- Test OpenMP installation ---"

echo "check for gcc"
gcc --version 
# gcc --version > /debian
echo ok
echo "check for mpirun"
mpirun --version 
echo ok
echo "check for mpicc"
mpicc --version 
echo ok
echo "check for cmake"
cmake --version 
echo ok

