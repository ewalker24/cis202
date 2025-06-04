#include "huffman_tree.h"
#include <algorithm>
#include <iostream>

Node* HuffmanTree::remove_min(vector<Node*>& nodes) {
    auto min_iter = min_element(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->frequency < b->frequency;
    });
    Node* min_node = *min_iter;
    nodes.erase(min_iter);
    return min_node;
}

HuffmanTree::HuffmanTree(const unordered_map<char, int>& frequency_map) {
    vector<Node*> nodes;

    for (auto iter = frequency_map.begin(); iter != frequency_map.end(); ++iter) {
        Node* new_node = new Node;
        new_node->character = iter->first;
        new_node->frequency = iter->second;
        new_node->left = nullptr;
        new_node->right = nullptr;
        nodes.push_back(new_node);
    }

    while (nodes.size() > 1) {
        Node* smallest = remove_min(nodes);
        Node* next_smallest = remove_min(nodes);
        Node* new_node = new Node;
        new_node->character = '\0';
        new_node->frequency = smallest->frequency + next_smallest->frequency;
        new_node->left = smallest;
        new_node->right = next_smallest;
        nodes.push_back(new_node);
    }

    if (!nodes.empty()) {
        root = nodes[0];
    }
}

string HuffmanTree::decode(const string& input) const {
    string result;
    Node* n = root;

    for (char ch : input) {
        if (ch == '0') n = n->left;
        else           n = n->right;

        if (n->left == nullptr && n->right == nullptr) {
            result += n->character;
            n = root;
        }
    }

    return result;
}

unordered_map<char, string> HuffmanTree::encoding_map() const {
    unordered_map<char, string> map;
    fill_encoding_map(map, "", root);
    return map;
}

void HuffmanTree::fill_encoding_map(unordered_map<char, string>& map, string prefix, Node* n) const {
    if (n == nullptr) return;

    if (n->left == nullptr && n->right == nullptr) {
        map[n->character] = prefix;
    } else {
        fill_encoding_map(map, prefix + "0", n->left);
        fill_encoding_map(map, prefix + "1", n->right);
    }
}