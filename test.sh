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

if [ $# -gt 0 ]; then
    TIMED_TEST=true
else
    TIMED_TEST=false
fi

if [ -f "random_xmonotone_points" -a -f "triangulate" ]; then
    if [ -f "locate_points" -a -f "generate_random_points" ]; then
	echo "Generating triangulation..."
	./random_triangulation.sh 5000 0 100000 > segments.txt
	echo "Generating points..."
	./generate_random_points 5000 0 100000 > points.txt
	echo "Point location..."
	if $TIMED_TEST; then
	    time ./locate_points segments.txt points.txt > /dev/null
	else
	    ./locate_points segments.txt points.txt
	fi
    fi
fi
