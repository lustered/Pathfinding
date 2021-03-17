#include "pathfinder.h"
#include "header-files/d_graph.h"
#include <sstream>

/* Helpers */
void pathfinder::displayVals() {
  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < this->cols; ++j)
      /* std::cout << this->mapping[i][j]; */
      std::cout << this->value[i][j];
    std::cout << std::endl;
  }
}

bool pathfinder::isLegal(int i, int j) {
  if (i < 0 || i > this->rows - 1 || j < 0 || j > this->cols - 1)
    return false;
  else if (this->value[i][j] == false)
    return false;

  return true;
}

/* Constructor */
pathfinder::pathfinder(std::ifstream &mapfile) {
  mapfile >> this->rows >> this->cols;

  this->value.resize(this->rows, this->cols);
  this->mapping.resize(this->rows, this->cols);

  /* String to concatenate the lines in the file */
  std::string line;
  /* Keep a counter for the rows */
  unsigned int r = 0;
  /* Iterate to get all the lines in the file */
  while (mapfile >> line) {
    /* iterate for every char in the line */
    for (int i = 0; i < line.length() - 1; ++i) {
      /* If the character is an X, can't go there, else we can */
      if (line[i] == 'X')
        this->value[r][i] = false;
      else if (line[i] == 'O' || line[i] == 'Z')
        this->value[r][i] = true;
    }

    /* Continue to the next row */
    r++;
  }
} // End of pathfinder constructor

/*
 * moves = [0, 1]  right
 *         [-1, 0] down
 *         [0, -1] left
 *         [1, 0]  up
 */

void pathfinder::mapToGraph(graph<int> &g) {

  // Create vertices
  for (int i = 0; i < this->cols; ++i)
    g.insertVertex(i);

  for (int i = 0; i < this->rows; i++) 
    for (int j = 0; j < this->cols; j++)
      if ((this->value[i][j]) == true && i != j)
        g.insertEdge(i, j, 1);

  /* std::cout << "i: " << i << " j: " << j << std::endl; */
  /* std::cout << std::endl; */
}

int main() {
  std::ifstream mapfile("map1.txt");
  pathfinder pf(mapfile);

  /* Graph testing */
  graph<int> g;
  g.begin();

  /* pf.displayVals(); */
  pf.mapToGraph(g);


  for (int i = 0; i < g.numberOfVertices(); ++i) {
    set<int> s = g.getNeighbors(i);

    std::cout << "vertex: " << i;

    for (auto&& v: s)
      /* links += v; */
      std::cout <<  " --> " << v;
    std::cout << std::endl;
    /* std::cout << "vertex: " << i << "-->" << links <<  endl; */
  }

  /* pair<int,int> p; */

  /* g.insertVertex(1); */
  /* g.insertVertex(2); */
  /* g.insertVertex(3); */
  /* g.insertVertex(4); */
  /* g.insertVertex(5); */
  /* g.insertEdge(1, 4, 3); */
  /* g.insertEdge(1, 2, 5); */
  /* g.insertEdge(1, 3, 2); */
  /* g.insertEdge(1, 5, 1); */
  /* g.insertEdge(2, 1, 2); */
  /* g.insertEdge(3, 1, 5); */

  /* std::cout << "in degree of vertex 1: " << g.inDegree(1) << "\n"; */
  /* std::cout << "out degree of vertex 1: " << g.outDegree(1) << "\n"; */
  /* std::cout << "Weight of edge 1->2 before" << g.getWeight(1, 2) << "\n"; */
  /* g.setWeight(1, 2, 100); */
  /* std::cout << "Weight of edge 1->2 after" << g.getWeight(1, 2) << "\n"; */

  /* set<int> s = g.getNeighbors(1); */
  /* for (auto&& v: s) */
  /*   std::cout << v << std::endl; */


  return 0;
}
