#!/bin/bash
./rebuild.sh

if [ -f "generate_random_points" ]; then
    ./generate_random_points 100 0 100000
fi

if [ -f "random_xmonotone_points" ]; then
    ./random_xmonotone_points 100 0 100000
fi

if [ -f "triangulate" -a -f "triangulate_input" ]; then
    cat triangulate_input | ./triangulate
fi

if [ -f "random_xmonotone_points" -a -f "triangulate" ]; then
    ./random_triangulation.sh 100 0 100000
fi
