#include <iostream>
#include <string>
#include <cmath>

#ifndef CHAINEDMAP_HPP_
#define CHAINEDMAP_HPP_
#include <stdexcept>
#include "Dictionary.hpp"
#include "list.hpp"
using std::pair;
using std::string;
using std::to_string;

#ifndef PRIME_CHECK_
#define PRIME_CHECK_
bool isPrime(long long int n)
{
	for(int i=2; i<=sqrt(n); i++)
		if(n%i==0)
			return false;
	return true;
}
#endif

namespace shukla
{
    template<typename Key, typename Value>
    class ChainedMap : public Dictionary<Key,Value>
    {
        void rehash();
        list<pair<Key,Value> >* m;
        int size;
        int Hash(const Key& key);
    public:
        ChainedMap();
        ChainedMap(const int& num);
        ChainedMap(ChainedMap<Key,Value>& ht);
        ~ChainedMap();
        void printMap();
        Value& operator[](const Key& key);
        virtual bool has(const Key& key);
        virtual void remove(const Key& key);
        virtual Value get(const Key& key);
        virtual void put(const Key& key, const Value& value);
    };
}

using namespace shukla;

template <typename Key,typename Value>
void ChainedMap<Key,Value>::printMap()
{
	std::cout<<"TableIndex\tKey(s)\n";
	for(int i=0; i<size; i++)
	{
		if(m[i].length()!=0)
		{
			std::cout<<"  "<<i<<"\t\t  ";
			node<pair<Key,Value> >* it = m[i].getHead();
			while(it!=nullptr)
			{
				std::cout<<it->getValue().first<<"  ";
				it = it->getNext();
			}
			std::cout<<"\n";
		}
	}
}

template <typename Key,typename Value>
void ChainedMap<Key,Value>::rehash()
{
	int origSize = size;
	size *= 2;
	while(!isPrime(size)) size++;
	list<pair<Key,Value> >* reMap;
	reMap = new list<pair<Key,Value> >[size];

	for(int i=0; i<origSize; i++)
	{
		if(m[i].length()!=0)
		{
			node<pair<Key,Value> >* it = m[i].getHead();
			while(it!=nullptr)
			{
				pair<Key,Value> temp = it->getValue();

				int h = Hash(temp.first);
				node<pair<Key,Value> >* it1 = reMap[h].getHead();
				bool present=false;
				while(!present && it1!=nullptr)
				{
					if(it1->getValue().first==temp.first)
					{
						it1->setValue(temp);
						present=true;
					}
					it1=it1->getNext();
				}
				if(!present) reMap[h].cons(temp);
				it = it->getNext();
			}
		}
	}
	m = reMap;
}

template <typename Key,typename Value>
int ChainedMap<Key,Value>::Hash(const Key& key)
{
	long long int SEED = 2166136261;
	long long int PRIME = 16777619;

    string k = to_string(key);
    long long int hash = SEED;
    for(int i=0;i<k.size();i++)
    	hash = (((k.c_str()[i]-'0')^hash)*PRIME)%size;
    return hash;
}

template <typename Key,typename Value>
ChainedMap<Key,Value>::ChainedMap()
{
    size = 101;
    m = new list<pair<Key,Value> >[size];
}

template <typename Key,typename Value>
ChainedMap<Key,Value>::ChainedMap(const int& num)
{
    size = num;
    m = new list<pair<Key,Value> >[size];
}

template <typename Key,typename Value>
ChainedMap<Key,Value>::ChainedMap(ChainedMap<Key,Value>& ht)
{
    size = ht.size;
    m = new list<pair<Key,Value> >[size];
    for(int i=0; i<size; i++)
        m[i] = ht.m[i];
}

template <typename Key,typename Value>
ChainedMap<Key,Value>::~ChainedMap()
{
    delete [] m;
}

template <typename Key,typename Value>
Value& ChainedMap<Key,Value>::operator[](const Key& key)
{
	int h = Hash(key);
	node<pair<Key,Value> >* it = m[h].getHead();
	bool present=false;
	while(!present && it!=nullptr)
	{
		if(it->getValue().first==key)
			return it->getValue().second;
		it = it->getNext();
	}
	if(!present)
	{
		Value temp;
		m[h].cons({key,temp});
		Value* ans = &m[h].getHead()->getValue().second;
		if(m[h].length()==size/2)
			rehash();
		return *ans;
	}
}

template <typename Key,typename Value>
void ChainedMap<Key,Value>::put(const Key& key, const Value& value)
{
	int h = Hash(key);
	node<pair<Key,Value> >* it = m[h].getHead();
	bool present=false;
	while(!present && it!=nullptr)
	{
		if(it->getValue().first==key)
		{
			it->setValue({key,value});
			present=true;
		}
		it=it->getNext();
	}
	if(!present) m[h].cons({key,value});
	if(m[h].length()==size/2)
		rehash();
}

template <typename Key,typename Value>
bool ChainedMap<Key,Value>::has(const Key& key)
{
	int h = Hash(key);
	node<pair<Key,Value> >* it = m[h].getHead();
	bool present=false;
	while(it!=nullptr)
	{
		if(it->getValue().first==key)
			return true;
		it = it->getNext();
	}
	return false;
}

template <typename Key,typename Value>
void ChainedMap<Key,Value>::remove(const Key& key)
{
	int h = Hash(key);
	Value value;
	node<pair<Key,Value> >* it = m[h].getHead();
	while(it!=nullptr)
	{
		if(it->getValue().first==key)
		{
			value = it->getValue().second;
			m[h].remove({key,value});
			return;
		}
		it = it->getNext();
	}
}

template <typename Key,typename Value>
Value ChainedMap<Key,Value>::get(const Key& key)
{
	int h = Hash(key);
	node<pair<Key,Value> >* it = m[h].getHead();
	bool present=false;
	while(it!=nullptr)
	{
		if(it->getValue().first==key)
			return it->getValue().second;
		it = it->getNext();
	}
	throw std::invalid_argument("Key doesn't exist in the map.\n");
}
#endif