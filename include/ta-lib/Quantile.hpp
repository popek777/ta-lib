#pragma once

#include <ta-lib/RangeCache.hpp>

#include <optional>
#include <cstdint>
#include <vector>

namespace talib {

// mimicks pandas quantile (linear) 
class Quantile {
public:
  Quantile(double q, uint32_t period);

  std::optional<double> nextVal(double val);

private:
  double k{0.};
  uint32_t i{0};
  uint32_t j{0};
  double fraction{0.};

  RangeCacheT<double, std::optional<double>> inputCache;

  std::vector<double> window;
};

} // namespace talib
