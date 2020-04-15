// Implemented a function to check if a binary tree is balanced. For the
// purposes of this question, a balanced tree is defined to be a tree such that
// the heights of the two subtrees of any node never differ by more than one.

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
  unsigned int Height();
  bool IsBalanced(unsigned int* h);
};

template <typename T>
unsigned int BinaryNode<T>::Height() {
  unsigned int h_left = 0, h_right = 0;
  if (left_ != nullptr) {
    h_left = left_->Height();
  }
  if (right_ != nullptr) {
    h_right = right_->Height();
  }
  return (h_left > h_right ? h_left : h_right) + 1;
}

template <typename T>
bool BinaryNode<T>::IsBalanced(unsigned int* h) {
  unsigned int h_left = 0, h_right = 0;
  bool b_left = true, b_right = true;
  if (left_ != nullptr) {  // check if left subtree is balanced
    b_left = left_->IsBalanced(&h_left);
    if (b_left == false) {
      return false;  // if a subtree is unbalanced, return false
    }
  }
  if (right_ != nullptr) {  // check if right subtree is balanced
    b_right = right_->IsBalanced(&h_right);
    if (b_right == false) {
      return false;  // if a subtree is unbalanced, return false
    }
  }
  *h = (h_left > h_right ? h_left : h_right) + 1;  // update node height
  if ((h_left > h_right ? h_left - h_right : h_right - h_left) >= 2) {
    return false;  // check imbalance between subtrees
  }
  return true;  // subtrees are balanced and no height imbalance between them
}

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
  BinaryNode<T>* root() { return root_.get(); }
  void set_root(BinaryNodePtr node) { root_ = move(node); }
  void set_root(T data) { root_ = make_unique<BinaryNode<T>>(data); }
  void InsertNode(T data);
  vector<forward_list<BinaryNode<T>*>> ListOfDepths();
  bool IsBalanced();
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

template <typename T>
void BinaryTree<T>::InsertNode(T data) {
  // check root
  if (root_ == nullptr) {
    root_ = make_unique<BinaryNode<T>>(data);
    return;
  }
  //
  BinaryNode<T>* node = root_.get();

  while (node != nullptr) {
    if (data < node->data()) {
      if (node->left() == nullptr) {
        node->set_left(make_unique<BinaryNode<T>>(data));
        return;
      }
      node = node->left();
    } else {
      if (node->right() == nullptr) {
        node->set_right(make_unique<BinaryNode<T>>(data));
        return;
      }
      node = node->right();
    }
  }
}

template <typename T>
bool BinaryTree<T>::IsBalanced() {
  unsigned int h = 0;
  return root_->IsBalanced(&h);
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

  bst->InsertNode(-1);

  auto ll = bst->ListOfDepths();

  cout << "List of Depths:" << endl;
  for (const auto& depth : ll) {
    for (const auto& node : depth) {
      cout << node->data() << " ";
    }
    cout << endl;
  }
  cout << "Height: " << bst->root()->Height() << endl;
  cout << "IsBalanced: " << bst->IsBalanced() << endl;

  return 0;
}
