#ifndef STACK_H_
#define STACK_H_

#include <exception>

template <typename T>
class Stack {
 private:
  unsigned int m_top = -1, m_capacity;
  T* m_arr;

 public:
  Stack(unsigned int t_capacity);
  ~Stack();

  bool empty();
  bool full();
  unsigned int size();
  T* top();
  void push(T t_data);
  T* pop();
};

template <typename T>
Stack<T>::Stack(unsigned int t_capacity) : m_capacity(t_capacity) {
  m_arr = new T[t_capacity];
}

template <typename T>
Stack<T>::~Stack() {
  delete[] m_arr;
}

template <typename T>
bool Stack<T>::empty() {
  return m_top < 0;
}

template <typename T>
bool Stack<T>::full() {
  return m_top >= m_capacity - 1;
}

template <typename T>
unsigned int Stack<T>::size() {
  return m_top + 1;
}

template <typename T>
T* Stack<T>::top() {
  if (empty()) {
    throw std::logic_error("Atempt to access element of an empty stack.");
  }
  return &(m_arr[m_top]);
}

template <typename T>
void Stack<T>::push(T data) {
  if (full()) {
    throw std::out_of_range("Attempt to insert element in a full stack.");
  }
  m_arr[++m_top] = data;
}

template <typename T>
T* Stack<T>::pop() {
  if (empty()) {
    throw std::logic_error("Atempt to access element of an empty stack.");
  }
  return &(m_arr[m_top--]);
}

#endif
