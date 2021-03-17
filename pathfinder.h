#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>
#include "header-files/d_graph.h"
#include "header-files/d_matrix.h"

using std::queue;
using std::stack;
using std::vector;

class pathfinder {
public:
  /* Must have */
  pathfinder(std::ifstream &fin);
  void mapToGraph(graph<int> &g);
  bool findPathRecursive(graph<int> &g, stack<int> &moves);
  bool findPathNonRecursive1(graph<int> &g, stack<int> &moves);
  bool findPathNonRecursive2(graph<int> &g, queue<int> &moves);
  bool findShortestPath1(graph<int> &g, stack<int> &bestMoves);
  bool findShortestPath2(graph<int> &, vector<int> &bestMoves);
  void printPath(stack<int> &s);
  void print(int, int, int, int);

  /* Utility */
  bool isLegal(int i, int j);
  void setMap(int i, int j, int n);
  int getMap(int i, int j) const;
  int getReverseMapI(int n) const;
  int getReverseMapJ(int n) const;
  void displayVals();

  int numRows() { return rows; };
  int numCols() { return cols; };

private:
  int rows; // number of latitudes/rows in the map
  int cols; // number of longitudes/columns in the map
  matrix<bool> value;
  matrix<int> mapping; // Mapping from latitude and longitude co-ordinates
                            // (i,j) values to node index values
  std::vector<int>
      reverseMapI; // Mapping from node index values to map latitude i value
  std::vector<int>
      reverseMapJ; // Mapping from node index values to map longitude j value
};
