#include <string>
#include <unordered_map>
#include <cassert>
using namespace std;
class Trie {
private:
  bool is_word;
  unordered_map<char, Trie*> children;

public:
  Trie() : is_word(), children() {}
  void insert(const string& str) {
    Trie* curr_trie = this;
    for (char a: str) {
      if (curr_trie->children.find(a) == curr_trie->children.end()) {
        curr_trie->children[a] = new Trie();
      }
      curr_trie = curr_trie->children[a];
    }
    curr_trie->is_word = true;
  }

  ~Trie() {
    for (auto& child: children) {
      delete child.second;
    }
  }

  bool search(const string& str) {
    Trie* curr_trie = this;
    for (char a: str) {
      if (curr_trie->children.find(a) == curr_trie->children.end()) {
        return false;
      }
      curr_trie = curr_trie->children[a];
    }
    return curr_trie->is_word;
  }
  bool starts_with(const string& str) {
    Trie* curr_trie = this;
    for (char a: str) {
      if (curr_trie->children.find(a) == curr_trie->children.end()) {
        return false;
      }
      curr_trie = curr_trie->children[a];
    }
    return true;
  }
};

int main () {
  string apple_str = "apple";
  Trie trie;
  trie.insert(apple_str);
  assert(trie.search(apple_str));
  assert(!trie.search(apple_str.substr(0, 3)));
  assert(trie.starts_with(apple_str));
  assert(trie.starts_with(apple_str.substr(0, 3)));
  trie.insert(apple_str.substr(0, 3));
  assert(trie.search(apple_str.substr(0, 3)));
  return 0;
}