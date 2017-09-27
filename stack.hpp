#include <iostream>
#include <climits>

#ifndef STACK_HPP_
#define STACK_HPP_
#include "list.hpp"

namespace shukla {
  	template<typename T>
    class stack
    {
    	list<T>* l;
    public:
        stack();
        ~stack();

        void push(const T& t);
        T pop();

        T& top();
        int size();
        inline bool empty();
    };
}

using namespace shukla;

// Constructor, creates an empty stack.
template<typename T>
stack<T>::stack()
{
	l = new list<T>;
}

// Destructor.
template<typename T>
stack<T>::~stack()
{
	delete l;
}

// Push an element in the stack.
template<typename T>
void stack<T>::push(const T& t)
{
	l->cons(t);
}

//Returns the element at the top of the stack, removing the top element from the stack.
template<typename T>
T stack<T>::pop()
{
	if(!l->empty())
	{
		T temp = l->getHead()->getValue();
		l->remove(temp);
		return temp;
	}
	else
	{
		std::cout<<"Can't pop as the stack is empty!\n";
		return INT_MIN;
	}	
}

//Returns the element at the top of the stack.
template<typename T>
T& stack<T>::top()
{
	if(!l->empty()) return l->getHead()->getValue();
}

template<typename T>
int stack<T>::size()
{
	return l->length();
}

template<typename T>
inline bool stack<T>::empty()
{
	return l->length()==0;
}

#endif