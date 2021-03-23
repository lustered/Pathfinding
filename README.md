<!-- Carlos Luis -->
<!-- Project Solution -->

# Compilation and execution instructions

## Linux

    g++ -std=c++11 -Wall CarlosLuisPathfinder.cpp
    ./a.out

## Windows

    Compiles and runs with Microsoft Visual Studio with C++ support.

## To choose the algorithm to run, uncomment its respective line from 23 - 32:

      /********************* Working Algorithms **********************/

      /*********************** DFS ***********************/
      /* pf.findPathNonRecursive1(g, sm); */

      /********************* BFS **********************/
      /* pf.findPathNonRecursive2(g, qm); */

      /*************** Dijkstra's Algorithm *****************/
      /* pf.findShortestPath1(g, sm); */

      /************ Recursive: Uncomment the following 2 lines **********/
      /* sm.push(0); */
      /* pf.findPathRecursive(g, sm); */

#### To choose the map.txt file, edit the name in line 7.

#### Working Condition of the algorithms:

| Map File | Recursive | NonRec1 | NonRec2 | ShortestPath1 | ShortestPath2   |
| -------- | --------- | ------- | ------- | ------------- | --------------- |
| map1     | ✅        | ✅      | ✅      | ✅            | Not implemented |
|          |           |
| map2     | ✅        | ❌      | ✅      | ❌            | Not implemented |
|          |           |
| map3     | ✅        | ❌      | ✅      | ❌            | Not implemented |

#### Notes

Initially I fixed and used the d_graph header file but decided to
reimplement everything with the newer supplied file.

DFS fails when it needs to move left in some cases.<br>
Due to my Dijkstra's algorithm being a DFS implementation, it inherits this error.
