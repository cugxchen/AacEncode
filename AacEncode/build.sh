#!/bin/sh
#rm -rf Build
export CC=gcc
export CXX=g++

# Compile
if [ ! -d Build/ ]; then
    mkdir Build
fi

if [ -f ../bin/${PROJECT} ]; then
    rm -f ../bin/${PROJECT}
fi

cd Build
cmake ..
make

