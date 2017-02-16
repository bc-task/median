#include <cstring>

#include "median_instertion_sort.h"

namespace mdn {
  MedianInsertionSort::MedianInsertionSort()
      : buf_(nullptr),
        data_size_(0),
        buf_size_(1) {
    buf_ = new int[buf_size_];
  }

  MedianInsertionSort::~MedianInsertionSort() {
    delete[] buf_;
  }

  void MedianInsertionSort::Add(int val) {
    data_size_++;
    ExpandBuffer();
    // insertion sort step
    int i = data_size_ - 2;
    while (i > 0 && buf_[i] > val) {
        buf_[i + 1] = buf_[i];
        --i;
    }
    buf_[i + 1] = val;
  }

  double MedianInsertionSort::GetMedian() const {
    int half_size = data_size_ / 2;
    if (data_size_ % 2)  { // odd number of elements
      return buf_[half_size];
    }
    // even number of elements
    return (buf_[half_size] + buf_[half_size - 1]) / 2.0;
  }

  void MedianInsertionSort::ExpandBuffer() {
    if (data_size_ == buf_size_) {
        buf_size_ *= 2;
        int* buf_tmp = new int[buf_size_];
        memcpy(buf_tmp, buf_, data_size_ * sizeof(int));
        delete[] buf_;
        buf_ = buf_tmp;
      }
  }

}
