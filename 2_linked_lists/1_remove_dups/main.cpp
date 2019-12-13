// Write code to remove duplicates from an unsorted linked list
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

// * Solution 1 time complexity: O(n)
// * Solution 1 space complexity: O(n)

// * Solution 2 time complexity: O(n^2)
// * Solution 2 space complexity: O(1)

#include <forward_list>
#include <iostream>
#include <unordered_map>

using namespace std;

template <typename T>
void removeListDupsHash(forward_list<T> &t_list) {
  // using a hash map to store duplicates
  unordered_map<T, bool> duplicate_map;
  auto it = t_list.begin();

  // iterating through list, checking duplicates in hash map
  duplicate_map[*(t_list.begin())] = true;
  while (next(it) != t_list.end()) {
    if (duplicate_map.find(*(next(it))) != duplicate_map.end()) {
      t_list.erase_after(it);
    } else {
      duplicate_map[*(next(it))] = true;
      it = next(it);
    }
  }
}

template <typename T>
void removeListDupsPointers(forward_list<T> &t_list) {
  // using only pointers to remove duplicates
  auto cur = t_list.begin();

  while (cur != t_list.end()) {
    auto cmp = cur;
    while (next(cmp) != t_list.end()) {
      if (*next(cmp) == *cur) {
        t_list.erase_after(cmp);
      } else {
        cmp = next(cmp);
      }
    }
    cur = next(cur);
  }
}

// int main(int argc, char **argv) { // not using argc/argv
int main() {
  forward_list<int> list;
  auto it = list.before_begin();
  int val = 0;

  // receiving list from stdin
  // inserting sequentially in list
  while (cin >> val) {
    it = list.insert_after(it, val);
  }

  if (list.empty()) {
    cout << "List is empty. Aborting..." << endl;
    return 0;
  }

  removeListDupsHash(list);
  // removeListDupsPointers(list);

  for (const auto &i : list) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
