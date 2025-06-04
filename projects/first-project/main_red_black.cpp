#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include "red_black_tree.h" // Assumes RedBlackTree and Node classes are defined here

using namespace std;

void test_from_book() {
   RedBlackTree t;
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
}

int insertion_test(string letters) {
   int count = 0;
   string s = letters;
   do {
      RedBlackTree t;
      for (int i = 0; i < s.length(); i++) {
         t.insert(s.substr(i, 1));
      }
      bool pass = true;
      for (int i = 0; i < s.length(); i++) {
         string e = s.substr(i, 1);
         if (t.count(e) == 0) {
            cout << e << " not inserted" << endl;
            pass = false;
         }
      }
      if (pass) {
         count++;
      } else {
         cout << "Failing for letters " << letters << endl;
      }
   } while (next_permutation(s.begin(), s.end()));
   return count;
}

int size(Node* n) {
   if (n == nullptr) return 0;
   return 1 + size(n->left) + size(n->right);
}

int cost_to_root(Node* n) {
   int c = 0;
   while (n != nullptr) {
      c += n->color;
      n = n->parent;
   }
   return c;
}

Node* copy(Node* n) {
   if (n == nullptr) return nullptr;
   Node* new_node = new Node;
   new_node->data = n->data;
   new_node->color = n->color;
   new_node->set_left_child(copy(n->left));
   new_node->set_right_child(copy(n->right));
   return new_node;
}

Node* mirror(Node* n) {
   if (n == nullptr) return nullptr;
   Node* new_node = new Node;
   new_node->data = n->data;
   new_node->color = n->color;
   new_node->set_left_child(mirror(n->right));
   new_node->set_right_child(mirror(n->left));
   return new_node;
}

Node* full_tree(int depth) {
   if (depth <= 0) return nullptr;
   Node* r = new Node;
   r->color = BLACK;
   r->set_left_child(full_tree(depth - 1));
   r->set_right_child(full_tree(depth - 1));
   return r;
}

void get_nodes(Node* n, vector<Node*>& nodes) {
   if (n == nullptr) return;
   get_nodes(n->left, nodes);
   nodes.push_back(n);
   get_nodes(n->right, nodes);
}

void print_detailed(Node* n, int level) {
   if (n == nullptr) return;
   print_detailed(n->left, level + 1);
   for (int i = 0; i < level; i++) cout << "  ";
   cout << n->data << " " << n->color << endl;
   print_detailed(n->right, level + 1);
}

int populate(RedBlackTree t) {
   vector<Node*> nodes;
   get_nodes(t.root, nodes);
   for (int i = 0; i < nodes.size(); i++) {
      string d = "A";
      d[0] = d[0] + i;
      nodes[i]->data = d;
   }
   return nodes.size();
}

int check_red_black(Node* n, bool is_root, bool report_errors) {
   if (n == nullptr) return 0;
   int nleft = check_red_black(n->left, false, report_errors);
   int nright = check_red_black(n->right, false, report_errors);
   if (nleft == -1 || nright == -1) return -1;
   if (nleft != nright) {
      if (report_errors)
         cout << "Left and right children of " << n->data << " have different black depths" << endl;
      return -1;
   }

   if (n->parent == nullptr) {
      if (!is_root) {
         if (report_errors)
            cout << n->data << " is not root and has no parent" << endl;
         return -1;
      }
      if (n->color != BLACK) {
         if (report_errors)
            cout << "Root " << n->data << " is not black" << endl;
         return -1;
      }
   } else {
      if (is_root) {
         if (report_errors)
            cout << n->data << " is root and has a parent" << endl;
         return -1;
      }
      if (n->color == RED && n->parent->color == RED) {
         if (report_errors)
            cout << "Parent of red " << n->data << " is red" << endl;
         return -1;
      }
   }

   if (n->left && n->left->parent != n) {
      if (report_errors)
         cout << "Left child of " << n->data << " has bad parent link" << endl;
      return -1;
   }
   if (n->right && n->right->parent != n) {
      if (report_errors)
         cout << "Right child of " << n->data << " has bad parent link" << endl;
      return -1;
   }

   if (n->color != RED && n->color != BLACK) {
      if (report_errors)
         cout << n->data << " has invalid color: " << n->color << endl;
      return -1;
   }

   return n->color + nleft;
}

bool check_red_black(RedBlackTree& t, bool report_errors) {
   int result = check_red_black(t.root, true, report_errors);
   if (result == -1) return false;

   vector<Node*> nodes;
   get_nodes(t.root, nodes);
   for (int i = 0; i < nodes.size() - 1; i++) {
      if (nodes[i]->data > nodes[i + 1]->data) { // FIXED comparison
         if (report_errors)
            cout << nodes[i]->data << " is larger than " << nodes[i + 1]->data << endl;
         return false;
      }
   }
   return true;
}

int removal_test(const RedBlackTree& t) {
   int count = 0;
   for (int m = 0; m <= 1; m++) {
      int nodes_to_color = size(t.root) - 2;
      for (int k = 0; k < pow(2, nodes_to_color); k++) {
         RedBlackTree rb;
         rb.root = (m == 0) ? copy(t.root) : mirror(t.root);

         vector<Node*> nodes;
         get_nodes(rb.root, nodes);
         Node* to_delete = nullptr;
         int bits = k;

         for (Node* n : nodes) {
            if (n == rb.root) {
               n->color = BLACK;
            } else if (n->color == BLACK) {
               to_delete = n;
            } else {
               n->color = bits % 2;
               bits /= 2;
            }
         }

         int target_cost = cost_to_root(to_delete);
         for (Node* n : nodes) {
            int cost = target_cost - cost_to_root(n);
            if (n->left == nullptr)
               n->set_left_child(full_tree(cost));
            if (n->right == nullptr)
               n->set_right_child(full_tree(cost));
         }

         int filled_size = populate(rb);

         if (check_red_black(rb, false)) {
            string d = to_delete->data;
            rb.erase(d);
            bool pass = check_red_black(rb, true);
            for (int j = 0; j < filled_size; j++) {
               string s = "A";
               s[0] = s[0] + j;
               if (rb.count(s) == 0 && d != s) {
                  cout << s << " deleted" << endl;
                  pass = false;
               }
            }
            if (rb.count(d) > 0) {
               cout << d << " not deleted" << endl;
               pass = false;
            }
            if (pass) {
               count++;
            } else {
               cout << "Failing tree: " << endl;
               print_detailed(rb.root, 0);
            }
         }
      }
   }
   return count;
}
RedBlackTree removal_test_template() {
   RedBlackTree result;
   Node* n[9];
   for (int i = 0; i < 9; i++) n[i] = new Node;

   result.root = n[7];
   n[7]->set_left_child(n[1]);
   n[7]->set_right_child(n[8]);
   n[1]->set_left_child(n[0]);
   n[1]->set_right_child(n[3]);
   n[3]->set_left_child(n[2]);
   n[3]->set_right_child(n[5]);
   n[5]->set_left_child(n[4]);
   n[5]->set_right_child(n[6]);

   // Set default color (optional - depends on Node constructor)
   for (int i = 0; i < 9; i++) {
      n[i]->color = RED; // or BLACK, adjust depending on your test
   }
   n[2]->color = BLACK; // Example of a specific node's color

   return result;
}

int main() {
   test_from_book();

   int passing = insertion_test("ABCDEFGHIJ");
   cout << passing << " insertion tests passed." << endl;

   passing = removal_test(removal_test_template());
   cout << passing << " removal tests passed." << endl;

   return 0;
}