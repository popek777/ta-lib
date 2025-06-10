#pragma once

#include <ta-lib/RangeCache.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class SMA {
public:
  SMA(uint32_t period);

  std::optional<double> nextVal(double val);

private:
  uint32_t period{0};

  double runningSum{0.};
  RangeCache inputCache;
};

} // namespace talib
