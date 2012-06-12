#!/bin/bash
./build.sh

# bail if build failed
if [ $? -ne 0 ]; then
    exit
fi

# options
TIMED=false
HIDE=false
REBUILD=false
if [ $# -eq 0 ]; then
    TIMED=true
elif [ $# -eq 1 ]; then
    HIDE=true
elif [ $# -eq 2 ]; then
    REBUILD=true
fi

if $REBUILD; then
    if [ -f "random_xmonotone_points" -a -f "triangulate" ]; then
	if [ -f "locate_points_ric" -a -f "generate_random_points" ]; then
	    echo "Generating triangulation..."
	    ./random_triangulation.sh 5000 -100000 100000 > segments.txt
	    echo "Generating points..."
	    ./generate_random_points 5000 -200000 200000 > points.txt
	    echo "Point location..."
	fi
    fi
fi

# naive
echo "======================================================================"
echo "| Naive Point Location                                               |"
echo "======================================================================"

if $TIMED; then
    time ./locate_points_naive segments.txt points.txt
elif $HIDE; then
    time ./locate_points_naive segments.txt points.txt > naive.txt
else
    ./locate_points_naive segments.txt points.txt
fi

# ric
echo "======================================================================"
echo "| Point Location using Randomized Incremental Trapezoid Maps         |"
echo "======================================================================"

if $TIMED; then
    time ./locate_points_ric segments.txt points.txt
elif $HIDE; then
    time ./locate_points_ric segments.txt points.txt > ric.txt
else
    ./locate_points_ric segments.txt points.txt
fi

# landmarks
echo "======================================================================"
echo "| Point Location using a KD tree on random landmarks                 |"
echo "======================================================================"

if $TIMED; then
    time ./locate_points_landmarks segments.txt points.txt
elif $HIDE; then
    time ./locate_points_landmarks segments.txt points.txt > landmarks.txt
else
    ./locate_points_landmarks segments.txt points.txt
fi

# comparison
if $HIDE; then
    diff naive.txt ric.txt
    diff naive.txt landmarks.txt
fi