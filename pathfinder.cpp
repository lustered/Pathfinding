#include "pathfinder.h"
#include "header-files/d_graph.h"
#include <sstream>

/* template <typename T> pathfinder<T>::pathfinder(std::ifstream &mapfile) { */
 pathfinder::pathfinder(std::ifstream &mapfile) {
  mapfile >> this->rows >> this->cols;

  this->value.resize(this->rows, this->cols);

  std::string data;
  while(mapfile >> data){

    unsigned int r = 0;

    for (unsigned int i = 0; i < data.length(); ++i) {

      if(data[i] == 'X')
        /* std::cout << " island"; */
        this->value[r][i] = false;
      else if(data[i] == 'O' || data[i] == 'Z')
        /* std::cout << " water"; */
        this->value[r][i] = true;
      /* else */
        // std::cout << " Goal";  In this case we can just get it by checking for m-1xn-1 

    } // End of for-loop
    std::cout << std::endl;

    /* Continue to the next row */
    r++;
  } // End of while loop
} // End of pathfinder constructor

int main() {
  std::ifstream mapfile("map1.txt");
  pathfinder pf(mapfile);

  /* Graph testing */
  /* 
  graph<int> g;
  g.begin();
  g.insertVertex(1);
  g.insertVertex(2);
  g.insertVertex(3);
  g.insertVertex(4);
  g.insertEdge(1, 2, 10);
  g.insertEdge(1, 3, 10);
  g.insertEdge(1, 4, 10);
  g.insertEdge(2, 1, 2);
  g.insertEdge(3, 1, 5);

  std::cout << "in degree of vertex 1: " << g.inDegree(1) << "\n";
  std::cout << "out degree of vertex 1: " << g.outDegree(1) << "\n";
  std::cout << "Weight of edge 1->2" << g.getWeight(1, 2) << "\n";
  */

  return 0;
}
