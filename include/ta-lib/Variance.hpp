#pragma once

#include <ta-lib/RangeCache.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class Variance {
public:
  Variance(uint32_t period);

  std::optional<double> nextVal(double val);

  struct ValueCtx {
    std::optional<double> var{};
    double mean{0.};
  };
  ValueCtx calcNext(double val);

private:
  uint32_t period{0};

  double runningSum{0.};
  double runningSquareSum{0.};

  struct CacheVal {
    double val{0.};
    double squareVal{0.};
  };
  RangeCacheT<CacheVal> inputCache;
};

} // namespace talib
