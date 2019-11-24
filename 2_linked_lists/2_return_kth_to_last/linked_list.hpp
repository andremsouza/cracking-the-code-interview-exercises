#ifndef LL_LINKED_LIST_H_
#define LL_LINKED_LIST_H_

#include <unordered_map>

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

  // * 2.1 implementations
  void removeDupsHash();
  void removeDupsPointers();

  // * 2.2 implementations
  SingleLinkedNode<T> *getKthToLast(const int t_k);
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
      m_size--;
      return true;
    }
    while (next != nullptr) {
      if (next->getData() == t_data) {
        cur->setNext(next->getNext());
        delete next;
        m_size--;
        return true;
      }
      cur = next;
      next = cur->getNext();
    }
  }
  return false;
}

template <typename T>
void SingleLinkedList<T>::removeDupsHash() {
  // using an unordered_map (hash table) to store duplicates for values
  std::unordered_map<T, bool> elementHash;
  SingleLinkedNode<T> *cur = m_head;

  elementHash[m_head->getData()] = true;
  while (cur->getNext() != nullptr) {
    if (elementHash.find(cur->getNext()->getData()) != elementHash.end()) {
      SingleLinkedNode<T> *tmp = cur->getNext();
      cur->setNext(tmp->getNext());
      delete tmp;
      m_size--;
    } else {
      elementHash[cur->getNext()->getData()] = true;
      cur = cur->getNext();
    }
  }
}

template <typename T>
void SingleLinkedList<T>::removeDupsPointers() {
  SingleLinkedNode<T> *cur = m_head, *cmp;

  while (cur != nullptr) {
    cmp = cur;
    while (cmp->getNext() != nullptr) {
      if (cmp->getNext()->getData() == cur->getData()) {
        SingleLinkedNode<T> *tmp = cmp->getNext();
        cmp->setNext(tmp->getNext());
        delete tmp;
        m_size--;
      } else {
        cmp = cmp->getNext();
      }
    }
    cur = cur->getNext();
  }
}

template <typename T>
SingleLinkedNode<T> *SingleLinkedList<T>::getKthToLast(const int t_k) {
  // initialize pointers to nodes in the list
  SingleLinkedNode<T> *cur = m_head, *cmp = m_head;

  // use cmp to go t_k positions ahead of cur
  for (int i = 0; i < t_k; i++) {
    if (cmp->getNext() != nullptr)
      cmp = cmp->getNext();
    else
      return nullptr;  // list size smaller than k
  }

  // iterate over list until the end
  // keeping cur exactly k spaces behind cmp
  while (cmp->getNext() != nullptr) {
    cur = cur->getNext();
    cmp = cmp->getNext();
  }

  // return kth node from last
  return cur;
}

}  // namespace ll

#endif
