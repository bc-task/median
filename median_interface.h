#ifndef MEDIAN_INTERFACE_H
#define MEDIAN_INTERFACE_H

namespace mdn {

/**
 * Interface for a median calculator.
 */
class IMedianCalc {
 public:
  /** Add new value from a stream of integers */
  virtual void Add(int val) = 0;
  /** Get median of current vector */
  virtual double GetMedian() const  = 0;
  virtual ~IMedianCalc(){}
};

}

#endif // MEDIAN_INTERFACE_H
