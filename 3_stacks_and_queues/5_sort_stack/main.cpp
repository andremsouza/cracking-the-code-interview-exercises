// Write a program to sort a stack such that the smallest items are on the top.
// You can use an additional temporary stack, but you may not copy the elements
// into any other data structure (such as an array). The stack supports the
// following operations: push, pop, peek, and isEmpty.

// * Solution time complexity: O(n^2)
// * Solution space complexity: O(n)

#include <iostream>
#include <stack>

template <typename T>
void sortStack(std::stack<T>& t_stack) {
  // if t_stack is empty, return
  if (t_stack.empty()) {
    return;
  }
  std::stack<T> tmp_stack;

  // pop first element from t_stack into tmp_stack
  tmp_stack.push(t_stack.top());
  t_stack.pop();

  // insert values in sorted order in temporary stack
  while (!t_stack.empty()) {
    // get top value from primary stack
    T tmp = t_stack.top();
    t_stack.pop();
    // while tmp = top value from primary stack is smaller than top value of
    // tmp_stack, pop top value from tmp_stack into primary stack
    while (tmp < tmp_stack.top()) {
      t_stack.push(tmp_stack.top());
      tmp_stack.pop();
    }
    // push tmp value into tmp_stack
    tmp_stack.push(tmp);
  }

  // swap values from temporary stack into primary stack
  while (!tmp_stack.empty()) {
    t_stack.push(tmp_stack.top());
    tmp_stack.pop();
  }
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  // testing implementation
  std::stack<int> st({5, 4, 3, 6, 7, 8, 5, 5, 5, 1, 10, 9, 2, 0});
  sortStack(st);
  while (!st.empty()) {
    std::cout << st.top() << std::endl;
    st.pop();
  }
  return 0;
}
