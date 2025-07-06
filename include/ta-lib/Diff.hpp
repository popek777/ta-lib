#pragma once

#include <ta-lib/RangeCache.hpp>

#include <cstdint>
#include <optional>

namespace talib {

// mimicks pandas diff
class Diff {
public:
  Diff(uint32_t period = 1);

  std::optional<double> nextVal(double v);

private:
  // returns optional to indicate that range is filled but there is not value (rather then 0.)
  RangeCacheT<double, std::optional<double>> inputCache;
};

} // namespace talib
