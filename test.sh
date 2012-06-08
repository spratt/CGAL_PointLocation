#!/bin/bash
./build.sh

# bail if build failed
if [ $? -ne 0 ]; then
    exit
fi

# otherwise, run test
echo "======================================================================"
echo "| Point Location Test                                                |"
echo "======================================================================"

TIMED=false
SHOWN=false
if [ $# -eq 1 ]; then
    TIMED=true
elif [ $# -gt 1 ]; then
    SHOWN=true
fi

if $TIMED; then
    time ./locate_points segments.txt points.txt > /dev/null
elif $SHOWN; then
    time ./locate_points segments.txt points.txt
else
    if [ -f "random_xmonotone_points" -a -f "triangulate" ]; then
	if [ -f "locate_points" -a -f "generate_random_points" ]; then
	    echo "Generating triangulation..."
	    ./random_triangulation.sh 5000 -100000 100000 > segments.txt
	    echo "Generating points..."
	    ./generate_random_points 5000 -200000 200000 > points.txt
	    echo "Point location..."
	    ./locate_points segments.txt points.txt
	fi
    fi
fi
