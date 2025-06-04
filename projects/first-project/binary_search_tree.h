#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <iostream>

using namespace std;

class Node
{
private:
   string data;
   Node* left;
   Node* right;
friend class BinarySearchTree;   
};   
class BinarySearchTree
{
public: 
   BinarySearchTree();
void insert(string element);
   int count(string element) const;  
    void erase(string element);
     void print() const;

private:   
  void print(Node* parent) const;
   void add_node(Node* parent, Node* new_node) const;

   Node* root;
};

#endif
