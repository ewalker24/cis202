#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Node
{
private:
    char character;
    int frequency;
    Node* left;
    Node* right;

    friend class HuffmanTree;
};

class HuffmanTree
{
public:
    HuffmanTree(const unordered_map<char, int>& frequency_map);
    unordered_map<char, string> encoding_map() const;
    string decode(const string& input) const;

private:
    Node* root = nullptr;
    void fill_encoding_map(unordered_map<char, string>& map, string prefix, Node* n) const;
    Node* remove_min(vector<Node*>& nodes);
};

#endif
