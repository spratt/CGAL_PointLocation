#!/bin/bash
./rebuild.sh

cp /home2bak/spratt/Projects/LEDA_PointLocation/points.txt .
cp /home2bak/spratt/Projects/LEDA_PointLocation/segments.txt .

# naive
echo "======================================================================"
echo "| Naive Point Location                                               |"
echo "======================================================================"
./locate_points_naive segments.txt points.txt > naive.txt
time ./locate_points_naive segments.txt points.txt