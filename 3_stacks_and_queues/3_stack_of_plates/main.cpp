// Imagine a (literal) stack of plates. If the stack gets too high, it might
// topple. Therefore, in real life, we would likely start a new stack when the
// previous stack exceeds some threshold. Implement a data structure SetOfStacks
// that mimics this. SetOfStacks should be composed of several stacks and should
// create a new stack once the previous one exceeds capacity. SetOfStacks.push()
// and SetOfStacks.pop() should behave identically to a single stack (that is,
// pop() should return the same values as it would if there were just a single
// stack).
// FOLLOW UP
// Implement a function popAt(int index) which performs a pop operation on a
// specific sub-stack.

// * Solution: maintain a list of stacks. push and pop only from the last stack
// * on the list. Create or delete stacks when necessary
// * Follow up: the popAt method may leave empty spaces in the structure. A
// * solution would be to rollover the elements
// * from the subsequents stacks, filling up the empty spaces, but this is
// * computationally expensive.

#include <deque>
#include <iostream>
#include <stack>

template <typename T>
class SetOfStacks {
 private:
  std::deque<std::stack<T>> m_arr;  // set of stacks
  unsigned int m_threshold;         // maximum size for each stack

 public:
  SetOfStacks(unsigned int t_threshold);

  T top();
  T top(unsigned int t_index);
  bool empty();                      // check if all stacks are empty
  bool empty(unsigned int t_index);  // check if a specific stack is empty
  unsigned int length();             // number of stacks in the set
  unsigned int size();               // number of all elements in the set
  unsigned int size(unsigned int t_index);  // number of elements in a stack
  void push(T t_data);
  void pop();
  void popAt(unsigned int t_index);  // pop operation on a specific sub-stack
};

template <typename T>
SetOfStacks<T>::SetOfStacks(unsigned int t_threshold)
    : m_threshold(t_threshold) {
  // initialize first empty stack
  m_arr.push_back(std::stack<T>());
}

template <typename T>
T SetOfStacks<T>::top() {
  return m_arr.back().top();
}

template <typename T>
T SetOfStacks<T>::top(unsigned int t_index) {
  return m_arr.at(t_index).top();
}

template <typename T>
bool SetOfStacks<T>::empty() {
  return m_arr.size() == 1 && m_arr.back().empty();
}

template <typename T>
bool SetOfStacks<T>::empty(unsigned int t_index) {
  return m_arr.at(t_index).empty();
}

template <typename T>
unsigned int SetOfStacks<T>::length() {
  return m_arr.size();
}

template <typename T>
unsigned int SetOfStacks<T>::size() {
  unsigned int sum = 0;
  for (const auto &i : m_arr) {
    sum += i.size();
  }
  return sum;
}

template <typename T>
unsigned int SetOfStacks<T>::size(unsigned int t_index) {
  return m_arr.at(t_index).size();
}

template <typename T>
void SetOfStacks<T>::push(T t_data) {
  // create new stack if last stack is at the threshold
  if (m_arr.back().size() >= m_threshold) {
    m_arr.push_back(std::stack<T>());
  }
  // push data to last stack in set
  m_arr.back().push(t_data);
}

template <typename T>
void SetOfStacks<T>::pop() {
  // pop from last stack
  m_arr.back().pop();

  // if last stack is empty, delete it from the set
  // conserve first stack
  if (m_arr.back().empty() && m_arr.size() > 1) {
    m_arr.pop_back();
  }
}

template <typename T>
void SetOfStacks<T>::popAt(unsigned int t_index) {
  // pop from stack at t_index
  m_arr.at(t_index).pop();

  // check if stack at t_index is empty. If empty, erase it
  // conserve first stack
  if (m_arr.at(t_index).empty() && m_arr.size() > 1) {
    m_arr.erase(m_arr.begin() + t_index);
  }
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  unsigned int threshold = 7, inserts = 100;
  SetOfStacks<int> arr(threshold);

  std::cout << "Inserting " << inserts
            << " elements into SetOfStacks, with threshold = " << threshold
            << std::endl;
  for (int i = 0; i < (int)inserts; i++) {
    arr.push(i);
  }
  std::cout << "# of stacks: " << arr.length() << std::endl;
  std::cout << "Top element: " << arr.top() << std::endl;
  std::cout << "# of elements: " << arr.size() << std::endl;
  std::cout << "# of elements in last stack: " << arr.size(arr.length() - 1)
            << std::endl;
  std::cout << "Removing last stack from set" << std::endl;
  for (auto i = 0, j = (int)arr.size(arr.length() - 1); i < j; i++) {
    arr.pop();
  }
  std::cout << "# of stacks: " << arr.length() << std::endl;
  std::cout << "Top element: " << arr.top() << std::endl;
  std::cout << "# of elements: " << arr.size() << std::endl;
  std::cout << "# of elements in last stack: " << arr.size(arr.length() - 1)
            << std::endl;
  std::cout << "Removing element from specific set" << std::endl;
  arr.popAt(0);
  std::cout << "# of stacks: " << arr.length() << std::endl;
  std::cout << "Top element: " << arr.top() << std::endl;
  std::cout << "# of elements: " << arr.size() << std::endl;
  std::cout << "# of elements in last stack: " << arr.size(arr.length() - 1)
            << std::endl;
  return 0;
}
