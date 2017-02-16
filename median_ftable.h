#ifndef MEDIAN_FTABLE_H
#define MEDIAN_FTABLE_H

#include "median_interface.h"

namespace mdn {

/**
 * Implements median calculation of integers using frequency table.
 * Requires known range of values at creation time.
 *
 * Complexity for stream of n values in range of size h:
 * Time complexity of addition O(n)
 * Time complexity of calculating median O(n*h)
 * Total time complexity O(n*h)
 * Space complexity O(h)
 */
class MedianFtable : public IMedianCalc {
 public:
  MedianFtable(int range_min, int range_max);
  virtual ~MedianFtable();

  // IMedian interface
  virtual void Add(int val);
  virtual double GetMedian() const { return median_; }

 private:
  unsigned int *frequency_table_;
  unsigned int total_count_;
  double median_; /// buffered value of current median
  int offset_;
  unsigned int size_;

};

}

#endif // MEDIAN_FTABLE_H
