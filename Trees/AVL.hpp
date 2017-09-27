#ifndef AVL_HPP
#define AVL_HPP 1

#include "BSTree.hpp"

namespace shukla {
template <typename Key, typename Value>
class AVL : public BSTree<Key, Value>
{
public:
	virtual void put(const Key& key, const Value& value);
	virtual void remove(const Key& key);
    int getBalance(Node<Key,Value>* z);
  	void rightRotate(Node<Key,Value>* z);
   	void leftRotate(Node<Key,Value>* z);
    void doBalance(Node<Key,Value>* z);
};

using namespace shukla;

template <typename Key, typename Value>
void AVL<Key,Value>::put(const Key& key,const Value& value)
{
	BSTree<Key,Value>::put(key,value);
	Node<Key,Value>* x = BSTree<Key,Value>::getRoot();
    while(x!=nullptr)
    {
        if(x->data.first == key) break;
        if(x->data.first > key) x = x->lchild;
        else x = x->rchild;
    }
    while(x != nullptr)
    {
    	if(getBalance(x)>1 || getBalance(x)<-1) doBalance(x);
    	x = x->parent;
    }
}

template <typename Key, typename Value>
void AVL<Key,Value>::remove(const Key& key)
{
	Key temp = BSTree<Key,Value>::maximum();
	if(temp != key) temp = BSTree<Key,Value>::successor(key);	
	Node<Key,Value>* x = BSTree<Key,Value>::getRoot();

	while(x!=nullptr)
    {
        if(x->data.first == temp) break;
        if(x->data.first > temp) x = x->lchild;
        else x = x->rchild;
    }
    if(x == nullptr) return;
	x = x->parent;
	
	BSTree<Key,Value>::remove(key);		
	
	while(x != nullptr)
    {
    	if(getBalance(x)>1 || getBalance(x)<-1) doBalance(x);
    	x = x->parent;
    }
}

template <typename Key, typename Value>
void AVL<Key,Value>::doBalance(Node<Key,Value>* z)
{
	if(getBalance(z)==2)
	{
		// Case 1/3
		if(getBalance(z->lchild)==1) rightRotate(z);
		else
		{	
			leftRotate(z->lchild);
			rightRotate(z);
		}
	}
	else if(getBalance(z)==-2)
	{
		// Case 2/4
		if(getBalance(z->rchild)==-1) leftRotate(z);
		else
		{
			rightRotate(z->rchild);
			leftRotate(z);
		}
	}
}

template <typename Key, typename Value>
void AVL<Key,Value>::rightRotate(Node<Key,Value>* z)
{
	Node<Key,Value>* y = z->lchild;
	Node<Key,Value>* p = z->parent;
	y->parent = p;

	if(p!=nullptr && p->rchild == z) p->rchild = y;
	else if(p!=nullptr && p->lchild == z) p->lchild = y;
	Node<Key,Value>* yr = y->rchild;
	z->parent = y;
	y->rchild = z;
	z->lchild = yr;
	if(yr != nullptr) yr->parent = z;
	if(p == nullptr) BSTree<Key,Value>::setRoot(y);	
}

template <typename Key, typename Value>
void AVL<Key,Value>::leftRotate(Node<Key,Value>* z)
{
	Node<Key,Value>* y = z->rchild;
	Node<Key,Value>* p = z->parent;
	y->parent = p;

	if(p!=nullptr && p->rchild == z) p->rchild = y;
	else if(p!=nullptr && p->lchild == z) p->lchild = y;
	Node<Key,Value>* yl = y->lchild;
	z->parent = y;
	y->lchild = z;
	z->rchild = yl;
	if(yl != nullptr) yl->parent = z;
	if(p == nullptr) BSTree<Key,Value>::setRoot(y);
}

template <typename Key, typename Value>
int AVL<Key,Value>::getBalance(Node<Key,Value>* z)
{
	int l = BSTree<Key,Value>::height_helper(z->lchild);
	int r = BSTree<Key,Value>::height_helper(z->rchild);
	return l-r;
}
}
#endif