// How would you design a stack which, in addition to push and pop, has a
// function min which returns the minimum element? Push, pop and min should all
// operate in O(1) time.

// * Solution: Mantain a second stack with the minimum values.
// *  Only push values into the min stack when a new minimum value appears, or
// *    when a value equal to the current minimum is pushed into the main stack.
// *  Only pop values from the min stack when the current min value is popped
// *    from the main stack.
// * Push, pop and min operations' complexities are O(1).
// * Space complexity is O(n)

#include <iostream>

#include "stack.hpp"

template <typename T>
class StackMin : public Stack<T> {
 private:
  Stack<T>* m_stack_min;  // secondary stack to store minimum elements

 public:
  StackMin(unsigned int t_capacity);
  ~StackMin();

  void push(T t_data);
  T* pop();
  T* min();
};

template <typename T>
StackMin<T>::StackMin(unsigned int t_capacity) : Stack<T>(t_capacity) {
  m_stack_min = new Stack<T>(t_capacity);
}

template <typename T>
StackMin<T>::~StackMin() {
  delete m_stack_min;
}

template <typename T>
void StackMin<T>::push(T t_data) {
  if (Stack<T>::size() == 0 || t_data <= *(min())) {
    (*m_stack_min).push(t_data);
  }
  Stack<T>::push(t_data);
}

template <typename T>
T* StackMin<T>::pop() {
  T* data = Stack<T>::pop();
  if (*data == *(min())) {
    (*m_stack_min).pop();
  }
  return data;
}

template <typename T>
T* StackMin<T>::min() {
  return (*m_stack_min).top();
}

// int main(int argc, char const *argv[]) { // Not using argc/argv
int main() {
  /* code */
  StackMin<int> arr(100);
  arr.push(10);
  arr.push(2);
  arr.push(5);
  arr.push(2);
  arr.push(4);
  arr.push(2);
  arr.push(20);
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();
  std::cout << *arr.top() << " " << *arr.min() << std::endl;
  arr.pop();

  return 0;
}
