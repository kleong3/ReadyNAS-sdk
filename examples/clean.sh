#!/bin/bash -e

HERE=$PWD

cd sample1-1.0.0
schroot -c R6 make -- veryclean
cd $HERE

cd sample2-1.0.0
schroot -c R6 make -- veryclean
cd $HERE

cd sample3-1.0.0
schroot -c R6 make -- veryclean
cd $HERE
