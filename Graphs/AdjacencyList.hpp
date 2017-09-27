#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1
#include "list.hpp"
#include "GraphAdjacencyBase.hpp"
using std::pair;

namespace shukla{
class AdjacencyList : public GraphAdjacencyBase {
	int numVertices, numEdges;
	list<pair<int,int> >* graph;
public:
	list<pair<int,int> >* getGraph() {return graph;}
	AdjacencyList(int num);
  	~AdjacencyList();

  	virtual bool edgeExits(int i, int j);
 	virtual int vertices();
	virtual int edges();
	virtual void add(int i, int j, int wt);
  	virtual void remove(int i, int j, int wt);	
	virtual int degree(int i);
	int indegree(int i);
};
}

using namespace shukla;
AdjacencyList::AdjacencyList(int num)
{
	numVertices = num;
	numEdges = 0;
	graph = new list<pair<int,int> >[numVertices];
}

AdjacencyList::~AdjacencyList()
{
	delete [] graph;
}

bool AdjacencyList::edgeExits(int i, int j)
{
	node<pair<int,int> >* it = graph[i].getHead();
	while(it != nullptr)
	{
		if(it->getValue().first == j) return true;
		it = it->getNext();
	}
	return false;
}

int AdjacencyList::vertices()
{
	return numVertices;
}

int AdjacencyList::edges()
{
	return numEdges;
}

void AdjacencyList::add(int i, int j, int wt)
{
	if(i>=numVertices || j>=numVertices || i<0 || j<0) return;
	graph[i].cons({j,wt});
	numEdges++;
}

void AdjacencyList::remove(int i, int j, int wt)
{
	if(i>=numVertices || j>=numVertices || i<0 || j<0) return;
	graph[i].remove({j,wt});
	numEdges--;
}

int AdjacencyList::degree(int i)
{
	return graph[i].length();
}

int AdjacencyList::indegree(int i)
{
	int inD=0;
	for(int k=0; k<numVertices; k++)
    {
        node<pair<int,int> >* it = graph[k].getHead();
        while(it != nullptr)
        {
            if(it->getValue().first == i) inD++;
            it = it->getNext();
        }
    }
    return inD;
}
#endif