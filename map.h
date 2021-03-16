#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

using std::queue;
using std::stack;
using std::vector;

/* template <unsigned int t_r> */
class graph {
public:
  std::vector<std::vector<int>> maze;
  /* int** maze = new int*[t_r]; */
  unsigned int r;
  unsigned int c;

  /* graph(unsigned int const rows, unsigned int const cols); */
  graph(std::ifstream &mapfile) {
    mapfile >> this->r >> this->c;

    std::string tmp;
    int row = 0;
    int col = 0;

    while (std::getline(mapfile, tmp)) {
      std::stringstream ss(tmp);
      std::string data;

      ss >> data;

      for (int i = 0; i < data.length(); ++i) {
        std::cout << data[i];
      }
      std::cout << std::endl;
    }
  }

  ~graph() {}

  unsigned int rows() { return this->r; }
  unsigned int cols() { return this->c; }

  void push(int &n) {}

  void display() {
    for (unsigned int i = 0; i < this->c; ++i) {
      for (unsigned int j = 0; j < this->c; ++j)
        std::cout << this->maze[i][j];
      std::cout << "\n";
    }
  }
};

class map {
public:
  /* Must have */
  map(std::ifstream &fin);
  void mapToGraph(graph &g);
  bool findPathRecursive(graph &g, stack<int> &moves);
  bool findPathNonRecursive1(graph &g, stack<int> &moves);
  bool findPathNonRecursive2(graph &g, queue<int> &moves);
  bool findShortestPath1(graph &g, stack<int> &bestMoves);
  bool findShortestPath2(graph &, vector<int> &bestMoves);
  void printPath(stack<int> &s);
  void print(int, int, int, int);

  /* void map::printPath(stack<int> &s); */
  bool isLegal(int i, int j);
  void setMap(int i, int j, int n);
  int getMap(int i, int j) const;
  int getReverseMapI(int n) const;
  int getReverseMapJ(int n) const;

  int numRows() { return rows; };
  int numCols() { return cols; };

private:
  int rows; // number of latitudes/rows in the map
  int cols; // number of longitudes/columns in the map
  std::vector<bool> value;
  std::vector<int> mapping; // Mapping from latitude and longitude co-ordinates
                            // (i,j) values to node index values
  std::vector<int>
      reverseMapI; // Mapping from node index values to map latitude i value
  std::vector<int>
      reverseMapJ; // Mapping from node index values to map longitude j value
};
