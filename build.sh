#!/bin/bash
if [ ! -f "CMakeLists.txt" ]; then
    cgal_create_cmake_script
fi

if [ ! -f "Makefile" ]; then
    cmake .
fi

if [ -f "Makefile" ]; then
    make
fi