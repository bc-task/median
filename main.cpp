#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <fstream>

#include "median_interface.h"

#include "median_bst.h"
#include "median_instertion_sort.h"
#include "median_ftable.h"

/**
  Test procedure of single method on sorted data.
*/
void test_sorted_calc(mdn::IMedianCalc *median, int range_max) {
  // preparing data
  const int kRangeMin = 0;
  std::vector<int> vals(range_max);
  // generate range from range_min to range_min + range_size
  std::iota(vals.begin(), vals.end(), kRangeMin);

  for (int v : vals) {
      median->Add(v);
      double m = median->GetMedian();
      std::cout << m << " ";
  }
  std::cout << std::endl;
  return;
}

/**
  Performance test procedure of single method on
  uniformly distrubuted random data.
*/
long test_performance_calc(mdn::IMedianCalc *median, int range_max, int stream_size) {
  std::vector<int> vals(stream_size);
  std::generate(vals.begin(), vals.end(), [&]{ return std::rand() % range_max; });

  auto start = std::chrono::steady_clock::now();
  for (int v : vals) {
      median->Add(v);
      median->GetMedian();
  }
  auto elapsed = std::chrono::steady_clock::now() - start;
  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

/**
  Main test function on sorted data.
*/
void test_sorted() {
  // test parameters
  int kRangeMax = 10;

  std::vector<std::pair<mdn::IMedianCalc*, std::string>> median_calcs = {
    { new mdn::MedianInsertionSort       , "insertion sort"  },
    { new mdn::MedianBST                 , "BST"             },
    { new mdn::MedianFtable(0, kRangeMax), "frequency table" }
  };

  std::cout << "Test on sorted range [0," << kRangeMax << ")" << std::endl;
  for (auto mc : median_calcs) {
    std::cout << "Method: " << mc.second << std::endl;
    test_sorted_calc(mc.first, kRangeMax);
  }

  // memory cleanup
  for (auto mc : median_calcs) {
    delete mc.first;
  }
}

/**
  Main performance test function.
*/
void test_performance(int range_max, int stream_size) {
  std::vector<std::pair<mdn::IMedianCalc*, std::string>> median_calcs = {
    { new mdn::MedianInsertionSort       , "insertion sort"  },
    { new mdn::MedianBST                 , "BST"             },
    { new mdn::MedianFtable(0, range_max), "frequency table" }
  };

  std::cout << "Performance test" << std::endl;
  std::cout << "Range [0," << range_max << "), set size " << stream_size << std::endl;
  std::cout << std::scientific << std::setprecision(2);
  for (auto mc : median_calcs) {
    double time_elapsed = test_performance_calc(mc.first, range_max, stream_size);

    std::cout << "Method: " << mc.second << std::endl;
    std::cout << "Time: " << time_elapsed << " us." << std::endl;
  }
  std::cout.unsetf(std::ios::scientific);

  // memory cleanup
  for (auto mc : median_calcs) {
    delete mc.first;
  }
}

/**
  Test procedure using file input.
 */
void test_file_stream(const std::string &filename, int method = 1) {
  const int kMaxFtableVal = 1000;

  std::ifstream fs(filename, std::ifstream::in);
  if (!fs.is_open()) {
    std::cout << "Cannot open file: " << filename << std::endl;
    return;
  }
  if (method < 0 && method > 2) {
    std::cout << "Wrong method selected." << std::endl;
  }

  mdn::IMedianCalc* median_calc = nullptr;
  switch (method) {
    case 0:
      median_calc = new mdn::MedianInsertionSort;
      break;
    case 1:
      median_calc = new mdn::MedianBST;
      break;
    case 2:
      median_calc = new mdn::MedianFtable(0, kMaxFtableVal + 1);
      break;
  };

  int v;
  std::vector<int> vals;
  while (fs.good()) {
    fs >> v;
    // range check only when using frequency table
    if (method == 2 && (v < 0 || v > kMaxFtableVal) ) { 
      std::cout << "Value outside the range, skipping." << std::endl;
      continue;
    }
    vals.push_back(v);
    std::cout << "Current vector: " << std::endl;
    for (int val : vals) std::cout << val << " ";
    std::cout << std::endl;
    median_calc->Add(v);
    double median = median_calc->GetMedian();
    std::cout << "Median: " << median << std::endl;
  }

  delete median_calc;
}

/**
 * Tests implemented algorithms.
 * Runs hard-coded tests of all algorithms when no argument is provided.
 *
 * Processes a text file of integer values using BST method when
 * filename in the argument is provided. Selects algorithm depending on
 * second argument: 0 - insertion sort, 1 - BST, 2 - Frequency Table
 * When using frequency table range is hardcoded from 0 to 1000 in this test.
 *
 * example usage: median_calc test.txt 1
 */
int main(int argc, char *argv[]) {
  if (argc < 2) {
    test_performance(100, 10e4);
    std::cout << "---" << std::endl;
    test_sorted();
  } else {
    int method = 1;
    if(argc >= 3) {
      method = atoi(argv[2]);
    }
    test_file_stream(argv[1], method);
  }

  return 0;
}
