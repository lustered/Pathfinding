#pragma once
#include "header-files/jankibhimani-graph.h"
#include "header-files/d_matrix.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

using std::queue;
using std::stack;
using std::vector;

class pathfinder {
public:
  bool* visited;
  int moves[4][4] = {{0, 1}, {-1, 0},  // right, down
                     {0, -1}, {1, 0}}; // left, up

  /* Must have */
  pathfinder(std::ifstream &fin);
  void mapToGraph(graph &g);
  bool findPathRecursive(graph &g, stack<int> &moves);
  bool findPathNonRecursive1(graph &g, stack<int> &moves);
  bool findPathNonRecursive2(graph &g, queue<int> &moves);
  bool findShortestPath1(graph &g, stack<int> &bestMoves);
  bool findShortestPath2(graph &, vector<int> &bestMoves);
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
