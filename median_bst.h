#ifndef MEDIAN_BST_H
#define MEDIAN_BST_H

#include "median_interface.h"

namespace mdn {

/**
 * Implements median calculation of integers using Order-statistic AVL tree.
 *
 * Complexity for stream of n values:
 * Time complexity of addition O(n*log(n))
 * Time complexity of calculating median O(n*log(n))
 * Total time complexity O(n*log(n))
 * Space complexity O(n)
 */
class MedianBST : public IMedianCalc {
 public:
  MedianBST();
  virtual ~MedianBST();

  // IMedian interface
  virtual void Add(int val);
  virtual double GetMedian() const { return median_; }

 private:
  struct Node {
    Node *left;
    Node *right;
    int height;
    int val;
    int size;
    Node(int val) : left(nullptr), right(nullptr), height(1), val(val), size(1) {}
  };

  // Value insertion to BST
  Node* Insert(Node *n, int val);

  // Selection of i-th element using order-statistic property
  int Select(Node *n, int i);

  // helper functions
  int GetHeight(Node *n) const { return n ? n->height : 0; }
  int GetSize (Node *n) const { return n ? n->size : 0; }
  int BalanceFactor(Node *n) const { return GetHeight(n->right) - GetHeight(n->left); }

  // AVL operations
  Node* BalanceTree(Node *n);
  Node* RotateRight(Node *n);
  Node* RotateLeft(Node *n);
  void FixHeightAndSize(Node *n);

  // Tree structure deallocation, recursive
  void DeleteTree(Node *n);

  Node *root_;
  double median_; /// buffered value of current median
};

}

#endif // MEDIAN_BST_H
