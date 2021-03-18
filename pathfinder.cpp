#include "pathfinder.h"
#include "header-files/d_graph.h"
#include <iterator>
#include <sstream>
#include <unordered_map>

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
  /* if (i < 0 || i > this->rows - 1 || j < 0 || j > this->cols - 1) */

  /* Brute force check */
  try {
    if (this->value[i][j] == true)
      return true;
    else
      return false;

  } catch (const std::exception &e) {
    std::cout << "Caught exception\n";
    return false;
  }
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
    for (int i = 0; i < line.length(); ++i) {
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
  for (int i = 1; i <= (this->cols * this->cols); ++i)
    g.insertVertex(i);

  int vtx = 1;

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->value[i].size(); j++) {

      /* Check down */
      if (i != this->rows - 1 && j == this->cols - 1)
        if (isLegal(i, this->value[i + 1][j]))
          g.insertEdge(vtx, vtx + this->cols, this->cols);

      /* Check right */
      if (i < this->rows - 1 && j < this->cols - 1) {
        if (isLegal(value[i][j], value[i][j + 1]))
          g.insertEdge(vtx, vtx + 1, 10);

        /* Down */
        if (isLegal(value[i][j], value[i + 1][j]))
          g.insertEdge(vtx, vtx + this->cols, 10);
      } else if (i == this->rows - 1 && j < this->cols - 1) // Last row
        /* Check right */
        if (isLegal(value[i][j], value[i][j + 1]))
          g.insertEdge(vtx, vtx + 1, 10);
      vtx++;
    }
}

/* Recursive DFS */
bool pathfinder::findPathRecursive(graph<int> &g, stack<int> &moves) {
  /* unordered_map<int, bool> visited; */

  /* Booleans are initialized as false by default */
  bool *visited = new bool[g.numberOfVertices()];
  graph<int> *tmp = new graph<int>(g);

  unsigned int vrtx = 1; 
  bool found = false;
  visited[vrtx] = true;

  for (int i = 1; i < g.numberOfEdges(); i++)
    for (auto &&node : g.getNeighbors(i)) {

      std::cout << "Current node: " << node << "\n";

      if (!visited[node]) {
        tmp->eraseVertex(vrtx++);
        findPathRecursive(*tmp, moves);
      }
    }

  return found;
}
/* DFS */
bool pathfinder::findPathNonRecursive1(graph<int> &g, stack<int> &moves){

  stack<int> visited;

  return false;
}

int main() {
  std::ifstream mapfile("map1.txt");
  pathfinder pf(mapfile);

  /* Graph testing */
  graph<int> g;

  pf.displayVals();
  pf.mapToGraph(g);
  stack<int> moves;
  std::cout << pf.findPathRecursive(g, moves);
  /* std::cout << pf.findPathNonRecursive1(g, moves); */

  /* std::cout << g.numberOfEdges(); */

  /* Print all nodes and edges */
  /* for (int i = 1; i < g.numbcrOfEdges(); i++) { */
  /* for (int i = 1; i < 3; i++) { */

  /* set<int> nodes = g.getNeighbors(i); */
  /* std::cout << "Node: " << i; */

  /* for(auto&& n : nodes) */
  /*   std::cout << " --> " << n; */

  /* std::cout << std::endl; */
  /* } */

  /* std::cout << "in degree of vertex 1: " << g.inDegree(1) << "\n"; */
  /* std::cout << "out degree of vertex 1: " << g.outDegree(1) << "\n"; */
  /* std::cout << "Weight of edge 1->2 before" << g.getWeight(1, 2) << "\n"; */
  /* g.setWeight(1, 2, 100); */
  /* std::cout << "Weight of edge 1->2 after" << g.getWeight(1, 2) << "\n"; */

  return 0;
}
