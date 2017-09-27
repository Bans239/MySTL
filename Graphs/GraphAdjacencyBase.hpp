#ifndef GRAPH_ADJACENCY_BAG
#define GRAPH_ADJACENCY_BAG 1

class GraphAdjacencyBase {
public:
 	virtual ~GraphAdjacencyBase() {}
  	virtual bool edgeExits(int i, int j) = 0;
 	virtual int vertices() = 0;
	virtual int edges() = 0;
	virtual void add(int i, int j, int wt) = 0;
  	virtual void remove(int i, int j, int wt) = 0;
	virtual int degree(int i) = 0;
};
#endif