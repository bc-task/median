#ifndef MEDIAN_INSTERTION_SORT_H
#define MEDIAN_INSTERTION_SORT_H

#include "median_interface.h"

#include <cstddef>

namespace mdn {

/**
* Simple implementation based on insertion sort.
*
* Complexity for stream of n values:
* Time complexity of addition O(n^2)
* Time complexity of calculatin median O(n)
* Total time complexity O(n^2)
* Space complexity O(n)
*/
class MedianInsertionSort : public IMedianCalc {
 public:
  MedianInsertionSort();
  virtual ~MedianInsertionSort();

  // IMedian interface
  virtual void Add(int val);
  virtual double GetMedian() const;

 private:
  /** Dynamically expands data buffer when needed */
  void ExpandBuffer();

  int*   buf_; ///< data buffer, dynamically expanded
  size_t data_size_;
  size_t buf_size_;
};

}

#endif // MEDIAN_INSTERTION_SORT_H
