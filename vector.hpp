#include <iostream>

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

namespace shukla {
template <typename T>
class vector_iterator
{
    T* pointer;
    int size;
    int currentPosition;
public:
    void set(T* v,int vsize) {pointer=v; size=vsize; currentPosition=0;}
    void reset() {currentPosition=0;}

    bool hasNext() {return currentPosition<size;}
    T& next() {currentPosition++; return pointer[currentPosition];}
    T& current() {return pointer[currentPosition];}
    
    T* begin() {return pointer;}
    T* end() {return pointer+size;}
};

template <typename T>
class vector
{
    T* v;
    int vsize;
    int capacity;
public:
    typedef T* iterator;

    // Iterators
    vector_iterator<T> iter();
    iterator begin();
    iterator end();

    // Constructors and destructor
    vector();
    vector(const int& isize);
    vector(const int& isize,const T& ival);
    vector(vector& v_copy);
    ~vector();

    // Operator overloads
    inline T& operator [] (const int& i);
    inline vector<T>& operator = (vector<T>& v_copy);

    // Utility methods
    void push_back(const T& item);
    void remove_back();
    bool empty();
    int size();
    void fill(const T& val);
    void clear();
    T& front();
    T& back();
};
}

using namespace shukla;

// Returns an object of vector_iterator class, set to beginning of vector
template <typename T>
vector_iterator<T> vector<T>::iter()
{
    vector_iterator<T> it;
    it.set(v,vsize);
    return it;
}

// Return pointer to first element of vector
template <typename T>
T* vector<T>::begin()
{
    vector_iterator<T> it;
    it.set(v,vsize);
    return it.begin();
}

// Return pointer to element after the last element of vector
template <typename T>
T* vector<T>::end()
{
    vector_iterator<T> it;
    it.set(v,vsize);
    return it.end(); 
}

// Default constructor
template <typename T>
vector<T>::vector() 
{
    vsize=0;
    capacity=1;
    v = new T[capacity];
}

// Constructor for making a vector of isize elements
template <typename T>
vector<T>::vector(const int& isize)
{
    vsize = isize;
    capacity = 2*isize;
    v = new T[capacity]; 
}

// Constructor for making a vector of isize elements initialized with ival
template <typename T>
vector<T>::vector(const int& isize,const T& ival)
{
    vsize = isize;
    capacity = 2*isize;
    v = new T[capacity];
    for(int i=0;i<isize;i++)
        v[i]=ival;
}

// Copy constructor
template <typename T>
vector<T>::vector(vector<T>& v_copy)
{
    vsize = v_copy.vsize;
    capacity = v_copy.capacity;
    v = new T[capacity];
    for(int i=0;i<vsize;i++)
        v[i]=v_copy[i];
}

// Destructor
template <typename T>
vector<T>::~vector() 
{
    delete[] v;
}

// [] operator overloading
template <typename T>
T& vector<T>::operator [] (const int& i)
{
    return v[i];
}

// = operator overloading
template <typename T>
vector<T>& vector<T>::operator = (vector<T>& v_copy)
{
    delete[] v;
    vsize = v_copy.vsize;
    capacity = v_copy.capacity;
    v = new T[capacity];
    for(int i=0;i<vsize;i++)
        v[i] = v_copy[i];
    return *this;
}

// push_back() method to insert item at end of vector and resizing if necessary
template <typename T>
void vector<T>::push_back(const T& item)
{
    if(vsize+1<=capacity)
    {
        v[vsize]=item;
        vsize++;
    }
    else
    {
        T* v_copy = new T[capacity*2];
        for(int i=0;i<vsize;i++)
            v_copy[i]=v[i];
        v_copy[vsize]=item;
        vsize++;
        capacity *= 2;
        v = v_copy;
    }
}

// remove_back() method to remove item from end of the vector
template <typename T>
void vector<T>::remove_back()
{
    vsize--;
}

// Check if vector is empty
template <typename T>
bool vector<T>::empty()
{
    return vsize==0?true:false;
}

// Return the size of the vector
template <typename T>
int vector<T>::size()
{
    return vsize;
}

// Fill all elements of array with given value
template <typename T>
void vector<T>::fill(const T& val)
{
    for(int i=0;i<vsize;i++)
        v[i]=val;
}

// Return the first element of vector
template <typename T>
T& vector<T>::front()
{
    return v[0];
}

// Return the last element of vector
template <typename T>
T& vector<T>::back()
{
    return v[vsize-1];
}

// Remove all elements from the vector, thus resizing the vector to 0
template <typename T>
void vector<T>::clear()
{
    vsize=0;
    capacity=1;
    delete[] v;
    v = new T[capacity];
}

#endif