#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1
#include "GraphAdjacencyBase.hpp"

namespace shukla{
class AdjacencyMatrix : public GraphAdjacencyBase {
	int numVertices, numEdges;
	int** graph;
public:
	int** getGraph() {return graph;}
	AdjacencyMatrix(int num);
  	~AdjacencyMatrix();

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
AdjacencyMatrix::AdjacencyMatrix(int num)
{
	numVertices = num;
	numEdges = 0;
	graph = new int*[numVertices];
	for(int i = 0; i<numVertices; ++i)
	{
    	graph[i] = new int[numVertices];
		for(int j=0; j < numVertices; ++j)
			graph[i][j] = 0;
	}
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	for(int i = 0; i < numVertices; ++i)
    	delete [] graph[i];
	delete [] graph;
}

bool AdjacencyMatrix::edgeExits(int i, int j)
{
	if(i>=numVertices || j>=numVertices || i<0 || j<0) return false;
	if(graph[i][j]!=0) return true;
	return false;
}

int AdjacencyMatrix::vertices()
{
	return numVertices;
}

int AdjacencyMatrix::edges()
{
	return numEdges;
}

void AdjacencyMatrix::add(int i, int j, int wt)
{
	if(i>=numVertices || j>=numVertices || i<0 || j<0) return;
	if(graph[i][j]==0)
	{	
		numEdges++;
		graph[i][j] = wt;
	}
}

void AdjacencyMatrix::remove(int i, int j, int wt)
{
	if(i>=numVertices || j>=numVertices || i<0 || j<0) return;
	if(graph[i][j]!=0) 
	{	
		numEdges--;
		graph[i][j] = 0;
	}
}

int AdjacencyMatrix::degree(int i)
{
	if(i>=numVertices || i<0) return 0;
	int deg=0;
	for(int j=0; j<numVertices; j++)
		if(graph[i][j]!=0) deg++;
	return deg;
}

int AdjacencyMatrix::indegree(int i)
{
	if(i>=numVertices || i<0) return 0;
	int deg=0;
    for(int k=0; k<numVertices; k++)
        if(graph[k][i]==1) deg++;
	return deg;
}
#endif