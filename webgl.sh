#!/bin/bash

rm -r build/webGL
mkdir build/webGL
cd build/webGL
cmake ../../ -DEMSCRIPTEN=1 -DCMAKE_CXX_COMPILER=em++ -DCMAKE_C_COMPILER=emcc 
emmake make
cp ../Packages.txt Packages.txt
cp ../GAME GAME
em++ LD34.bc -o LD34.html  -s ALLOW_MEMORY_GROWTH=1 -O2 --preload-file GAME
python -m SimpleHTTPServer 8080
