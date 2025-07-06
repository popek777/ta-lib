#pragma once

#include <ta-lib/RangeCache.hpp>
#include <ta-lib/SortedWindow.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class Median {
public:
  Median(uint32_t period);

  std::optional<double> nextVal(double val);

private:
  std::size_t midIdx{0};
  std::size_t midIdxPlus{0};

  RangeCacheT<double, std::optional<double>> inputCache;
  SortedWindow window;
};

} // namespace talib
