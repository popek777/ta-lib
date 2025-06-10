#pragma once

#include <vector>

namespace talib {

class RangeCache {
public:
  RangeCache(std::size_t size);

  // return true if range is fully filled
  bool push(double v);

  double front() const;

private:
  std::vector<double> buffer;
  std::size_t idx{static_cast<std::size_t>(-1)};
};

} // namespace talib
