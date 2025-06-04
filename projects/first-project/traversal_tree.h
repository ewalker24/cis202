#ifndef traversal_tree_h

#include <vector>
#include <queue>
#include <string>

using namespace std;

class Visitor
{
public:   
  
   virtual void visit(string data);
};

class BreadthFirstIterator;

class Node
{
private:
 
   int size() const;

   string data;
   vector<Node*> children;
friend class BreadthFirstIterator;
friend class Tree;
};

class Tree
{
public:
  
   Tree();

   Tree(string root_data);

   void add_subtree(const Tree& subtree);

   int size() const;

   void preorder(Visitor& v) const;
   
   void postorder(Visitor& v) const;

   void breadth_first(Visitor& v) const;

   BreadthFirstIterator begin() const;
 
   BreadthFirstIterator end() const;

 private:   
  
   void preorder(Node* n, Visitor& v) const;

   void postorder(Node* n, Visitor& v) const;
   
   Node* root;
};

class BreadthFirstIterator
{
 public:
 
   BreadthFirstIterator(Node* root);
  
   string get() const;
  
   void next();
   bool equals(const BreadthFirstIterator& other) const;
   
private:
   queue<Node*> q;
};

#endif