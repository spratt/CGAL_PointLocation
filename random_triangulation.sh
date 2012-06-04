#!/bin/bash
if [ $# -lt "3" ]; then
    echo "Usage: ./random_triangulation [n] [lower] [upper]"
    echo "     where n is the number of points to triangulate"
    echo "     and the coordinates vary from lower (inclusive) to upper (not inclusive)"
    exit
else
    ./random_xmonotone_points $1 $2 $3 | ./triangulate
fi