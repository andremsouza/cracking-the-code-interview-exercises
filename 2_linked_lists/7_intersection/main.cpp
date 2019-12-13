// Given two (singly) linked lists, determine if the two lists intersect. Return
// the intersecting node. Note that the intersection is defined based on
// reference, not value. That is, if the kth node of the first linked list is
// the exact same node (by reference) as the jth node of the second linked list,
// the  they are intersecting.

// * Solution time complexity: O(n), n is the sum of the number of elements of the two lists
// * Solution space complexity: O(n)

#include "linked_list.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <random>

constexpr double INTERSECTION_PROBABILITY = 0.8;

typedef unsigned char uchar;

using namespace std;

template<typename T>
ll::SingleLinkedNode<T> *findIntersection(ll::SingleLinkedList<T> &t_a, ll::SingleLinkedList<T> &t_b) {
  unordered_map<ll::SingleLinkedNode<T> *, bool> node_map;

  // iterate through list a, adding nodes to map
  for (auto it = t_a.getHead(); it != nullptr; it = it->getNext()) {
    node_map[it] = true;
  }

  // iterate through list b, checking if each node is part of the map. if a node is part of the map, return that node
  for (auto it = t_b.getHead(); it != nullptr; it = it->getNext()) {
    if (node_map.find(it) != node_map.end()) {
      return it;
    }
    node_map[it] = true;
  }

  return nullptr;
}

// int main(int argc, char **argv) { // not using argc/argv
int main() {
  ll::SingleLinkedList<int> list_a, list_b;
  ll::SingleLinkedNode<int> *intersection = nullptr, *node = nullptr, *out_node = nullptr;
  int val = 0;

  // initialize random with seed
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> dist(0.0, 1.0);

  // receiving list from stdin
  // inserting sequentially in list
  // randomly select a node for intersection
  string str_a;
  getline(cin, str_a);
  istringstream s_stream_a(str_a);
  while (s_stream_a >> val) {
    node = list_a.push_back(val);
    auto r = dist(mt);
    if (r > INTERSECTION_PROBABILITY) {
      intersection = node;
    }

  }

  // receiving list from stdin
  // inserting sequentially in list
  //
  string str_b;
  getline(cin, str_b);
  istringstream s_stream_b(str_b);
  while (s_stream_b >> val) {
    node = list_b.push_back(val);
  }

  if (intersection != nullptr && node != nullptr) {
    node->setNext(intersection);
  }

  if (list_a.getHead() == nullptr || list_b.getHead() == nullptr) {
    cout << "List is empty. Aborting..." << endl;
    return 0;
  }

  cout << "List B: ";
  out_node = list_b.getHead();
  while (out_node != nullptr) {
    cout << out_node->getData() << " ";
    out_node = out_node->getNext();
  }
  cout << endl;

  auto it = findIntersection(list_a, list_b);

  if (it == nullptr) {
    cout << "No found intersection between list A and list B" << endl;
  } else {
    cout << "Intersection found. Value of node: " << it->getData() << endl;
  }

  // remove intersection to avoid double free
  node->setNext(nullptr);

  return 0;
}
