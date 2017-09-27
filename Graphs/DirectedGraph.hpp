#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1
#include <algorithm>
#include <climits>
#include "stack.hpp"
#include "queue.hpp"
#include "vector.hpp"
#include "AbstractGraph.hpp"
#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"
#include "DisjointSetDS.hpp"
#include "heap.hpp"

namespace shukla {
class DirectedGraph : AbstractGraph {	
    char type;
    AdjacencyList* Lgraph;
    AdjacencyMatrix* Mgraph;
public:
    DirectedGraph(int vertices, const char mode);
    ~DirectedGraph();
    int indegree(int i);
    int outdegree(int i);
    virtual bool edgeExits(int i, int j);
    virtual int edges();
    virtual int vertices();
    virtual void add(int i, int j, int wt);
    virtual void remove(int i, int j, int wt);
    virtual void dfs(void (*work)(int&));
    virtual void bfs(void (*work)(int&));
    virtual void kruskal_mst();
    virtual void prims_mst(int src);
};
}

using namespace shukla;
void DirectedGraph::prims_mst(int src)
{
	int n = Lgraph->vertices(), m = Lgraph->edges(), edges = 0;
    list<pair<int,int> >* graph = Lgraph->getGraph();

    priority_queue pq;
    vector<pair<int,int> > S(n,{0,INT_MAX}); // S: 'Visited' indicator and keeps track of key of all nodes.

    // Initialize heap with all nodes having INT_MAX key, and decrease 'src' key to 0.
    for(int i=0; i<n; i++)
    	pq.insert({{i,i},INT_MAX});
	pq.decrease_key(src,src,0);
    S[src].second = 0;

    while(!pq.empty() && edges<n-1)
    {
    	pair<pair<int,int>,int> ex = pq.extract_min();
    	int u = ex.first.first;
    	S[u].first = 1;
    	
    	// Updation of keys of all adjacent nodes of 'u' which are in S-V (non-visited nodes).
    	auto it = graph[u].getHead();
    	while(it!=nullptr)
    	{
    		int v = it->getValue().first;
    		if((S[v].first==0) && (S[v].second > it->getValue().second))
    		{
    			S[v].second = it->getValue().second;
	    		pq.decrease_key(v,u,S[v].second);
	    	}
    		it = it->getNext();
    	}
     	std::cout<<pq.top().first.second<<" -> "<<pq.top().first.first<<" ("<<pq.top().second<<")\n";
    	edges++;
    }
}

void DirectedGraph::kruskal_mst()
{
    vector<pair<int,pair<int,int> > > edges;
    int n,m;
    if(type=='m') 
    {
        n = Mgraph->vertices(), m = Mgraph->edges();
        int** graph = Mgraph->getGraph();
        for(int i=0; i<n; i++)
          for(int j=0; j<n; j++)
            if(graph[i][j]!=0)
              edges.push_back({graph[i][j],{i,j}});
    }
    else 
    {
        n = Lgraph->vertices(), m = Lgraph->edges();
        list<pair<int,int> >* graph = Lgraph->getGraph();
        for(int i=0; i<n; i++)
        {
            node<pair<int,int> >* it = graph[i].getHead();
            while(it!=nullptr)
            {
                edges.push_back({it->getValue().second,{i,it->getValue().first}});
                it = it->getNext();
            }
        }
    }

    DisjointSet Set(n);
    for(int i=0; i<n; i++) Set.CreateSet(i);
    std::sort(edges.begin(),edges.end());
    for(int i=0; i<m; i++)
    {
        if(Set.Union(edges[i].second.first, edges[i].second.second))
            std::cout<<" "<<edges[i].second.first<<" --> "<<edges[i].second.second<<" ("<<edges[i].first<<")\n";
    }
}

DirectedGraph::DirectedGraph(int vertices, const char mode)
{
    type = mode;
    if(mode == 'm') Mgraph = new AdjacencyMatrix(vertices);
    else Lgraph = new AdjacencyList(vertices);
}

DirectedGraph::~DirectedGraph()
{
    if(type == 'm') delete Mgraph;
    else delete Lgraph;
}

int DirectedGraph::indegree(int i)
{
    if(type=='m') return Mgraph->indegree(i);
    else return Lgraph->indegree(i);
}

int DirectedGraph::outdegree(int i)
{
    return (type=='m'? Mgraph->degree(i):Lgraph->degree(i));
}

bool DirectedGraph::edgeExits(int i, int j)
{
    if (type=='m') return Mgraph->edgeExits(i,j);
    else return Lgraph->edgeExits(i,j);
}

int DirectedGraph::edges()
{
    return (type=='m'? Mgraph->edges():Lgraph->edges());
}

