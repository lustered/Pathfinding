/* Carlos Luis
 * Project Solution
 * CarlosLuisPathfinder.cpp
 */

#include "CarlosLuis_Map.h"
#include <sstream>

int main() {
  /********************** Read from file **********************/
  std::ifstream mapfile("map3.txt");
  Map pf(mapfile);

  graph g;
  pf.mapToGraph(g);
  pf.displayVals();

  /********************* Pathfinding algorithms **********************/
  stack<int> sm;
  queue<int> qm;
  vector<int> vm;

  /********************* Working Algorithms **********************/
  /* ---------------- Iterative ---------------- */
  /*********************** DFS ***********************/
  pf.findPathNonRecursive1(g, sm);
  /********************* BFS **********************/
  /* pf.findPathNonRecursive2(g, qm); */
  /*************** Dijkstra's Algorithm *****************/
  /* pf.findShortestPath1(g, sm); */

  /************ Recursive: Uncomment the following 2 lines **********/
  /* sm.push(0); */
  /* pf.findPathRecursive(g, sm); */

  /************* TODO: Not implemented. Will work on it on my own time
   * *********/
  /* Bellman Ford algorithm not implemented. */
  /* std::cout << pf.findShortestPath2(g, vm); */

  return 0;
}

/* Helpers */
void Map::displayVals() {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      printf("%5d", this->mapping[i][j]);
      /* printf("%5d", this->value[i][j]); */
    }
    std::cout << std::endl;
  }
}

bool Map::isLegal(int i, int j) {
  /* Brute force check */
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
Map::Map(std::ifstream &mapfile) {
  /* Create a Map from a text file stream */
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
} // End of Map constructor

void Map::mapToGraph(graph &g) {
  /* Translates a map file into a graph with vertices and edges */
  int vtx = 0;

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->cols; j++) {
      if (isLegal(i, j)) {
        this->mapping[i][j] = vtx;
        g.addNode(vtx);
        /* Set the weight of each node to the sum of row+col */
        /* g.setNodeWeight(vtx, i + j); */
        vtx++;
      }
    }

  vtx = 0;

  for (int i = 0; i < this->rows; ++i)
    for (int j = 0; j < this->cols; ++j) {
      /* Add edges vertically */
      if (i < this->rows - 1)
        if (isLegal(i, j) && isLegal(i + 1, j)) {
          g.addEdge(this->mapping[i][j], this->mapping[i + 1][j], i + j);
          g.addEdge(this->mapping[i + 1][j], i + j, this->mapping[i][j]);
        }

      /* Add edges horizontally */
      if (j < this->cols - 1)
        if (isLegal(i, j) && isLegal(i, j + 1)) {
          g.addEdge(this->mapping[i][j], this->mapping[i][j + 1], i + j);
          g.addEdge(this->mapping[i][j + 1], i + j, this->mapping[i][j]);
        }
    }
}

/********************* DFS **********************/
bool Map::findPathNonRecursive1(graph &g, stack<int> &moves) {
  /* Implements DFS to find the goal node */
  std::cout << "\n\nPerforming DFS: findPathRecursive1\n";

  stack<int> dfs;
  /* Starting node will be 0, since that's [0][0]; */
  dfs.push(0);
  moves.push(0);

  g.getNode(0).visit();

  /* While there are nodes unvisited */
  while (!dfs.empty()) {

    /* Check if the last node was visited. If so, we solved the maze. */
    if (g.getNode(g.numNodes() - 1).isVisited()) {
      /* Make sure we leave the graph intact for the next algorithm */
      g.clearVisit();
      std::cout << "found goal\n";
      this->printPath(moves);
      return true;
    }

    /* Get the last added node in the stack to be our current node(cn) */
    int cn = dfs.top();
    moves.push(cn);
    dfs.pop();

    std::cout << "Current node: " << cn << std::endl;

    /* Set current node as visited */
    if (!g.isVisited(cn))
      g.getNode(cn).visit();

    /* Add the neighbor nodes */
    for (int i = 0; i < g.numNodes(); i++)
      if (g.isEdge(cn, i))
        if (!g.isVisited(i))
          dfs.push(i);
  }

  std::cout << "Path was not found" << std::endl;
  return false;
}

