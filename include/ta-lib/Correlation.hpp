#pragma once

#include <ta-lib/RangeCache.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class Correlation {
public:
  Correlation(uint32_t period);

  std::optional<double> nextVal(double x, double y);

private:
  uint32_t period{0};

  double sumX{0.};
  double sumY{0.};
  double sumX2{0.};
  double sumY2{0.};
  double sumXY{0.};

  struct CacheVal {
    double x{0.};
    double y{0.};
    double x2{0.};
    double y2{0.};
    double xy{0.};
  };
  RangeCacheT<CacheVal> inputCache;
};

} // namespace talib
