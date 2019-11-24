// Write code to remove duplicates from an unsorted linked list
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

// * Solution 1 time complexity: O(n)
// * Solution 1 space complexity: O(n)

// * Solution 2 time complexity: O(n^2)
// * Solution 2 space complexity: O(1)

// ! NOTE: Solution in "linked_list.hpp"

#include <iostream>
#include "linked_list.hpp"

using namespace std;

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  ll::SingleLinkedList<int> list_1, list_2;
  ll::SingleLinkedNode<int> *node;
  int i;

  // receive input from stdin
  while (cin >> i) {
    list_1.push_back(i);
    list_2.push_back(i);
  }

  // removing duplicates
  list_1.removeDupsHash();
  list_2.removeDupsPointers();
  // writing output to stdout
  cout << "List 1 (removal with hash mapping): ";
  node = list_1.getHead();
  while (node != nullptr) {
    cout << node->getData() << " ";
    node = node->getNext();
  }
  cout << endl;

  // writing output to stdout
  cout << "List 2 (removal with pointers only): ";
  node = list_2.getHead();
  while (node != nullptr) {
    cout << node->getData() << " ";
    node = node->getNext();
  }
  cout << endl;

  return 0;
}