int DirectedGraph::vertices()
{
    return (type=='m'? Mgraph->vertices():Lgraph->vertices());
}

void DirectedGraph::add(int i, int j, int wt)
{
    if(type == 'm') Mgraph->add(i,j,wt);
    else Lgraph->add(i,j,wt);
}

void DirectedGraph::remove(int i, int j, int wt)
{
    if(type == 'm') Mgraph->remove(i,j,wt);
    else Lgraph->remove(i,j,wt);
}

void DirectedGraph::dfs(void (*work)(int&))
{
    if(type == 'm') 
    {
        // DFS of directed graph using adjacency matrix
        int** graph = Mgraph->getGraph();
        int n = Mgraph->vertices(), m = Mgraph->edges();

        int color[n];
        for(int i=0; i<n; i++) color[i]=0;

        for(int src = 0; src<n; src++)
        {
            stack<int> s;
            if(color[src] == 0) 
            { 
                s.push(src);
                color[src]=1;
            }
            while(!s.empty())
            {
                int v = s.pop();
                if(color[v]==2) continue;
                for(int i=n-1; i>=0; i--)
                {
                    if(graph[v][i]!=0 && color[i]!=2 && i!=v) 
                    {
                        s.push(i);
                        color[i] = 1;
                    }
                }
                color[v] = 2;
                if(!s.empty() && s.top()!=v) 
                {
                    work(v);
                    std::cout<<" -> ";
                    work(s.top());
                    std::cout<<"\n";
                }
                else {work(v); std::cout<<" -> end\n";}
            }
        }
    }
    else
    {
        // DFS of directed graph using adjacency list
        list<pair<int,int> >* graph = Lgraph->getGraph();
        int n = Lgraph->vertices(), m = Lgraph->edges();

        int color[n], comp=1;
        for(int i=0; i<n; i++) color[i]=0;

        for(int src=0; src<n; src++)
        {
            stack<int> s;
            if(color[src] == 0) 
            {
                s.push(src);
                color[src]=1;
            }
            while(!s.empty())
            {
                int v = s.pop(), flag=0;
                if(color[v]==2) continue;
                for(auto it = graph[v].getHead(); it != nullptr; it = it->getNext())
                {
                    if(color[it->getValue().first] != 2 && it->getValue().first!=v)
                    {
                        s.push(it->getValue().first);
                        color[it->getValue().first] = 1;
                        flag=1;
                    }
                }
                color[v] = 2;
                if(!s.empty() && s.top()!=v && flag) 
                {
                    work(v);
                    std::cout<<" -> ";
                    work(s.top());
                    std::cout<<"\n";
                }
                else if(s.empty()) {work(v); std::cout<<" -> end\n";}
            }
        }
    }
}

void DirectedGraph::bfs(void (*work)(int&))
{
    if(type == 'm') 
    {
        // BFS of directed graph using adjacency matrix
        int** graph = Mgraph->getGraph();
        int n = Mgraph->vertices(), m = Mgraph->edges();

        int color[n];
        for(int i=0; i<n; i++) color[i]=0;

        for(int src=0; src<n; src++)
        {
            int flag=0;
            queue<int> q;
            if(color[src]==0) 
            {            
                q.push(src);
                color[src]=1;
            }
            while(!q.empty())
            {
                int v = q.pop();
                for(int i=0; i<n; i++)
                {
                    if(graph[v][i]!=0 && color[i]==0) 
                    {
                        q.push(i);
                        color[i] = 1;
                        work(v);
                        std::cout<<" -> ";
                        work(i);
                        std::cout<<"\n";
                        flag=1;
                    }
                }
                if(!flag) {work(v); std::cout<<" -> end\n";}
                color[v] = 2;
            }
        }
    }
    else
    {
        // BFS of directed graph using adjacency list
        list<pair<int,int> >* graph = Lgraph->getGraph();
        int n = Lgraph->vertices(), m = Lgraph->edges();

        int color[n];
        for(int i=0; i<n; i++) color[i]=0;

        for(int src=0; src<n; src++)
        {
            int flag=0;
            queue<int> q;
            if(color[src]==0) 
            {
                q.push(src);
                color[src]=1;
            }
            while(!q.empty())
            {
                int v = q.pop();
                for(auto it = graph[v].getHead(); it != nullptr; it = it->getNext())
                {
                    if(color[it->getValue().first] == 0)
                    {
                        q.push(it->getValue().first);
                        color[it->getValue().first] = 1;
                        work(v);
                        std::cout<<" -> ";
                        work(it->getValue().first);
                        std::cout<<"\n";
                        flag=1;
                    }
                }
                if(!flag) {work(v); std::cout<<" -> end\n";}
                color[v] = 2;
            }
        }
    }
}
#endif
