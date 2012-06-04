#!/bin/bash
./build.sh

if [ -f "triangulate" -a -f "triangulate_input" ]; then
    cat triangulate_input | ./triangulate
fi