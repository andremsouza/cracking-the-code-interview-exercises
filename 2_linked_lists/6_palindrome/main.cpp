// Implement a function to check if a linked list is a palindrome

// * Solution time complexity: O(n)
// * Solution space complexity: O(n)

#include <forward_list>
#include <iostream>
#include <sstream>
#include <stack>

typedef unsigned char uchar;

using namespace std;

template<typename T>
bool isPalindrome(forward_list<T> t_list) {
  // using an iterative approach with a stack
  stack<T> st;
  auto cur = t_list.begin(), cmp = t_list.begin();

  // push first half of the list into a stack

  while (cmp != t_list.end() && next(cmp) != t_list.end()) {
    st.push(*cur);
    cur = next(cur);
    cmp = next(next(cmp));
  }

  // solving odd number of elements
  if (cmp != t_list.end()) {
    cur = next(cur);
  }

  // popping from stack and comparing to second half of the list
  while (cur != t_list.end()) {
    T top = st.top();
    st.pop();

    if (top != *cur) return false;
    cur = next(cur);
  }
  return true;
}

// int main(int argc, char **argv) { // not using argc/argv
int main() {
  forward_list<int> list;
  auto it = list.before_begin();

  // receiving list from stdin
  // inserting sequentially in list
  string str;
  getline(cin, str);
  istringstream s_stream(str);
  int val;
  while (s_stream >> val) {
    it = list.insert_after(it, val);
  }

  if (list.empty()) {
    cout << "List is empty. Aborting..." << endl;
    return 0;
  }

  bool is_palindrome = isPalindrome(list);

  cout << is_palindrome << endl;

  return 0;
}
