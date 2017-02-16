#include <string.h>

#include "median_ftable.h"

namespace mdn {
  MedianFtable::MedianFtable(int range_min, int range_max)
      : frequency_table_(nullptr),
        total_count_(0),
        median_(0.0) {
    size_            = range_max - range_min;
    offset_          = -range_min;
    frequency_table_ = new unsigned int[size_];
    memset(frequency_table_, 0, size_ * sizeof(unsigned int));
  }

  MedianFtable::~MedianFtable() {
    delete[] frequency_table_;
  }

  void MedianFtable::Add(int val) {
    // add value
    total_count_++;
    frequency_table_[val + offset_]++;

    // find new median
    unsigned int half_count = total_count_ / 2;
    unsigned int cnt = 0;
    unsigned int i = 0;
    if (total_count_ % 2) { // odd number of elements
      for (; i < size_; ++i) {
        cnt += frequency_table_[i];
        if(half_count < cnt) {
          break;
        }
      }
      median_ = i - offset_;
    } else { // even number of elements
      int i2 = 0;
      bool i2_found = false;
      for (; i < size_; ++i) {
        cnt += frequency_table_[i];
        if (!i2_found && half_count - 1 < cnt) {
          i2 = i;
          i2_found = true;
        }
        if (half_count < cnt) {
          break;
        }
      }
      median_ = (i + i2) / 2.0 - offset_;
    }
  }

}
