#include <iostream>
#include "binary_search_tree.h"

using namespace std;

int main()
{  
   BinarySearchTree t;
   t.insert("D");
   t.insert("B");
   t.insert("A");
   t.insert("C");
   t.insert("F");
   t.insert("E");
   t.insert("I");
   t.insert("G");
   t.insert("H");
   t.insert("J");
   t.erase("A");
   t.erase("B");
   t.erase("F");
   t.erase("D");
   t.print();
   cout << "Expected: C E G H I J" << endl;
   cout << t.count("A") << " " << t.count("J") << endl;
   cout << "Expected: 0 1" << endl;
   return 0;
}
