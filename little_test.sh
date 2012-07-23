#!/bin/bash
./build.sh

# bail if build failed
if [ $? -ne 0 ]; then
    exit
fi

# options
if [ -f "random_xmonotone_points" -a -f "triangulate" ]; then
    if [ -f "locate_points_ric" -a -f "generate_random_points" ]; then
	echo "Generating triangulation..."
	./random_triangulation.sh 20 -10 10 > segments.txt
	echo "Generating points..."
	./generate_random_points 20 -12 12 > points.txt
	echo "Point location..."
    fi
fi

# naive
echo "======================================================================"
echo "| Naive Point Location                                               |"
echo "======================================================================"
time ./locate_points_naive segments.txt points.txt
