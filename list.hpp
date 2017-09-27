#include <iostream>

#ifndef LIST_HPP
#define LIST_HPP 1

namespace shukla {
	template<typename T>
	class node
	{
		T value;
		node* next;
	public:
		void setValue(const T& val) {value = val;}
		T& getValue() {return value;}
		void setNext(node* nxt) {next = nxt;}
		node* getNext() {return next;}
	};

  	template<typename T>
    class list
    {
    	int size;
    	node<T>* head;
        node<T>* end;
    public:
        list();
        list(const list<T> & x);
        ~list();
        
		inline int length();
        inline bool empty();
        void printList();
        node<T>* getHead() const;
        node<T>* getEnd() const;
        
        void append(const T& value);
        void append(list<T>& x);
    	void cons(const T& value);
        void remove(const T & x);
    };
}

using namespace shukla;

// Primary contructor. Constructs an empty list with size = 0.
template<typename T>
list<T>::list()
{
	size = 0;
	head = nullptr;
	end = nullptr;
}

// Copy constructor. Creates a list which is a copy of the given list.
template<typename T>
list<T>::list(const list<T>& x)
{
	size = 0;
	head = nullptr;
	end = nullptr;
	node<T>* it = x.getHead();
	while(it!=nullptr)
	{
		node<T>* n = new node<T>;
		n->setValue(it->getValue());
		n->setNext(head);
		if(head==nullptr)
		{
			head = n;
			n->setNext(nullptr);
		}
		else
		{
			end->setNext(n);
			n->setNext(nullptr);
		}
		size++;
		end = n;
		it = it->getNext();
	}
}

// Destructor
template<typename T>
list<T>::~list()
{
	node<T>* n = head;
	while(n!=nullptr)
	{
		node<T>* temp = n;
		n = n->getNext();
		delete temp;
	}
	delete n;
}

// Adds the given value at the end of the list.
template<typename T>
void list<T>::append(const T& value)
{
	node<T>* n = new node<T>;
	n->setValue(value);
	n->setNext(head);
	if(head==nullptr)
	{
		head = n;
		n->setNext(nullptr);
	}
	else
	{
		end->setNext(n);
		n->setNext(nullptr);
	}
	end = n;
	size++;
}

// Add the given list to the end of our list.
template<typename T>
void list<T>::append(list<T>& x)
{
	node<T>* it = x.getHead();
	while(it!=nullptr)
	{
		node<T>* n = new node<T>;
		n->setValue(it->getValue());
		n->setNext(head);
		if(head==nullptr)
		{
			head = n;
			n->setNext(nullptr);
		}
		else
		{
			end->setNext(n);
			n->setNext(nullptr);
		}
		size++;
		end = n;
		it = it->getNext();
	}
}

// Add the given value at the start of the list.
template<typename T>
void list<T>::cons(const T& value)
{
	node<T>* n = new node<T>;
	n->setValue(value);
	n->setNext(head);
	head = n;
	size++;
}

// Removes the first node with the given value from the list.
template<typename T>
void list<T>::remove(const T& x)
{
	bool removed = false;
	if(head == nullptr) removed = false;
	else if(head->getValue()==x)
	{
		head = head->getNext();
		removed = true;
	}
	else
	{
		node<T> *it1 = head->getNext(), *it2 = head;
		while(it1!=nullptr && !removed)
		{
			if(it1->getValue()==x)
			{
				it2->setNext(it1->getNext());
				removed = true;
			}
			it1 = it1->getNext();
			it2 = it2->getNext();
		}
	}
	if(removed) size--;
}

// Print the list.
template<typename T>
void list<T>::printList()
{
	node<T>* it;
	it = head;
	if(it==nullptr)
		std::cout<<"The list is empty!\n";
	else
	{
		while(it!=nullptr)
		{
			std::cout<<it->getValue()<<std::endl;
			it = it->getNext();
		}
		std::cout<<"The length of the list is "<<size<<std::endl;
	}
}

// Return the length of our list.
template<typename T>
int list<T>::length()
{
	return size;
}

// Return a bool indicating whether the list is empty.
template<typename T>
bool list<T>::empty()
{
	return size==0;
}

// Return a pointer to the head node of the list.
template<typename T>
node<T>* list<T>::getHead() const
{
	return head;
}

// Return a pointer to the end node of the list.
template<typename T>
node<T>* list<T>::getEnd() const
{
	return end;
}

#endif