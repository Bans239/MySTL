#ifndef BSTREE_HPP
#define BSTREE_HPP 1

#include <iostream>
#include <stdexcept>
#include "Dictionary.hpp"
#include "queue.hpp"
using std::pair;
using std::cout;

namespace shukla {
template <typename Key, typename Value>
class Node
{
public:
    pair<Key,Value> data;
    Node* parent;
    Node* lchild;
    Node* rchild;
};

template <typename Key, typename Value>
class BSTree : public Dictionary<Key, Value> 
{
    Node<Key,Value>* root;
    int count;
public:
    BSTree();
    ~BSTree();

    virtual int getHeight();
    virtual int size();
	virtual void put(const Key& key, const Value& value);
    virtual bool has(const Key& key);
    virtual Value get(const Key& key);
	virtual void remove(const Key& key);
    virtual void print();
    virtual void in_order(void (*fun)(const Key& key, const Value& value));
    virtual void pre_order(void (*fun)(const Key& key, const Value& value));
    virtual void post_order(void (*fun)(const Key& key, const Value& value));
    virtual void print_in_order();
    virtual void print_pre_order();
    virtual void print_post_order();
    virtual void print_level_order();
    virtual Key minimun();
    virtual Key maximum();
    virtual Key successor(const Key& key);
    virtual Key predecessor(const Key& key);

