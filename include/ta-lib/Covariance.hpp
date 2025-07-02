#pragma once

#include <ta-lib/RangeCache.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class Covariance {
public:
  Covariance(uint32_t period);

  std::optional<double> nextVal(double x, double y);

private:
  uint32_t period{0};

  double runningXSum{0.};
  double runningYSum{0.};
  double runningXYSum{0.};

  struct CacheVal {
    double x{0.};
    double y{0.};
    double xy{0.};
  };
  RangeCacheT<CacheVal> inputCache;
};

} // namespace talib