/********************* BFS **********************/
bool Map::findPathNonRecursive2(graph &g, queue<int> &moves) {
  /* Implements BFS to find the goal node */
  std::cout << "\n\nPerforming BFS: findPathRecursive2\n";

  queue<int> bfs;

  bfs.push(0);
  moves.push(0);
  g.getNode(0).visit();

  while (!bfs.empty()) {
    int cn = bfs.front();
    moves.push(cn);
    bfs.pop();

    std::cout << "Current node: " << cn << std::endl;

    /* Check if the last node was visited. If so, we solved the maze. */
    if (g.getNode(g.numNodes() - 1).isVisited()) {
      /* Make sure we leave the graph intact for the next algorithm */
      g.clearVisit();

      std::cout << "found goal\n";
      stack<int> tmps;

      while (!moves.empty()) {
        int tmp = moves.front();
        moves.pop();
        tmps.push(tmp);
      }

      /* Print visualization */
      this->printPath(tmps);

      return true;
    }

    /* Set current node as visited */
    if (!g.isVisited(cn))
      g.getNode(cn).visit();

    int hasNeighbor = false;

    /* Add the neighbor nodes */
    for (int i = 0; i < g.numNodes(); i++) {
      if (g.isEdge(cn, i) || g.isEdge(i, cn))
        if (!g.isVisited(i)) {
          bfs.push(i);
          hasNeighbor = true;
        }
    }
    if (!hasNeighbor)
      moves.pop();
  }

  std::cout << "Path was not found" << std::endl;
  return false;
}

/********************* Recurisve **********************/
bool Map::findPathRecursive(graph &g, stack<int> &moves) {
  /* Finds the goal node in a graph using tail recursion */

  /*********** Stop recursion ***********/
  if (g.getNode(g.numNodes() - 1).isVisited()) {
    /* Make sure we leave the graph intact for the next algorithm */
    g.clearVisit();

    while (!moves.empty())
      moves.pop();

    /* this->printPath(moves); */

    std::cout << "found goal\n";
    return true;
  }

  if (!moves.empty()) { // return true;

    int cn = moves.top();
    moves.pop();
    g.visit(cn);

    std::cout << "Current node: " << cn << std::endl;

    /* Add neighbor nodes */
    for (int i = 0; i < g.numNodes(); i++) {
      if (g.isEdge(cn, i) || g.isEdge(i, cn))
        if (!g.isVisited(i))
          moves.push(i);
    }
  }

  return findPathRecursive(g, moves);
}

bool Map::findShortestPath1(graph &g, stack<int> &bestMoves) {
  /* Implemnentation of Dijkstra's algorithm using DFS/stack */
  std::cout << "\n\nPerforming DFS Dijkstra: findShortestPath1\n";
  const size_t INT_MAX = 99999;

  for (int i = 1; i < g.numNodes(); ++i) {
    g.setNodeWeight(i, INT_MAX);
  }

  stack<int> dfs;
  /* Starting node will be 0, since that's [0][0]; */
  dfs.push(0);
  bestMoves.push(0);
  g.visit(0);
  int weight;

  /* While there are nodes unvisited */
  while (!dfs.empty()) {

    /* Check if the last node was visited. If so, we solved the maze. */
    if (g.getNode(g.numNodes() - 1).isVisited()) {
      /* Make sure we leave the graph intact for the next algorithm */
      g.clearVisit();
      std::cout << "found goal\n";

      this->printPath(bestMoves);
      return true;
    }

    /* Get the last added node in the stack to be our current node(cn) */
    int cn = dfs.top();
    bestMoves.push(cn);
    dfs.pop();

    std::cout << "Current node: " << cn << std::endl;

    g.visit(cn);

    bool hasNeighbor = false;

    /* Find neighbor nodes */
    for (int i = 0; i < g.numNodes(); i++) {
      /* Check neighbors relation */
      if (g.isEdge(cn, i)) {
        /* If we haven't visited that neighbor */
        if (!g.isVisited(i)) {
          dfs.push(i);
          hasNeighbor = true;

          /* get the weight from the current node to the neighbors */
          weight = g.getEdgeWeight(cn, i);

          /* Relax node */
          if (g.getNodeWeight(cn) + weight < g.getNodeWeight(i))
            g.setNodeWeight(i, (g.getNodeWeight(i) + weight));
        }
      }
    }
  }

  std::cout << "Path was not found" << std::endl;
  return false;
}

/* Bellman Ford algorithm not implemented */
/* bool Map::findShortestPath2(graph &, vector<int> &bestMoves){} */

void Map::printPath(stack<int> &s) {
  /* Reverse stack in the proper order */
  stack<int> tmp;
  while (!s.empty()) {
    int cn = s.top();
    tmp.push(cn);
    s.pop();
  }

  /* Divider */
  std::string divider(this->cols * 4, '-');

  while (!tmp.empty()) {
    /* Get current node */
    int cn = tmp.top();
    tmp.pop();

    std::cout << divider << '\n';
    /* Current position of the node; */
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        if (this->mapping[i][j] == cn)
          printf("%3c|", '@');
        else if (this->value[i][j])
          printf("%3c|", 'O');
        else
          printf("%3c|", 'X');
      }
      std::cout << "\n";
    }

    std::cout << divider << '\n';
    std::cout << "\n";
  }
}
