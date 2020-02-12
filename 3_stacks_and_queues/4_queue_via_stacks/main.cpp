// Implement a MyQueue class which implements a queue using two stacks.

// * Solution: Maintain two stacks. Always push to stack 1. Always pop from
// * stack 2.
// * Swap elements between stacks only when necessary.

#include <iostream>
#include <stack>
#include <stdexcept>

template <typename T>
class MyQueue {
 private:
  std::stack<T> m_stack_1, m_stack_2;

  void swap();  // transfer elements between stack 1 and stack 2

 public:
  T& front();
  T& back();
  bool empty();
  unsigned int size();
  void push(T t_data);
  void pop();
};

template <typename T>
void MyQueue<T>::swap() {
  if (m_stack_1.empty()) {
    // transfer elements from stack 2 to stack 1
    while (!m_stack_2.empty()) {
      m_stack_1.push(m_stack_2.top());
      m_stack_2.pop();
    }
  } else if (m_stack_2.empty()) {
    // transfer elements from stack 1 to stack 2
    while (!m_stack_1.empty()) {
      m_stack_2.push(m_stack_1.top());
      m_stack_1.pop();
    }
  } else {
    // execution should never reach this point
    throw std::logic_error(
        "At least one stack of a MyQueue instance must be empty at all times.");
  }
}

template <typename T>
T& MyQueue<T>::front() {
  // if stack 2 is empty, swap from stack 1 to stack 2
  // return top from stack 2
  if (m_stack_2.empty()) {
    swap();
  }
  return m_stack_2.top();
}

template <typename T>
T& MyQueue<T>::back() {
  // if stack 1 is empty, swap from stack 2 to stack 1
  // return top from stack 1
  if (m_stack_1.empty()) {
    swap();
  }
  return m_stack_1.top();
}

template <typename T>
bool MyQueue<T>::empty() {
  return m_stack_1.empty() && m_stack_2.empty();
}

template <typename T>
unsigned int MyQueue<T>::size() {
  return m_stack_1.size() + m_stack_2.size();
}

template <typename T>
void MyQueue<T>::push(T t_data) {
  // always push into stack 1
  if (m_stack_1.empty()) {
    swap();
  }
  m_stack_1.push(t_data);
}

template <typename T>
void MyQueue<T>::pop() {
  // always pop from stack 2
  if (m_stack_2.empty()) {
    swap();
  }
  m_stack_2.pop();
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  // testing implementation
  MyQueue<int> arr;
  arr.push(1);
  arr.push(2);
  arr.push(3);
  arr.push(4);
  std::cout << "Front: " << arr.front() << " Back: " << arr.back() << std::endl;
  arr.pop();
  std::cout << "Front: " << arr.front() << " Back: " << arr.back() << std::endl;
  arr.pop();
  std::cout << "Front: " << arr.front() << " Back: " << arr.back() << std::endl;
  arr.pop();
  std::cout << "Front: " << arr.front() << " Back: " << arr.back() << std::endl;
  arr.pop();

  return 0;
}
