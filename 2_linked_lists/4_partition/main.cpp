// Write code to partition a linked list around a value x, such that all nodes
// less than x come before all nodes greater than or equal to x. If x is
// contained within the list, the values of x only need to be after the elements
// less than x (see below). The partition element x can appear anywhere in the
// "right partition"; it does not need to appear between the left and right
// partitions.
// EXAMPLE
// Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition=5]
// Output 3-> 1 -> 2 -> 10 -> 5 -> 5 -> 8

// * Solution time complexity: O(n)
// * Solution space complexity: O(1)

// ! NOTE: Solution in "linked_list.hpp"

#include <iostream>
#include "linked_list.hpp"

using namespace std;

// int main(int argc, char **argv) { // not using argc/argv
int main() {
  ll::SingleLinkedList<int> list;
  ll::SingleLinkedNode<int> *node = nullptr;
  int i = 0, k = 0;

  // receive input from stdin
  cin >> k;
  while (cin >> i) {
    list.push_back(i);
  }

  // writing output to stdout
  list.partitionByValue(k);
  node = list.getHead();
  while (node != nullptr) {
    cout << node->getData() << " ";
    node = node->getNext();
  }
  cout << endl;

  return 0;
}
