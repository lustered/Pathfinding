#include "pathfinder.h"
#include "header-files/d_graph.h"
/* #include "header-files/jankibhimani-graph.h" */
#include <iterator>
#include <sstream>
#include <unordered_map>

/* Helpers */
void pathfinder::displayVals() {
  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < value[i].size(); ++j)
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
  /* this->visited = new bool[this->cols * this->cols]; */
  this->visited = new bool[this->cols * this->cols];

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
  /* for (int i = 1; i <= (this->cols * this->cols); ++i) */
  for (int i = 1; i <= this->cols * this->cols; ++i)
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
          g.insertEdge(vtx, vtx + 1, this->cols);

        /* Down */
        if (isLegal(value[i][j], value[i + 1][j]))
          g.insertEdge(vtx, vtx + this->cols, this->cols);
      } else if (i == this->rows - 1 && j < this->cols - 1) // Last row
        /* Check right */
        if (isLegal(value[i][j], value[i][j + 1]))
          g.insertEdge(vtx, vtx + 1, this->cols);
      vtx++;
    }
}

bool pathfinder::findPathRecursive(graph<int> &g, stack<int> &moves) {
  for (int i = 1; i < g.numberOfEdges(); i++)
    for (auto &&node : g.getNeighbors(i)) {

      std::cout << "Current node: " << node << "\n";

      if (!visited[node]) {
        visited[node] = true;
        findPathRecursive(g, moves);
      } 

      /* Not sure this would be right */
      if(node == (this->cols * this->rows)){
        std::cout << " result "<< node + this->cols;
        return true;
      }
    }

  return false;
}


bool pathfinder::findPathNonRecursive1(graph<int> &g, stack<int> &moves){ 
    /* moves.push(initNode); */
    bool visited[g.numberOfVertices()];
    stack<int> ret;
    int initNode = 1;
    ret.push(initNode);

    while(!ret.empty())
    {

      int cn = ret.top();
      ret.pop();

      if(!visited[cn])
        visited[cn] = true;

      for (int i = initNode; i < g.numberOfEdges(); i++)
        for (auto &&node : g.getNeighbors(i)){

          if(!visited[node])
            ret.push(node);
          else if(node == (this->cols * this->rows))
            return true;
          /* else */

        }
    }

    return false;
}
/* bool pathfinder::findPathNonRecursive2(graph<int> &g, queue<int> &moves){} */
/* bool pathfinder::findShortestPath1(graph<int> &g, stack<int> &bestMoves){} */
/* bool pathfinder::findShortestPath2(graph<int> &, vector<int> &bestMoves){} */

int main() {
  std::ifstream mapfile("map1.txt");
  pathfinder pf(mapfile);

  graph<int> g;

  pf.displayVals();
  pf.mapToGraph(g);
  stack<int> sm;
  queue<int> qm;

  /* g.display(); */

  /* std::cout << pf.findPathRecursive(g, sm); */
  std::cout << pf.findPathNonRecursive1(g, sm);
  std::cout << "stack size: " << sm.size() << std::endl;
  while(!sm.empty()){
    std::cout << sm.top() << std::endl;
    sm.pop();
  }

  /* Display the visited array */
  /* for(int i = 1; i < pf.numCols() * pf.numRows();i++) */
  /*   std::cout << pf.visited[i] << " -> " << i << std::endl; */

  /* g.display(); */

  return 0;
}
