#pragma once

#include <vector>

namespace talib {

class RangeCache {
public:
  RangeCache(std::size_t size);

  // return firt element of a range (since it will be replaced with pushed value) 
  // and bool indicating if range is filled
  std::pair<double, bool> push(double v);

private:
  std::vector<double> buffer;
  std::size_t idx{static_cast<std::size_t>(-1)};
};

} // namespace talib
