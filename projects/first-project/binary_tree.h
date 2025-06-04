#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>

using namespace std;

class Node
{
private:
    string data;
    Node* left;
    Node* right;

    friend class BinaryTree;
};

class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(string root_data);
    BinaryTree(string root_data, BinaryTree left, BinaryTree right);

    int height() const;
    bool empty() const;
    string data() const;
    BinaryTree left() const;
    BinaryTree right() const;

private:
    Node* root = nullptr;
    int height(const Node* n) const; // Helper
};

#endif