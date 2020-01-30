// Given a circular linked list, implement an algorithm that returns the node at
// the beginning of the loop

// * Solution time complexity: O(n)
// * Solution space complexity: O(n)

#include <iostream>
#include <random>
#include <sstream>
#include <unordered_map>

#include "linked_list.hpp"

constexpr double LOOP_PROBABILITY = 0.8;

typedef unsigned char uchar;

using namespace std;

template <typename T>
ll::SingleLinkedNode<T> *findLoop(ll::SingleLinkedList<T> &t_list) {
  auto cur = t_list.getHead();
  unordered_map<ll::SingleLinkedNode<T> *, bool> node_map;

  while (cur != nullptr) {
    if (node_map.find(cur) != node_map.end()) {
      return cur;
    }
    node_map[cur] = true;
    cur = cur->getNext();
  }

  return nullptr;
}

// int main(int argc, char **argv) { // not using argc/argv
int main() {
  ll::SingleLinkedList<int> list;
  ll::SingleLinkedNode<int> *loop_node = nullptr, *node = nullptr,
                            *out_node = nullptr;
  int val = 0, count = 0;

  // initialize random with seed
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> dist(0.0, 1.0);

  // receiving list from stdin
  // inserting sequentially in list
  // randomly select a node for loop_node
  string str_a;
  getline(cin, str_a);
  istringstream s_stream_a(str_a);
  while (s_stream_a >> val) {
    node = list.push_back(val);
    auto r = dist(mt);
    if (r > LOOP_PROBABILITY) {
      loop_node = node;
    }
    count++;
  }
  count *= 2;

  if (list.getHead() == nullptr) {
    cout << "List is empty. Aborting..." << endl;
    return 0;
  }

  // making loop in list
  node->setNext(loop_node);

  cout << "List: ";
  out_node = list.getHead();
  while (out_node != nullptr && count--) {
    cout << out_node->getData() << " ";
    out_node = out_node->getNext();
  }
  cout << endl;

  auto it = findLoop(list);

  if (it == nullptr) {
    cout << "No found loop" << endl;
  } else {
    cout << "Loop found. Value of first node: " << it->getData() << endl;
  }

  // remove loop to avoid double free
  node->setNext(nullptr);

  return 0;
}
