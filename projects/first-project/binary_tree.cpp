#include "binary_tree.h"

BinaryTree::BinaryTree() {}

BinaryTree::BinaryTree(string root_data) {
    root = new Node;
    root->data = root_data;
    root->left = nullptr;
    root->right = nullptr;
}

BinaryTree::BinaryTree(string root_data, BinaryTree left, BinaryTree right) {
    root = new Node;
    root->data = root_data;
    root->left = left.root;
    root->right = right.root;
}

bool BinaryTree::empty() const {
    return root == nullptr;
}

string BinaryTree::data() const {
    if (root != nullptr)
        return root->data;
    else
        return "";
}

BinaryTree BinaryTree::left() const {
    BinaryTree result;
    result.root = root != nullptr ? root->left : nullptr;
    return result;
}

BinaryTree BinaryTree::right() const {
    BinaryTree result;
    result.root = root != nullptr ? root->right : nullptr;
    return result;
}

int BinaryTree::height() const {
    return height(root);
}

int BinaryTree::height(const Node* n) const {
    if (n == nullptr) {
        return 0;
    } else {
        return 1 + max(height(n->left), height(n->right));
    }
}