// Given a binary tree, design an algorithm which creates a linked list of all
// the nodes at each depth (e.g., if you have a tree with depth D, you'll have D
// linked lists).

#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

template <typename T>
class BinaryNode {
  typedef unique_ptr<BinaryNode> BinaryNodePtr;

 private:
  T data_;
  BinaryNodePtr left_;
  BinaryNodePtr right_;

 public:
  BinaryNode() {}
  BinaryNode(T data) : data_(data) {}
  T data() { return data_; }
  void set_data(T data) { data_ = data; }
  BinaryNode* left() { return left_.get(); }
  void set_left(BinaryNodePtr node) { left_ = move(node); }
  BinaryNode* right() { return right_.get(); }
  void set_right(BinaryNodePtr node) { right_ = move(node); }
};

template <typename T>
class BinaryTree {
  typedef unique_ptr<BinaryNode<T>> BinaryNodePtr;

 private:
  BinaryNodePtr root_ = nullptr;
  template <class RandomAccessIterator>
  BinaryNodePtr CreateMinTree(RandomAccessIterator first,
                              RandomAccessIterator last);

 public:
  BinaryTree() {}
  BinaryTree(T data) { set_root(data); }
  template <class RandomAccessIterator>
  BinaryTree(RandomAccessIterator first, RandomAccessIterator last) {
    root_ = move(CreateMinTree(first, last));
  }
  BinaryNodePtr root() { return root_; }
  void set_root(BinaryNodePtr node) { root_ = move(node); }
  void set_root(T data) { root_ = make_unique<BinaryNode<T>>(data); }
  vector<forward_list<BinaryNode<T>*>> ListOfDepths();
};

template <typename T>
template <class RandomAccessIterator>
unique_ptr<BinaryNode<T>> BinaryTree<T>::CreateMinTree(
    RandomAccessIterator first, RandomAccessIterator last) {
  // base case
  if (first == last) {
    return nullptr;
  }
  // find middle point from container/array
  unsigned int half = distance(first, last) / 2;
  auto middle = first;
  while (half-- > 0) {
    middle++;
  }
  // create node with middle element
  auto node = make_unique<BinaryNode<T>>(*middle);
  // split container into left and right section
  node->set_left(CreateMinTree(first, middle));
  node->set_right(CreateMinTree(++middle, last));
  return node;
}

template <typename T>
vector<forward_list<BinaryNode<T>*>> BinaryTree<T>::ListOfDepths() {
  vector<forward_list<BinaryNode<T>*>> depth_list;
  if (root_ == nullptr) {
    return depth_list;
  }

  // using a BFS algorithm to add to the list
  queue<tuple<BinaryNode<T>*, int>> q;  // store pointer and depth of node
  q.push(make_tuple(root_.get(), 0));   // push root and height indicator
  depth_list.push_back(forward_list<BinaryNode<T>*>());
  while (!q.empty()) {
    auto a = q.front();  // get queue's front element
    q.pop();
    auto node = get<0>(a);
    auto level = get<1>(a);

    if (level == (int)depth_list.size()) {
      // if found a new level, insert new element to list
      depth_list.push_back(forward_list<BinaryNode<T>*>());
    }

    depth_list[level].push_front(node);  // push element to level list

    // push children nodes to queue with height indicator
    auto left = node->left(), right = node->right();
    if (right != nullptr) {
      q.push(make_tuple(node->right(), level + 1));
    }
    if (left != nullptr) {
      q.push(make_tuple(node->left(), level + 1));
    }
  }

  return depth_list;
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  // testing implementation
  vector<int> sorted_arr;
  int tmp;

  while (cin >> tmp) {
    sorted_arr.push_back(tmp);
  }

  sort(sorted_arr.begin(), sorted_arr.end(),
       [](int a, int b) { return a < b; });

  auto bst = make_unique<BinaryTree<int>>(sorted_arr.begin(), sorted_arr.end());

  auto ll = bst->ListOfDepths();

  for (const auto& depth : ll) {
    for (const auto& node : depth) {
      cout << node->data() << " ";
    }
    cout << endl;
  }

  return 0;
}
