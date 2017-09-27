#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE 1
#include "vector.hpp"

namespace shukla{
class priority_queue{
	vector<pair<pair<int,int>,int> > A;
public:
	void insert(pair<pair<int,int>,int> p);
	pair<pair<int,int>,int> extract_min();
	pair<pair<int,int>,int> top();
	void decrease_key(int i, int j, int to);
	bool empty();
};
}

using namespace shukla;
void priority_queue::insert(pair<pair<int,int>,int> p)
{
	A.push_back(p);
	int it = A.size()-1;
	while(A[it].second < A[it/2].second)
	{
		std::swap(A[it/2],A[it]);
		it/=2;
	}
}

pair<pair<int,int>,int> priority_queue::extract_min()
{
	pair<pair<int,int>,int> min = A[0];
	std::swap(A[0] , A[A.size()-1]);
	A.remove_back();
	int len = A.size()-1;

	int it = 0, l = it*2, r = it*2+1;
	while(l<=len)
	{
		int low = it;
		if((r > len) && (A[it].second > A[l].second)) low = l;
		else if(r<=len)
		{
			if(A[l].second < A[r].second) low = (A[l].second < A[it].second?l:it);
			else low = (A[r].second < A[it].second?r:it);
		}
		if(low != it)
		{
			std::swap(A[it],A[low]);
			it = low, l = it*2, r = it*2+1;
		}
		else break;
	}
	return min;
}

pair<pair<int,int>,int> priority_queue::top()
{
	return A[0];
}

void priority_queue::decrease_key(int i, int j, int to)
{
	int it;
	for(it=0; it<A.size(); it++)
		if(A[it].first.first == i)
			break;
	A[it].first.second = j;
	A[it].second = to;
	while(A[it].second < A[it/2].second)
	{
		std::swap(A[it/2],A[it]);
		it/=2;
	}
}

bool priority_queue::empty()
{
	return (A.size()==0);
}
#endif