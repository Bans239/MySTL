#include <iostream>
#include <climits>

#ifndef QUEUE_HPP_
#define QUEUE_HPP_
#include "list.hpp"

namespace shukla {
    template<typename T>
    class queue
    {
    	list<T>* l; 
    public:
        queue();
        ~queue();
    
        void push(const T& t);
        T pop();
    
        T& front();
        inline int size();
        inline bool empty();
    };
}

using namespace shukla;

// Constructor, creates an empty queue.
template<typename T>
queue<T>::queue()
{
	l = new list<T>;
}

// Destructor.
template<typename T>
queue<T>::~queue()
{
	delete l;
}

// Push an element in the queue.
template<typename T>
void queue<T>::push(const T& t)
{
	l->append(t);
}

//Returns the element at the front of the queue, removing the front element from the queue.
template<typename T>
T queue<T>::pop()
{
	if(!l->empty())
	{
		T temp = l->getHead()->getValue();
		l->remove(temp);
		return temp;
	}
}

//Returns the element at the front of the queue.
template<typename T>
T& queue<T>::front()
{
	if(!l->empty()) return l->getHead()->getValue();
}

template<typename T>
inline int queue<T>::size()
{
	return l->length();
}

template<typename T>
inline bool queue<T>::empty()
{
	return l->length()==0;
}

#endif