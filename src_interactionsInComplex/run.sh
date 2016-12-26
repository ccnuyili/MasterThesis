#!/bin/bash
g++ source/main.cpp -o main
for file in $(ls data/id*);do
    ./main $file "$file"_edge.txt DIP_SPIN.txt
done
