#include "tree.h"

Tree::Tree() {}

Tree::Tree(string root_data) {
    root = new Node;
    root->data = root_data;
}

void Tree::add_subtree(const Tree& subtree) {
    if (root != nullptr && subtree.root != nullptr) {
        root->children.push_back(subtree.root);
    }
}

int Tree::size() const {
    if (root == nullptr) {
        return 0;
    } else {
        return root->size();
    }
}

void Tree::print() const {
    if (root != nullptr) {
        root->print();
    }
}

int Node::size() const {
    int sum = 0;
    for (Node* child : children) {
        sum += child->size();
    }
    return 1 + sum;
}

void Node::print() const {
    cout << data << endl;
    for (Node* np : children) {
        np->print();
    }
}
