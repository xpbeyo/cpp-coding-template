// #include "adder/adder.hpp"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
class CordNode {
public:
  static const string OOB_MSG;
  size_t length;

  CordNode(size_t _length) : length(_length)
  {}
  virtual char operator[](size_t index) = 0;
};
const string CordNode::OOB_MSG = "Index out of bound";

class LeafNode : public CordNode {
public:
  string val;
  LeafNode(string _val) : CordNode(_val.size()), val(_val)
  {
  }
  char operator[](size_t index) override final {
    if (index < 0 || index >= length) {
      throw out_of_range(CordNode::OOB_MSG);
    }
    return val[index];
  }
};

class InternalNode: public CordNode {
public:
  CordNode* left;
  CordNode* right;
  InternalNode(CordNode* _left, CordNode* _right) : CordNode(0), left(_left), right(_right)
  {
    if (left) {
      length += left->length;
    }
    if (right) {
      length += right->length;
    }
  }
  char operator[](size_t index) override final {
    if (index < 0 || index >= length) {
      throw out_of_range(CordNode::OOB_MSG);
    }
    size_t left_size = left == nullptr ? 0 : left->length;
    if (index < left_size) {
      return (*left)[index];
    }
    return (*right)[index - left_size];
  }
};

int main() {
  LeafNode leaf1("ABCDE");
  LeafNode leaf2("FGHIJKLMNO");
  LeafNode leaf3("PQRSTUVWXYZ");
  InternalNode internal1(&leaf2, &leaf3);
  InternalNode internal2(&leaf1, &internal1);
  CordNode& root = internal2;
  for (size_t i = 0; i < root.length; i++) {
    cout << root[i] << endl;
  }
  return 0;
}
