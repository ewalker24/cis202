#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>

using namespace std;

const int BLACK = 1;
const int RED = 0;
const int NEGATIVE_RED = -1;
const int DOUBLE_BLACK = 2;

class Node
{
public:   

   Node();
      
private:
   
   void add_node(Node* new_node);
public: // These members are public for testing  
   
   void set_left_child(Node* child);

   void set_right_child(Node* child);

   string data;
   Node* left;
   Node* right;
   Node* parent;
   int color;
   
friend class RedBlackTree;
};

class RedBlackTree
{  
public: 
  
   RedBlackTree();
 
   void insert(string element); 

   int count(string element) const;
  
   void erase(string element);

   void print() const;
   
private:
   
   void print(Node* parent) const;
   
   void replace_with(Node* to_be_replaced, Node* replacement);

   void fix_after_add(Node* new_node);

   void fix_before_remove(Node* to_be_removed);
   
   void bubble_up(Node* parent);

   bool bubble_up_fix(Node* child);
  
   void fix_double_red(Node* child);
   
   void fix_negative_red(Node* neg_red);

public:
   Node* root; 
};

#endif