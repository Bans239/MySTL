#ifndef ABSTRACT_GRAPH
#define ABSTRACT_GRAPH 1

class AbstractGraph {
public:
  virtual ~AbstractGraph() {}
  virtual bool edgeExits(int i, int j) = 0;
  virtual int edges() = 0;
  virtual int vertices() = 0;
  virtual void add(int i, int j, int wt) = 0;
  virtual void remove(int i, int j, int wt) = 0;  
  
  virtual void dfs(void (*work)(int&)) = 0;
  virtual void bfs(void (*work)(int&)) = 0;
  virtual void kruskal_mst() = 0;
  virtual void prims_mst(int src) = 0;
};
#endif