#!/bin/bash -e

export LANGUAGE=C
export LC_ALL=C
export LANG=en_US.utf8

HERE=$PWD

cd sample1-1.0.0
schroot -c R6 debuild -- -uc -us -B
ARCH=arm schroot -p -c R6 debuild -- -e ARCH -uc -us -B -aarmel
cd $HERE

cd sample2-1.0.0
schroot -c R6 debuild -- -uc -us -A
cd $HERE

cd sample3-1.0.0
schroot -c R6 debuild -- -uc -us -A
cd $HERE
