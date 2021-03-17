#include <list>
class graph {
public:
  int numV;
  std::list<int> *adj;

  graph(int verts = 1);
  void insertEdge(int vert, int w); 
};

graph::graph(int verts){
    this->numV = verts;
}

void graph::insertEdge(int vert, int w){
    adj[vert].push_back(w);
}
