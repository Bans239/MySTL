#ifndef RBTree_HPP_
#define RBTree_HPP_ 1
#include "BSTree.hpp"

namespace shukla {
template <typename Key, typename Value>
class RBTree : public BSTree<Key, Value> {
public:	
	typedef Node<Key,Value>* node_ptr;
	void put(const Key& key, const Value& value);
	void insertRBFixup(node_ptr root);
	
	void remove(const Key& key);
	void deleteRBFixup(node_ptr x, node_ptr xParent);
	
	void leftRotate(node_ptr z);
	void rightRotate(node_ptr z);
};
}

using namespace shukla;
template <typename Key, typename Value>
void RBTree<Key,Value>::leftRotate(node_ptr z)
{
	node_ptr root = BSTree<Key,Value>::getRoot();
	node_ptr zr = z->rchild;
	
	z->rchild = zr->lchild;
	if(z->rchild != nullptr) z->rchild->parent = z;
	
	zr->parent = z->parent;
	if(z->parent == nullptr) 
	{
		root = zr;
		BSTree<Key,Value>::setRoot(root);
	}
	else if(z == z->parent->lchild) z->parent->lchild = zr;
	else z->parent->rchild = zr;

	zr->lchild = z;
	z->parent = zr;
}

template <typename Key, typename Value>
void RBTree<Key,Value>::rightRotate(node_ptr z)
{
	node_ptr root = BSTree<Key,Value>::getRoot();
	node_ptr zl = z->lchild;
	
	z->lchild = zl->rchild;
	if(z->lchild != nullptr) z->lchild->parent = z;
	
	zl->parent = z->parent;
	if(z->parent == nullptr) 
	{
		root = zl;
		BSTree<Key,Value>::setRoot(root);	
	}
	else if(z == z->parent->rchild) z->parent->rchild = zl;
	else z->parent->lchild = zl;

	zl->rchild = z;
	z->parent = zl;
}

template <typename Key, typename Value>
void RBTree<Key,Value>::put(const Key& key, const Value& value)
{
	BSTree<Key,Value>::put(key,value);
	node_ptr x = BSTree<Key,Value>::getNode(key);
	insertRBFixup(x);
}

template <typename Key, typename Value>
void RBTree<Key,Value>::insertRBFixup(node_ptr z)
{
	node_ptr root = BSTree<Key,Value>::getRoot();
	node_ptr p,gp,uncle;
	while(z != root && z->color == RED && z->parent->color == RED)
	{
		p = z->parent, gp = z->parent->parent;
		if(p == gp->lchild)
		{
			uncle = gp->rchild;
			// Case 1
			if(uncle != nullptr && uncle->color == RED)
			{
				gp->color = RED;
				p->color = BLACK, uncle->color = BLACK;
				z = gp;
			}
			else
			{
				// Case 2
				if(z == p->rchild)
				{
					RBTree<Key,Value>::leftRotate(p);
					z = p;
					p = z->parent;
				}
				// Case 3
				RBTree<Key,Value>::rightRotate(gp);
				std::swap(p->color, gp->color);
				z = p;
			}
		}
		else if(p == gp->rchild)
		{
			uncle = gp->lchild;
			// Case 4
			if(uncle != nullptr && uncle->color == RED)
			{
				gp->color = RED;
				p->color = BLACK, uncle->color = BLACK;
				z = gp;
			}
			else
			{
				// Case 5
				if(z == p->lchild)
				{
					RBTree<Key,Value>::rightRotate(p);
					z = p;
					p = z->parent;
				}
				// Case 6
				RBTree<Key,Value>::leftRotate(gp);
				std::swap(p->color, gp->color);
				z = p;
			}
		}
		root = BSTree<Key,Value>::getRoot();
	}
	root->color = BLACK;
}

template <typename Key, typename Value>
void RBTree<Key,Value>::remove(const Key& key)
{
    node_ptr x, xParent;
    node_ptr it = BSTree<Key,Value>::getNode(key);
    node_ptr root = BSTree<Key,Value>::getRoot();
   	
   	if(it == nullptr) return;
    // Case 1/2 : No children or 1 child
    else if(it->lchild == nullptr || it->rchild == nullptr)
    {
    	xParent = it->parent;
        if(it->parent == nullptr)
        {
            root = (it->lchild !=nullptr ? it->lchild:it->rchild);
            if(root != nullptr) root->parent = nullptr;
            BSTree<Key,Value>::setRoot(root);
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
        BSTree<Key,Value>::decCount();
        x = (it->lchild !=nullptr ? it->lchild:it->rchild);
    }    
    // Case 3 : 2 children
    else
    {
    	Node<Key,Value>* succ = it->rchild;
	    while(succ->lchild != nullptr) succ = succ->lchild;
    	xParent = succ->parent;
        it->data = succ->data;
	    it->color = succ->color;
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
    	BSTree<Key,Value>::decCount();
        x = (succ->lchild!=nullptr ? succ->lchild:succ->rchild);
    }
    if(it->color == BLACK) deleteRBFixup(x,xParent);
    if(root != nullptr) root->color = BLACK;
}

template <typename Key, typename Value>
void RBTree<Key,Value>::deleteRBFixup(node_ptr node, node_ptr nodeParent)
{
	node_ptr root = BSTree<Key,Value>::getRoot();
	while (node != root && (node==nullptr || node->color == BLACK))
	{
		node_ptr s;
		if(nodeParent->lchild == node)
		{
			s = nodeParent->rchild;
			// Case 1
			if(s!=nullptr && s->color == RED)
			{
				s->color = BLACK;
				nodeParent->color = RED;
				leftRotate(nodeParent);
				s = nodeParent->rchild;
			}
			// Case 3
			if((s->lchild == nullptr || s->lchild->color == BLACK) && (s->rchild == nullptr || s->rchild->color == BLACK))
			{
				s->color = RED;
				node = nodeParent;
				nodeParent = node->parent;
			}
			else
			{
				// Case 5
				if(s->rchild == nullptr || s->rchild->color == BLACK)
				{
					s->lchild->color = BLACK;
					s->color = RED;
					rightRotate(s);
					s = nodeParent->rchild;
				}

				// Case 6
				s->color = nodeParent->color;
				nodeParent->color = BLACK;
				s->rchild->color = BLACK;
				leftRotate(nodeParent);
				node = root;
				nodeParent = nullptr;
			}
		}
		else
		{
			s = nodeParent->lchild;
			// Case 2
			if(s!=nullptr && s->color == RED)
			{
				s->color = BLACK;
				nodeParent->color = RED;
				rightRotate(nodeParent);
				s = nodeParent->lchild;
			}
			// Case 4
			if((s->lchild == nullptr || s->lchild->color == BLACK) && (s->rchild == nullptr || s->rchild->color == BLACK))
			{
				s->color = RED;
				node = nodeParent;
				nodeParent = node->parent;
			}
			else
			{
				// Case 7
				if(s->lchild == nullptr || s->lchild->color == BLACK)
				{
					s->rchild->color = BLACK;
					s->color = RED;
					leftRotate(s);
					s = nodeParent->lchild;
				}

				// Case 8
				s->color = nodeParent->color;
				nodeParent->color = BLACK;
				s->lchild->color = BLACK;
				rightRotate(nodeParent);
				node = root;
				nodeParent = nullptr;
			}
		}	
	}
	if(node != nullptr) node->color = BLACK;
}
#endif