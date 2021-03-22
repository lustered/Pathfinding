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

void pathfinder::mapToGraph(graph &g) {
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
      /* Add edges vertically */
      if (i < this->rows - 1)
        if (isLegal(i, j) && isLegal(i + 1, j))
          g.addEdge(this->mapping[i][j], this->mapping[i + 1][j]);

      /* Add edges horizontally */
      if (j < this->cols - 1)
        if (isLegal(i, j) && isLegal(i, j + 1))
          g.addEdge(this->mapping[i][j], this->mapping[i][j + 1]);
    }
}

/********************* DFS **********************/
bool pathfinder::findPathNonRecursive1(graph &g, stack<int> &moves) {
  std::cout << "\n\nPerforming DFS: findPathRecursive1\n";

  /* Starting node will be 0, since that's [0][0]; */
  moves.push(0);
  g.getNode(0).visit();

  /* While there are nodes unvisited */
  while (!moves.empty()) {

    /* Check if the last node was visited. If so, we solved the maze. */
    if (g.getNode(g.numNodes() - 1).isVisited()) {
      /* Make sure we leave the graph intact for the next algorithm */
      g.clearVisit();
      std::cout << "found goal\n";
      return true;
    }

    /* Get the last added node in the stack to be our current node(cn) */
    int cn = moves.top();
    moves.pop();

    std::cout << "Current node: " << cn << std::endl;

    /* Set current node as visited */
    if (!g.isVisited(cn))
      g.getNode(cn).visit();

    for (int i = 0; i < g.numNodes(); i++)
      if (g.isEdge(cn, i))
        if (!g.isVisited(i))
          moves.push(i);
  }

  return false;
}

/********************* BFS **********************/
bool pathfinder::findPathNonRecursive2(graph &g, queue<int> &moves) {
  std::cout << "\n\nPerforming BFS: findPathRecursive2\n";

  moves.push(0);
  g.getNode(0).visit();

  while (!moves.empty()) {
    int cn = moves.front();
    moves.pop();

    std::cout << "Current node: " << cn << std::endl;

    /* Check if the last node was visited. If so, we solved the maze. */
    if (g.getNode(g.numNodes() - 1).isVisited()) {
      /* Make sure we leave the graph intact for the next algorithm */
      g.clearVisit();
      std::cout << "found goal\n";
      return true;
    }

    /* Set current node as visited */
    if (!g.isVisited(cn))
      g.getNode(cn).visit();

    for (int i = 0; i < g.numNodes(); i++)
      if (g.isEdge(cn, i))
        if (!g.isVisited(i))
          moves.push(i);
  }

  return false;
}

/********************* Recurisve **********************/
bool pathfinder::findPathRecursive(graph &g, stack<int> &moves) {

  /*********** Stop recursion ***********/
  if (g.getNode(g.numNodes() - 1).isVisited()) {
    /* Make sure we leave the graph intact for the next algorithm */
    g.clearVisit();

    while (!moves.empty())
      moves.pop();

    std::cout << "found goal\n";
    return true;
  }

  if (!moves.empty()) { // return true;

    int cn = moves.top();
    moves.pop();
    g.visit(cn);

    std::cout << "Current node: " << cn << std::endl;

    for (int i = 0; i < g.numNodes(); i++) {
      if (g.isEdge(cn, i))
        if (!g.isVisited(i)) {
          moves.push(i);
          /* findPathRecursive(g, moves); */
        }
    }
  }

  return findPathRecursive(g, moves);
}

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
  /* g.printNodes(); */
  /* g.printEdges(); */
  /********************* Pathfinding algorithms **********************/
  stack<int> sm;
  queue<int> qm;
  vector<int> vm;
  /********************* Working condition **********************/
  /* std::cout << pf.findPathNonRecursive1(g, sm); */
  /* std::cout << pf.findPathNonRecursive2(g, qm); */

  /********************* TODO **********************/
  /* Push the source edge. Incremental search */
  sm.push(0);
  std::cout << pf.findPathRecursive(g, sm);

  /* std::cout << pf.findShortestPath1(g, sm); */
  /* std::cout << pf.findShortestPath2(g, vm); */

  /********************* TESTING **********************/

  /********************* Print the stack **********************/
  /* std::cout << "stack size: " << sm.size() << std::endl; */
  /* while(!sm.empty()){ */
  /*   std::cout << sm.top() << std::endl; */
  /*   sm.pop(); */
  /* } */

  return 0;
}
