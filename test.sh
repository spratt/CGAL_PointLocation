#!/bin/bash
./build.sh

if [ -f "generate_random_points" ]; then
    ./generate_random_points 100 0 100000
fi

if [ -f "triangulate" -a -f "triangulate_input" ]; then
    cat triangulate_input | ./triangulate
fi