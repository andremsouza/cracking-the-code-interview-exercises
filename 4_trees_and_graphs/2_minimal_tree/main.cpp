// Given a sorted (increasing order) array with unique integer elements, write
// an algorithm to create a binary search tree with minimal height.

// * Solution: recursive function in a divide-and-conquer fashion

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

template <typename T>
class BinaryNode {
  typedef std::unique_ptr<BinaryNode> BinaryNodePtr;

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
  void set_left(BinaryNodePtr node) { left_ = std::move(node); }
  BinaryNode* right() { return right_.get(); }
  void set_right(BinaryNodePtr node) { right_ = std::move(node); }
};

template <typename T>
class BinaryTree {
  typedef std::unique_ptr<BinaryNode<T>> BinaryNodePtr;

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
    root_ = std::move(CreateMinTree(first, last));
  }
  BinaryNodePtr root() { return root_; }
  void set_root(BinaryNodePtr node) { root_ = std::move(node); }
  void set_root(T data) { root_ = std::make_unique<BinaryNode<T>>(data); }
};

template <typename T>
template <class RandomAccessIterator>
std::unique_ptr<BinaryNode<T>> BinaryTree<T>::CreateMinTree(
    RandomAccessIterator first, RandomAccessIterator last) {
  // base case
  if (first == last) {
    return nullptr;
  }
  // find middle point from container/array
  unsigned int half = std::distance(first, last) / 2;
  auto middle = first;
  while (half-- > 0) {
    middle++;
  }
  std::cout << *(middle) << std::endl;
  // create node with middle element
  auto node = std::make_unique<BinaryNode<T>>(*middle);
  // split container into left and right section
  node->set_left(CreateMinTree(first, middle));
  node->set_right(CreateMinTree(++middle, last));
  return node;
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  // testing implementation
  std::vector<int> sorted_arr;
  int tmp;

  while (std::cin >> tmp) {
    sorted_arr.push_back(tmp);
  }

  std::sort(sorted_arr.begin(), sorted_arr.end(),
            [](int a, int b) { return a < b; });

  auto bst =
      std::make_unique<BinaryTree<int>>(sorted_arr.begin(), sorted_arr.end());

  return 0;
}
