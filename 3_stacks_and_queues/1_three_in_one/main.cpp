// Describe how you could use a single array to implement three stacks

// * Solution: Class that implements multiple dynamic size stacks on a fixed
// *  size array.

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class ArrayMultiStack {
 private:
  T* m_arr;               // array of size m_n_capacity to store data
  unsigned int* m_sizes;  // number of elements in each stack
  unsigned int* m_top;    // index of top element of each stack
  unsigned int* m_next;   // index of next item, for all elements of m_arr

  unsigned int m_n_stacks, m_n_capacity,
      m_free = 0;  // stores starting index of free list

  void checkValidStackId(const unsigned int t_stack_id);
  bool full();

 public:
  ArrayMultiStack(const unsigned int t_n_stacks,
                  const unsigned int t_n_capacity);
  ~ArrayMultiStack();

  bool empty(unsigned int t_stack_id);
  unsigned int size(unsigned int t_stack_id);
  T& top(unsigned int t_stack_id);
  void push(T t_data, unsigned int t_stack_id);
  T& pop(unsigned int t_stack_id);
};

template <typename T>
ArrayMultiStack<T>::ArrayMultiStack(const unsigned int t_n_stacks,
                                    const unsigned int t_n_capacity)
    : m_n_stacks(t_n_stacks), m_n_capacity(t_n_capacity) {
  m_arr = new T[m_n_capacity]();
  m_sizes = new unsigned int[m_n_stacks]();
  m_top = new unsigned int[m_n_stacks];
  m_next = new unsigned int[m_n_capacity];

  // initialize all stacks as empty (-1)
  fill(m_top, m_top + m_n_stacks, -1);

  // initialize all spaces as free
  for (unsigned int i = 0; i < m_n_capacity - 1; i++) {
    m_next[i] = i + 1;
  }
  m_next[m_n_capacity - 1] = -1;  // indicating end of free list
}

template <typename T>
ArrayMultiStack<T>::~ArrayMultiStack() {
  delete[] m_arr;
  delete[] m_sizes;
  delete[] m_top;
  delete[] m_next;
}

template <typename T>
void ArrayMultiStack<T>::checkValidStackId(unsigned int t_stack_id) {
  // checking validity of t_stack_id argument
  if (t_stack_id >= m_n_stacks) {
    throw out_of_range("Invalid value for t_stack_id parameter");
  }
}

template <typename T>
bool ArrayMultiStack<T>::full() {
  return m_free == -1;
}

template <typename T>
bool ArrayMultiStack<T>::empty(unsigned int t_stack_id) {
  checkValidStackId(t_stack_id);
  return m_sizes[t_stack_id] == 0;
}

template <typename T>
unsigned int ArrayMultiStack<T>::size(unsigned int t_stack_id) {
  checkValidStackId(t_stack_id);
  return m_sizes[t_stack_id];
}

template <typename T>
T& ArrayMultiStack<T>::top(unsigned int t_stack_id) {
  checkValidStackId(t_stack_id);
  if (m_sizes[t_stack_id] == 0) {
    throw logic_error("Atempt to access element of an empty stack.");
  }
  return m_arr[m_top[t_stack_id]];
}

template <typename T>
void ArrayMultiStack<T>::push(T t_data, unsigned int t_stack_id) {
  checkValidStackId(t_stack_id);
  if (full()) {
    throw out_of_range("Attempt to insert element in a full stack.");
  }
  // storing element of first free space
  int i = m_free;
  // update index of first free element to next space
  m_free = m_next[i];
  // update next of top and top for stack "t_stack_id"
  m_next[i] = m_top[t_stack_id];
  m_top[t_stack_id] = i;

  // insert data
  m_arr[i] = t_data;
}

template <typename T>
T& ArrayMultiStack<T>::pop(unsigned int t_stack_id) {
  checkValidStackId(t_stack_id);
  if (m_sizes[t_stack_id] == 0) {
    throw logic_error("Atempt to access element of an empty stack.");
  }

  // get top item in stack "t_stack_id"
  int i = m_top[t_stack_id];

  // change top to store next element in the stack
  m_top[t_stack_id] = m_next[i];

  // insert previous top element to beginning of free list
  m_next[i] = m_free;
  m_free = i;

  // return removed element
  return m_arr[i];
}

// int main(int argc, char const *argv[]) { // Not using argc/argv
int main() {
  /* code */
  ArrayMultiStack<int> arr(3, 30);

  return 0;
}
