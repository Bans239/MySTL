#ifndef DISJOINT_SET_DS
#define DISJOINT_SET_DS 1

namespace shukla {
class DSNode {
public:
    int value;
    DSNode* parent;
};

class DisjointSet {
    DSNode* set;
public:
    DisjointSet(int numVertices);
    ~DisjointSet();
    void CreateSet(int x);
    pair<DSNode*,int> Find(int x);
    bool Union(int x, int y);
};
}

using namespace shukla;
DisjointSet::DisjointSet(int numVertices)
{
    set = new DSNode[numVertices];
}

DisjointSet::~DisjointSet()
{
    delete set;
}

void DisjointSet::CreateSet(int x)
{
    set[x].parent = &set[x];
    set[x].value = x;
}

pair<DSNode*,int> DisjointSet::Find(int x)
{
    DSNode* it = &set[x];
    int size=0;
    while(it != it->parent)
    {
		it = it->parent;
    	size++;
    }
    return {it,size};
}

bool DisjointSet::Union(int x, int y)
{
    pair<DSNode*,int> Xrep = Find(x);
    pair<DSNode*,int> Yrep = Find(y);
    if(Xrep.first->value == Yrep.first->value) return false;
    
    if(Xrep.second < Yrep.second) Xrep.first->parent = Yrep.first;
    else Yrep.first->parent = Xrep.first;
    return true;
}
#endif