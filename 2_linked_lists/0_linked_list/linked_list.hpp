#ifndef LL_LINKED_LIST_H_
#define LL_LINKED_LIST_H_
namespace ll {

// ! --------------------------------------------------------------------------

template <typename T>
class SingleLinkedNode {
 private:
  T m_data;
  SingleLinkedNode<T> *m_next = nullptr;

 public:
  // constructor

  SingleLinkedNode();
  SingleLinkedNode(T t_data);

  // public methods

  T getData();
  void setData(T t_data);
  SingleLinkedNode<T> *getNext();
  void setNext(SingleLinkedNode<T> *t_next);
};

template <typename T>
SingleLinkedNode<T>::SingleLinkedNode() {}

template <typename T>
SingleLinkedNode<T>::SingleLinkedNode(T t_data) : m_data(t_data) {}

template <typename T>
T SingleLinkedNode<T>::getData() {
  return m_data;
}

template <typename T>
void SingleLinkedNode<T>::setData(T t_data) {
  m_data = t_data;
}

template <typename T>
SingleLinkedNode<T> *SingleLinkedNode<T>::getNext() {
  return m_next;
}

template <typename T>
void SingleLinkedNode<T>::setNext(SingleLinkedNode<T> *t_next) {
  m_next = t_next;
}

// ! --------------------------------------------------------------------------

template <typename T>
class SingleLinkedList {
 private:
  SingleLinkedNode<T> *m_head = nullptr;
  unsigned long long int m_size = 0;

 public:
  SingleLinkedList();
  ~SingleLinkedList();

  SingleLinkedNode<T> *getHead();
  SingleLinkedNode<T> *push_back(T t_data);
  bool remove(T t_data);
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList() {}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList() {
  if (m_size) {
    SingleLinkedNode<T> *cur = m_head;
    SingleLinkedNode<T> *next;

    while (cur->getNext() != nullptr) {
      next = cur->getNext();
      delete cur;
      cur = next;
    }
    delete cur;
  }
}

template <typename T>
SingleLinkedNode<T> *SingleLinkedList<T>::getHead() {
  return m_head;
}

template <typename T>
SingleLinkedNode<T> *SingleLinkedList<T>::push_back(T t_data) {
  SingleLinkedNode<T> *new_node = new SingleLinkedNode<T>(t_data);
  // if list is empty, set head as new node
  if (m_size == 0) {
    m_head = new_node;
  } else {
    SingleLinkedNode<T> *cur = m_head;
    // inserting at the end of the list
    while (cur->getNext() != nullptr) {
      cur = cur->getNext();
    }
    cur->setNext(new_node);
  }
  m_size++;
  return new_node;
}

template <typename T>
bool SingleLinkedList<T>::remove(T t_data) {
  if (m_size) {
    SingleLinkedNode<T> *cur = m_head;
    SingleLinkedNode<T> *next = cur->getNext();
    if (cur->getData() == t_data) {
      m_head = next;
      delete cur;
      return true;
    }
    while (next != nullptr) {
      if (next->getData() == t_data) {
        cur->setNext(next->getNext());
        delete next;
        return true;
      }
      cur = next;
      next = cur->getNext();
    }
  }
  return false;
}

}  // namespace ll

#endif