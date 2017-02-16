#include "median_bst.h"

namespace mdn {
  MedianBST::MedianBST()
      : root_(nullptr),
        median_(0.0) {}

  MedianBST::~MedianBST() {
    DeleteTree(root_);
  }

  void MedianBST::Add(int val) {
    // insert new element
  root_ = Insert(root_, val);
    int half_size = GetSize(root_) / 2;

    // find new median
    if (GetSize(root_) % 2) { // odd number of elements
      median_ = Select(root_, half_size);
    } else { // even number of elements
      double m1 = Select(root_, half_size);
      double m2 = Select(root_, half_size - 1);
      median_ = (m1 + m2) / 2.0;
    }
  }

  MedianBST::Node *MedianBST::Insert(MedianBST::Node *n, int val) {
    if (!n)
      return new Node(val);
    if (val < n->val)
      n->left = Insert(n->left, val);
    else
      n->right = Insert(n->right, val);
    return BalanceTree(n);
  }

  int MedianBST::Select(MedianBST::Node *n, int i) {
    int r = GetSize(n->left);
    if (i == r)
      return n->val;
    else if(i < r)
      return Select(n->left, i);
    else
      return Select(n->right, i - (r + 1));
  }

  MedianBST::Node *MedianBST::BalanceTree(MedianBST::Node *n) {
    FixHeightAndSize(n);
    if (BalanceFactor(n) == 2) {
      if (BalanceFactor(n->right) < 0)
        n->right = RotateRight(n->right);
      return RotateLeft(n);
    }
    if (BalanceFactor(n) == -2) {
      if (BalanceFactor(n->left) > 0)
        n->left = RotateLeft(n->left);
      return RotateRight(n);
    }
    return n;
  }

  MedianBST::Node* MedianBST::RotateRight(MedianBST::Node *n) {
    Node *m = n->left;
    n->left = m->right;
    m->right = n;
    FixHeightAndSize(n);
    FixHeightAndSize(m);
    return m;
  }

  MedianBST::Node* MedianBST::RotateLeft(MedianBST::Node *n) {
    Node *m = n->right;
    n->right = m->left;
    m->left = n;
    FixHeightAndSize(n);
    FixHeightAndSize(m);
    return m;
  }

  void MedianBST::FixHeightAndSize(MedianBST::Node *n) {
    int h_l = GetHeight(n->left);
    int h_r = GetHeight(n->right);
    n->height = (h_l > h_r ? h_l : h_r) + 1;
    n->size = GetSize(n->left) + GetSize(n->right) + 1;
  }

  void MedianBST::DeleteTree(MedianBST::Node *n) {
    if (n) {
      DeleteTree(n->right);
      DeleteTree(n->left);
      delete n;
      n = nullptr;
    }
  }
}