	// Helper Methods
    virtual int height_helper(Node<Key,Value>* root);
    virtual void in_order_helper(Node<Key,Value>* root, void (*fun)(const Key& key, const Value& value));
    virtual void pre_order_helper(Node<Key,Value>* root, void (*fun)(const Key& key, const Value& value));
    virtual void post_order_helper(Node<Key,Value>* root, void (*fun)(const Key& key, const Value& value));
	void setRoot(Node<Key,Value>* z);
    Node<Key,Value>* getRoot();
};

using namespace shukla;

template <typename Key, typename Value>
BSTree<Key,Value>::BSTree()
{
    root = nullptr;
    count = 0;
}

template <typename Key, typename Value>
BSTree<Key,Value>::~BSTree()
{
	delete root;
}

template <typename Key, typename Value>
void BSTree<Key,Value>::setRoot(Node<Key,Value>* z)
{
	root = z;
}    

template <typename Key, typename Value>
Node<Key,Value>* BSTree<Key,Value>::getRoot()
{
	return root;
}    

template <typename Key, typename Value>
int BSTree<Key,Value>::height_helper(Node<Key,Value>* root)
{
    if(root == nullptr) return -1;
    int l = BSTree<Key,Value>::height_helper(root->lchild);
    int r = BSTree<Key,Value>::height_helper(root->rchild);
    return 1+std::max(l,r);
}

template <typename Key, typename Value>
int BSTree<Key,Value>::getHeight()
{
    return BSTree<Key,Value>::height_helper(root);
}

template <typename Key, typename Value>
int BSTree<Key,Value>::size()
{
    return count;
}

template <typename Key, typename Value>
void BSTree<Key,Value>::put(const Key& key, const Value& value)
{
    Node<Key,Value>* temp = new Node<Key,Value>;
    temp->data = {key,value};
    temp->parent = temp->lchild = temp->rchild = nullptr;
      
    if(root == nullptr) root = temp;
    else
    {
        Node<Key,Value> *it, *prev = root;
        if(root->data.first == key) {root->data.second = value;return;}
        else if(root->data.first > key) it = root->lchild;
        else it = root->rchild;

        while(it != nullptr)
        {
            prev = it;
            if(it->data.first == key) {it->data.second = value;return;}
            else if(it->data.first > key) it = it->lchild;
            else it = it->rchild;
        }

        temp->parent = prev;
        if(prev->data.first > key) prev->lchild = temp;
        else prev->rchild = temp;
    }
    count++;
}

template <typename Key, typename Value>
bool BSTree<Key,Value>::has(const Key& key)
{
    Node<Key,Value>* it = root;
    while(it!=nullptr)
    {
        if(it->data.first == key) return true;
        if(it->data.first > key) it = it->lchild;
        else it = it->rchild;
    }
    return false;
}

template <typename Key, typename Value>
Value BSTree<Key,Value>::get(const Key& key)
{
    Node<Key,Value>* it = root;
    while(it!=nullptr)
    {
        if(it->data.first == key) return it->data.second;
        if(it->data.first > key) it = it->lchild;
        else it = it->rchild;
    }
    throw std::invalid_argument("\n\nKey doesn't exist in the tree.\n");
}

template <typename Key, typename Value>
void BSTree<Key,Value>::remove(const Key& key)
{
	// Search for the node<Key,Value>
	Node<Key,Value>* it = root;
    while(it!=nullptr)
    {
    	if(it->data.first == key) break;
    	else if(it->data.first > key) it = it->lchild;
    	else it = it->rchild;
    }
    if(it == nullptr) return;

    // Case 1/2 : No children or 1 child
    if(it->lchild == nullptr || it->rchild == nullptr)
    {
	    if(it->parent == nullptr) 
	    {
	    	root = (it->lchild !=nullptr ? it->lchild:it->rchild);
	    	if(root != nullptr) root->parent = nullptr;
	    }
	    else if(it->parent->lchild == it) 
	    {
	    	it->parent->lchild = (it->lchild!=nullptr ? it->lchild:it->rchild);
	    	if(it->parent->lchild != nullptr) it->parent->lchild->parent = it->parent;
	    }
    	else 
    	{
    		it->parent->rchild = (it->lchild!=nullptr ? it->lchild:it->rchild);
    		if(it->parent->rchild != nullptr) it->parent->rchild->parent = it->parent;
    	}
    	count--;
    	return;
    }
	
	// Case 3 : 2 children
    Node<Key,Value>* succ = it->rchild;
    while(succ->lchild != nullptr) succ = succ->lchild;
    it->data = succ->data;
    if(succ->parent->lchild == succ) 
    {
    	succ->parent->lchild = (succ->lchild!=nullptr ? succ->lchild:succ->rchild);
    	if(succ->parent->lchild != nullptr) succ->parent->lchild->parent = succ->parent;
    }
    else 
    {
    	succ->parent->rchild = (succ->lchild!=nullptr ? succ->lchild:succ->rchild);
    	if(succ->parent->rchild != nullptr) succ->parent->rchild->parent = succ->parent;
    }
    count--;
}

template <typename Key, typename Value>
void BSTree<Key,Value>::print()
{
    print_in_order();
}

template <typename Key, typename Value>
void BSTree<Key,Value>::in_order_helper(Node<Key,Value>* root, void (*fun)(const Key& key, const Value& value))
{
	if(root==nullptr) return;
	in_order_helper(root->lchild,fun);
	fun(root->data.first, root->data.second);
	in_order_helper(root->rchild,fun);
}

template <typename Key, typename Value>
void BSTree<Key,Value>::in_order(void (*fun)(const Key& key, const Value& value))
{
	BSTree<Key,Value>::in_order_helper(root,fun);
}

template <typename Key, typename Value>
void BSTree<Key,Value>::pre_order_helper(Node<Key,Value>* root, void (*fun)(const Key& key, const Value& value))
{
	if(root==nullptr) return;
	fun(root->data.first, root->data.second);
	pre_order_helper(root->lchild,fun);
	pre_order_helper(root->rchild,fun);
}

template <typename Key, typename Value>
void BSTree<Key,Value>::pre_order(void (*fun)(const Key& key, const Value& value))
{	
	BSTree<Key,Value>::pre_order_helper(root,fun);
}

template <typename Key, typename Value>
void BSTree<Key,Value>::post_order_helper(Node<Key,Value>* root, void (*fun)(const Key& key, const Value& value))
{
	if(root==nullptr) return;
	post_order_helper(root->lchild,fun);
	post_order_helper(root->rchild,fun);
	fun(root->data.first, root->data.second);
}

template <typename Key, typename Value>
void BSTree<Key,Value>::post_order(void (*fun)(const Key& key, const Value& value))
{
	BSTree<Key,Value>::post_order_helper(root,fun);
}

template <typename Key, typename Value>
void print_helper(const Key& key, const Value& value)
{
	cout<<"  "<<key<<" : "<<value<<"\n";
}

template <typename Key, typename Value>
void BSTree<Key,Value>::print_in_order()
{
	cout<<"\nINORDER TRAVERSAL\n";
	BSTree<Key,Value>::in_order(print_helper);
	cout<<"\n";
}

template <typename Key, typename Value>
void BSTree<Key,Value>::print_pre_order()
{
	cout<<"\nPREORDER TRAVERSAL\n";
	BSTree<Key,Value>::pre_order(print_helper);
	cout<<"\n";
}

template <typename Key, typename Value>
void BSTree<Key,Value>::print_post_order()
{
	cout<<"\nPOSTORDER TRAVERSAL\n";
	BSTree<Key,Value>::post_order(print_helper);
	cout<<"\n";
}

template <typename Key, typename Value>
void BSTree<Key,Value>::print_level_order()
{
	cout<<"\nLEVELORDER TRAVERSAL\n";
	queue<Node<Key,Value>*> q;
	if(root != nullptr) q.push(root);
	while(!q.empty())
	{
		Node<Key,Value>* temp = q.pop();
		cout<<"  "<<temp->data.first<<" : "<<temp->data.second<<"\n";
		if(temp->lchild != nullptr) q.push(temp->lchild);
		if(temp->rchild != nullptr) q.push(temp->rchild);
	}
	cout<<"\n";
}

template <typename Key, typename Value>
Key BSTree<Key,Value>::minimun()
{
    Node<Key,Value>* it = root;
    if(it == nullptr) throw std::invalid_argument("\n\nTree is empty.\n");
    while(it->lchild != nullptr)
        it = it->lchild;
    return it->data.first;
}

template <typename Key, typename Value>
Key BSTree<Key,Value>::maximum()
{
    Node<Key,Value>* it = root;
    if(it == nullptr) throw std::invalid_argument("\n\nTree is empty.\n");
    while(it->rchild != nullptr)
        it = it->rchild;
    return it->data.first;
}

template <typename Key, typename Value>
Key BSTree<Key,Value>::successor(const Key& key)
{
    Node<Key,Value>* x = root;
    while(x!=nullptr)
    {
        if(x->data.first == key) break;
        if(x->data.first > key) x = x->lchild;
        else x = x->rchild;
    }
    if(x==nullptr) throw std::invalid_argument("\n\nKey doesn't exist in the tree.\n");
    if(x->data.first == maximum()) throw std::invalid_argument("\n\nThe key is the maximum in the tree, hence doesn't have a successor.\n");

    if(x->rchild != nullptr)
    {
        Node<Key,Value>* it = x->rchild;
        while(it->lchild != nullptr) it = it->lchild;
        return it->data.first;	
    }
    Node<Key,Value>* y = x->parent;
    while(y != nullptr && x == y->rchild)
    {
        x = y;
        y = y->parent;
    }
    return y->data.first;
}

template <typename Key, typename Value>
Key BSTree<Key,Value>::predecessor(const Key& key)
{
    Node<Key,Value>* x = root;
    while(x!=nullptr)
    {
        if(x->data.first == key) break;
        if(x->data.first > key) x = x->lchild;
        else x = x->rchild;
    }
    if(x==nullptr) throw std::invalid_argument("\n\nKey doesn't exist in the tree.\n");
    if(x->data.first == minimun()) throw std::invalid_argument("\n\nThe key is the minimum in the tree, hence doesn't have a predecessor.\n");

    if(x->lchild != nullptr)
    {
        Node<Key,Value>* it = x->lchild;
        while(it->rchild != nullptr) it = it->rchild;
        return it->data.first;
    }
    Node<Key,Value>* y = x->parent;
    while(y != nullptr && x == y->lchild)
    {
        x = y;
        y = y->parent;
    }
    return y->data.first;
}
}
#endif