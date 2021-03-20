#include "pathfinder.h"
#include <iterator>
#include <sstream>
#include <unordered_map>

/* Helpers */
void pathfinder::displayVals() {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      /* std::cout << std::setw(4) << this->mapping[i][j]; */
      printf("%4d", this->mapping[i][j]);
      /* printf("%4d", this->value[i][j]); */
    }
    std::cout << std::endl;
  }
}

bool pathfinder::isLegal(int i, int j) {
  /* if (i < 0 || i > this->rows - 1 || j < 0 || j > this->cols - 1) */
  /*   return false; */
  /* if (!this->value[i][j]) */
  /*   return false; */

  /* return true; */
  try {
    if (this->value[i][j])
      return true;
    else
      return false;
  } catch (const std::exception) {
    return false;
  }
}

/* Constructor */
pathfinder::pathfinder(std::ifstream &mapfile) {
  mapfile >> this->rows >> this->cols;

  this->value = matrix<bool>(this->rows, this->cols, -1);
  this->mapping = matrix<int>(this->rows, this->cols, -1);

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


/* bool pathfinder::findPathRecursive(graph &g, stack<int> &moves) { */
/*   for (int i = 1; i < g.; i++) */
/*     for (auto &&node : g.getNeighbors(i)) { */

/*       std::cout << "Current node: " << node << "\n"; */

/*       if (!visited[node]) { */
/*         visited[node] = true; */
/*         findPathRecursive(g, moves); */
/*       } */

/*       /1* Not sure this would be right *1/ */
/*       if(node == (this->cols * this->rows)){ */
/*         std::cout << " result "<< node + this->cols; */
/*         return true; */
/*       } */
/*     } */

/*   return false; */
/* } */

/* bool pathfinder::findPathNonRecursive1(graph &g, stack<int> &moves){ */
/*     /1* moves.push(initNode); *1/ */
/*     bool visited[g.numberOfVertices()]; */
/*     stack<int> ret; */
/*     int initNode = 1; */
/*     ret.push(initNode); */

/*     while(!ret.empty()) */
/*     { */

/*       int cn = ret.top(); */
/*       ret.pop(); */

/*       if(!visited[cn]) */
/*         visited[cn] = true; */

/*       for (int i = initNode; i < g.numberOfEdges(); i++) */
/*         for (auto &&node : g.getNeighbors(i)){ */

/*           if(!visited[node]) */
/*             ret.push(node); */
/*           else if(node == (this->cols * this->rows)) */
/*             return true; */
/*           /1* else *1/ */

/*         } */
/*     } */

/*     return false; */
/* } */


void pathfinder::mapToGraph(graph &g) {
  /* The first node added will be a 0 */ 
  int vtx = 0;

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->cols; j++) {
      if (isLegal(i, j)) {
        this->mapping[i][j] = vtx;
        g.addNode(vtx);
        vtx++;
      }
    }

  vtx = 0;

  for (int i = 0; i < this->rows; ++i)
    for (int j = 0; j < this->cols; ++j) {
      /* Check Vertically */
      if (i < this->rows - 1)
        if (isLegal(i, j) && isLegal(i + 1, j))
          g.addEdge(this->mapping[i][j], this->mapping[i + 1][j]);

      /* Check horizontally */
      if (j < this->cols - 1)
        if (isLegal(i, j) && isLegal(i, j + 1))
          g.addEdge(this->mapping[i][j], this->mapping[i][j + 1]);
    }
}

/* bool pathfinder::findPathNonRecursive2(graph &g, queue<int> &moves){} */
/* bool pathfinder::findShortestPath1(graph &g, stack<int> &bestMoves){} */
/* bool pathfinder::findShortestPath2(graph &, vector<int> &bestMoves){} */

int main() {
  /********************** Read from file **********************/
  std::ifstream mapfile("map1.txt");
  pathfinder pf(mapfile);

  graph g;
  pf.mapToGraph(g);
  pf.displayVals();


  /********************* Graph info **********************/
  g.printNodes();
  g.printEdges();

  /********************* Pathfinding algorithms **********************/
  stack<int> sm;
  queue<int> qm;
  vector<int> vm;
  /* std::cout << pf.findPathRecursive(g, sm); */
  /* std::cout << pf.findPathNonRecursive1(g, sm); */
  /* std::cout << pf.findPathNonRecursive2(g, qm); */
  /* std::cout << pf.findShortestPath1(g, sm); */
  /* std::cout << pf.findShortestPath2(g, vm); */

  /********************* Print the stack **********************/
  /* std::cout << "stack size: " << sm.size() << std::endl; */
  /* while(!sm.empty()){ */
  /*   std::cout << sm.top() << std::endl; */
  /*   sm.pop(); */
  /* } */

  return 0;
}
