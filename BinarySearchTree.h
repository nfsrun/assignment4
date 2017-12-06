/*
 * BinarySearchTree.h
 *
 *  Created on: Oct 30, 2017
 *  Revised on: Dec 06, 2017
 *      Author: fatma.serce
 *      Edited: Kevin Tran
 *      Binary Search Tree has been revised to remove unused methods and to
 *      implement various improvements to make the Binary Search Tree more
 *      efficient when traversing.
 */

#ifndef ASSIGNMENT4_BINARYSEARCHTREE_H_
#define ASSIGNMENT4_BINARYSEARCHTREE_H_
#include <iostream>
using namespace std;

template <class T>
struct node{
	T data;
	node<T>* left;
	node<T>* right;
public:
    friend ostream& operator<<(ostream& os, node<T> const& n){
        return os << n.data;
    }
};

template <class T>
class BinarySearchTree{
private:
	node<T>* root;

    //boolean to stop a traversing early when using the filter functions
    bool stop=false;
    void inOrderT(node<T>*, string&, T);
	void destroy(node<T>*);
	int treeNodeCount(node<T>*);
	int treeLeaveCount(node<T>*);
	void treeInsert(node<T>*&, T&);
    node<T>* treeSearch(node<T>*, T&);

public:
	BinarySearchTree();
    bool isEmpty();
	string inOrder(string s="", T item = T()){
        inOrderT(this->root, s, item);
        this->stop=false;
        return s;
    }
	void insert(T& item){treeInsert(root, item);}
	T search(T& item){
        T output = T();
        node<T>* check = treeSearch(root,item);
        if(check!=NULL){
            output = check->data;
        }
        return output;
    }

	~BinarySearchTree(){destroy(root);}
};

//default constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree(){
	root = NULL;
}

//isEmpty method checks to see if the tree's root is empty (is NULL).
template <class T>
bool BinarySearchTree<T>::isEmpty() {
    return this->root==NULL;
}

//traversal will ensure that it will stop outputting more items once the item
//has been reached. It will not print the reached item. This utilizes an extra
//variable not oftenly seen in Binary Tree Searching so that it can stop early
//once it reaches a target item (this is for use in the filter function).
template <class T>
void BinarySearchTree<T>::inOrderT(node<T>* p, string& s, T target){
	if(p!=NULL && stop==false){
        if(this->stop==false) {
            inOrderT(p->left, s, target);
        }
        if(target==p->data){
            this->stop=false;
        }else {
            s += p->data;
        }
        if(this->stop==false) {
            inOrderT(p->right, s, target);
        }
	}
}

//treeNodeCount counts the number of nodes within a tree.
template <class T>
int BinarySearchTree<T>::treeNodeCount(node<T>* p){
	if(p==NULL)
		return 0;
	else
		return 1 + treeNodeCount(p->left) + treeNodeCount(p->right);
}

//treeLeaveCount counts the number of leaves within a tree.
template <class T>
int BinarySearchTree<T>::treeLeaveCount(node<T>* p){
	if(p==NULL)
		return 0;
	else if(p->left==NULL && p->right==NULL)
		return 1;
	else
		return treeLeaveCount(p->left) + treeLeaveCount(p->right);
}

//destroy function destroys the data in each node and  all of its children and
//then nullifies the pointer.
template <class T>
void BinarySearchTree<T>::destroy(node<T>* p){
	if(p!= NULL){
		destroy(p->left);
		destroy(p->right);
		delete p;
		p= NULL;
	}
}

//treeInsert function goes through the nodes based on its value against other
//nodes and slowly gets to a null spot to copy its in formation to a null leaf
//so that null leaf can be a normal leaf.
template <class T>
void BinarySearchTree<T>::treeInsert(node<T>*& p, T& item){
	if(p == NULL){
		p = new node<T>;
		p->data = item;
		p->left = p->right = NULL;
	}
	else if(item<p->data){
		treeInsert(p->left, item);
	}else{
		treeInsert(p->right, item);
	}

}

//treeSearch function traverses through the tree (in order from a node at
//address p) to find the data in which the function is trying to find (under
//address of item). If it finds it, it will return the template object itself.
template <class T>
node<T>* BinarySearchTree<T>::treeSearch(node<T>* p, T& item) {
    if (p == NULL)
        return NULL;
    else if (item < p->data)
        return treeSearch(p->left, item);
    else if (item > p->data)
        return treeSearch(p->right, item);
    else {
        return p;
    }
}

#endif /* ASSIGNMENT4_BINARYSEARCHTREE_H_ */
