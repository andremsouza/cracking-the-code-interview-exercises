// Implement an algorithm to delete a node in the middle (i.e., any node but the
// first and last node, not necessarily the exact middle) of a singly linked
// list, given only access to that node.
// EXAMPLE
// Input: the node c from the linked list a->b->c->d->e->f
// Result: nothing is returned, but the new linked list looks like a->b->d->e->f

// * Solution time complexity: O(1)
// * Solution space complexity: O(1)

// ! NOTE: Solution in "linked_list.hpp"

#include <iostream>
#include "linked_list.hpp"

using namespace std;

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  ll::SingleLinkedList<int> list;
  ll::SingleLinkedNode<int> *node = nullptr;
  int i, k;

  // receive input from stdin
  cin >> k;
  while (cin >> i) {
    if (!(--k)) {
      node = list.push_back(i);
    } else {
      list.push_back(i);
    }
  }

  // writing output to stdout
  list.removeNodeFromMiddle(node);
  node = list.getHead();
  while (node != nullptr) {
    cout << node->getData() << " ";
    node = node->getNext();
  }
  cout << endl;

  return 0;
}
