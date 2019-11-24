// Implement an algorithm to find the kth to last element of a singly linked
// list

// * Solution time complexity: O(n)
// * Solution space complexity: O(1)

// ! NOTE: Solution in "linked_list.hpp"

#include <iostream>
#include "linked_list.hpp"

using namespace std;

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  ll::SingleLinkedList<int> list;
  ll::SingleLinkedNode<int> *node;
  int i, k;

  // receive input from stdin
  cin >> k;
  while (cin >> i) {
    list.push_back(i);
  }

  // writing output to stdout
  node = list.getKthToLast(k);
  cout << node->getData() << endl;

  return 0;
}
