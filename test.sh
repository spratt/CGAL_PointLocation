#!/bin/bash
./rebuild.sh

if [ -f "random_xmonotone_points" -a -f "triangulate" ]; then
    if [ -f "locate_points" -a -f "generate_random_points" ]; then
	./random_triangulation.sh 5000 0 100000 > segments.txt
	./generate_random_points 5000 0 100000 > points.txt
	./locate_points segments.txt points.txt
    fi
fi
