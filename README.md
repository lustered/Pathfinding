# Compilation and execution instructions

## Linux

    g++ -std=c++11 -Wall pathfinder.cpp
    ./a.out

## Windows

    Compiles and runs with Microsoft Visual Studio with C++ support.

#### To choose the map.txt file, pass it as an arg, eg:

    g++ -std=c++11 -Wall pathfinder.cpp
    ./a.out map1.txt

## Notes

I have modified d_graph.h header file (provided by the professor) to properly compile using the gcc compiler.
