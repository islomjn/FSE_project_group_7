#!/bin/sh
sudo apt install libgtest-dev libgmock-dev
sudo apt install libtbb-dev
sudo apt install cmake
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
