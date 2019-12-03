// Implement an algorithm to find the kth to last element of a singly linked
// list

// * Solution time complexity: O(n)
// * Solution space complexity: O(1)

#include <forward_list>
#include <iostream>

using namespace std;

template <typename T>
typename forward_list<T>::iterator getKthToLast(forward_list<T> &t_list,
                                                const unsigned int t_k) {
  // initialize iterators to nodes in the list
  auto cur = t_list.begin(), cmp = t_list.begin();

  // use cmp to go t_k positions ahead of cur
  for (auto i = 0; i < (int)t_k; i++) {
    if (next(cmp) != t_list.end()) {
      cmp = next(cmp);
    } else {
      return t_list.end();  // if list size smaller than k, return t_list.end()
    }
  }

  // iterate with cur over list until end, keeping exactly k spaces behind cmp
  while (next(cmp) != t_list.end()) {
    cur = next(cur);
    cmp = next(cmp);
  }

  // return kth node from end
  return cur;
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  forward_list<int> list;
  auto it = list.before_begin();
  unsigned int k;
  int val;

  // receiving k from stdin
  cin >> k;
  // receiving list from stdin
  // inserting sequentially in list
  while (cin >> val) {
    it = list.insert_after(it, val);
  }

  if (list.empty()) {
    cout << "List is empty. Aborting..." << endl;
    return 0;
  }

  // writing value to stdout
  auto kth = getKthToLast(list, k);

  if (kth != list.end())
    cout << *getKthToLast(list, k) << endl;
  else
    cout << "List is smaller than " << k + 1 << endl;

  return 0;
}
