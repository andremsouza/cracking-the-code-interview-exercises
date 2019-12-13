#ifndef LL_LINKED_LIST_H_
#define LL_LINKED_LIST_H_

#include <unordered_map>
#include <vector>

namespace ll {

// ! --------------------------------------------------------------------------

template<typename T>
class SingleLinkedNode {
 private:
  T m_data;
  SingleLinkedNode<T> *m_next = nullptr;

 public:
  // constructor

  SingleLinkedNode();
  explicit SingleLinkedNode(T t_data);

  // public methods

  T getData();
  void setData(T t_data);
  SingleLinkedNode<T> *getNext();
  void setNext(SingleLinkedNode<T> *t_next);
};

template<typename T>
SingleLinkedNode<T>::SingleLinkedNode() = default;

template<typename T>
SingleLinkedNode<T>::SingleLinkedNode(T t_data) : m_data(t_data) {}

template<typename T>
T SingleLinkedNode<T>::getData() {
  return m_data;
}

template<typename T>
void SingleLinkedNode<T>::setData(T t_data) {
  m_data = t_data;
}

template<typename T>
SingleLinkedNode<T> *SingleLinkedNode<T>::getNext() {
  return m_next;
}

template<typename T>
void SingleLinkedNode<T>::setNext(SingleLinkedNode<T> *t_next) {
  m_next = t_next;
}

// ! --------------------------------------------------------------------------

template<typename T>
class SingleLinkedList {
 private:
  SingleLinkedNode<T> *m_head = nullptr;
  unsigned long long int m_size = 0;

 public:
  SingleLinkedList();
  ~SingleLinkedList();

  SingleLinkedNode<T> *getHead();
  SingleLinkedNode<T> *push_front(T t_data);
  SingleLinkedNode<T> *push_back(T t_data);
  bool remove(T t_data);

  // * 2.1 implementations
  void removeDupsHash();
  void removeDupsPointers();

  // * 2.2 implementations
  SingleLinkedNode<T> *getKthToLast(int t_k);

  // * 2.3 implementations
  void removeNodeFromMiddle(SingleLinkedNode<T> *t_node);

  // * 2.4 implementations
  void partitionByValue(T t_value);

  // * 2.7 implementations
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList() = default;

template<typename T>
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

template<typename T>
SingleLinkedNode<T> *SingleLinkedList<T>::getHead() {
  return m_head;
}

template<typename T>
SingleLinkedNode<T> *SingleLinkedList<T>::push_back(T t_data) {
  auto *new_node = new SingleLinkedNode<T>(t_data);
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

template<typename T>
SingleLinkedNode<T> *SingleLinkedList<T>::push_front(T t_data) {
  auto *new_node = new SingleLinkedNode<T>(t_data);
  // if list is empty, set head as new node
  if (m_size == 0) {
    m_head = new_node;
  } else {
    // inserting at the start of the list
    new_node->setNext(m_head);
    m_head = new_node;
  }
  m_size++;
  return new_node;
}

template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
void SingleLinkedList<T>::removeNodeFromMiddle(SingleLinkedNode<T> *t_node) {
  // assuming I don't have access to the list's head
  if (t_node != nullptr) {
    SingleLinkedNode<T> *tmp = t_node->getNext();

    if (tmp != nullptr) {
      t_node->setData(tmp->getData());
      t_node->setNext(tmp->getNext());
      delete tmp;
      m_size--;
    }
  }
}

template<typename T>
void SingleLinkedList<T>::partitionByValue(const T t_value) {
  // EXAMPLE
  // Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition=5]
  // Output 3-> 1 -> 2 -> 10 -> 5 -> 5 -> 8
  // trying to do this operation in place
  SingleLinkedNode<T> *cur = m_head, *left_s = nullptr, *left_e = nullptr,
      *right_s = nullptr, *right_e = nullptr;

  // iterate over original list
  while (cur != nullptr) {
    SingleLinkedNode<T> *next = cur->getNext();
    cur->setNext(nullptr);
    if (cur->getData() < t_value) {
      // if value less than t_value, append to left list
      if (left_s == nullptr) {
        left_s = cur;
        left_e = left_s;
      } else {
        left_e->setNext(cur);
        left_e = cur;
      }
    } else {
      // if value greater or equal than t_value, insert to right list
      if (right_s == nullptr) {
        right_s = cur;
        right_e = right_s;
      } else if (cur->getData() == t_value) {
        // if value equal to t_value, insert at the beginning
        cur->setNext(right_s);
        right_s = cur;
      } else {
        // if value greater than t_value, insert at the end
        right_e->setNext(cur);
        right_e = cur;
      }
    }
    cur = next;
  }

  // set new head for list
  if (left_s == nullptr) {
    // if left list is empty, set head to right list
    m_head = right_s;
  } else {
    // else, merge the two lists
    left_e->setNext(right_s);
    m_head = left_s;
  }
}

}  // namespace ll

#endif
