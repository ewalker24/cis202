#include "huffman_tree.h"
#include <iostream>
#include <unordered_map>

using namespace std;

// Simple encode function
string encode(const string& text, const unordered_map<char, string>& map) {
    string result;
    for (char c : text) {
        result += map.at(c);
    }
    return result;
}

int main() {
    unordered_map<char, int> frequency_map;
    frequency_map['A'] = 2089;  frequency_map['E'] = 576;
    frequency_map['H'] = 357;   frequency_map['I'] = 671;
    frequency_map['K'] = 849;   frequency_map['L'] = 354;
    frequency_map['M'] = 259;   frequency_map['N'] = 660;
    frequency_map['O'] = 844;   frequency_map['P'] = 239;
    frequency_map['U'] = 472;   frequency_map['W'] = 74;
    frequency_map['\''] = 541;

    HuffmanTree tree(frequency_map);
    unordered_map<char, string> enc_map = tree.encoding_map();

    string message = "ALOHA";
    string encoded = encode(message, enc_map);
    cout << "Encoded: " << encoded << endl;

    string decoded = tree.decode(encoded);
    cout << "Decoded: " << decoded << endl;

    return 0;
}