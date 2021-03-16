#include "map.h"
#include <sstream>


map::map(std::ifstream &fin) { std::cin >> this->rows >> this->cols; }

void map::mapToGraph(graph &g) {
  /* Remove some overhead */
  /* g.maze.resize(g.r, vector<int>(g.c)); */
}

int main() {
  std::ifstream mapfile("mymap.txt");

  graph g(mapfile);
  g.display();

  return 0;
}
