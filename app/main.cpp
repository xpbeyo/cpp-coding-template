// #include "adder/adder.hpp"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
class CordNode {
public:
  CordNode* left;
  CordNode* right;
  string val;
  size_t length;

  CordNode(string const& _val) : left(nullptr), right(nullptr), val(_val), length(_val.size())
  {
  }
  CordNode(CordNode* _left, CordNode* _right) : left(_left), right(_right), val(), length(0)
  {
    if (left != nullptr) {
      length += left->length;
    }
    if (right != nullptr) {
      length += right->length;
    }
  }
  bool is_leaf() {
    return left == nullptr && right == nullptr;
  }

  char operator[](size_t index) {
    if (index < 0 || index >= length) {
      return '#';
    }
    if (is_leaf()) {
      return val[index];
    }
    size_t left_size = left == nullptr ? 0 : left->length;
    if (index < left_size) {
      return (*left)[index];
    }
    return (*right)[index - left_size];
  }
};

int main() {
  CordNode leaf1("ABCDE");
  CordNode leaf2("FGHIJKLMNO");
  CordNode leaf3("PQRSTUVWXYZ");
  CordNode internal1(&leaf2, &leaf3);
  CordNode internal2(&leaf1, &internal1);
  CordNode& root = internal2;
  for (size_t i = 0; i < root.length; i++) {
    cout << root[i] << endl;
  }
  return 0;
}
