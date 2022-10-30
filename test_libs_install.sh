#!/bin/sh
apt install libgtest-dev libgmock-dev
apt install libtbb-dev
apt install cmake
PRJDIR=$(pwd)
cd /usr/src/googletest/
mkdir build
cd build
cmake ..
make
cp lib/* /usr/lib
cd ..
rm build -r
cd $PRJDIR
