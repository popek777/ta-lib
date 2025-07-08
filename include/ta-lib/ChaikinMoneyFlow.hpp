#pragma once

#include <ta-lib/RangeCache.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class ChaikinMoneyFlow {
public:
  ChaikinMoneyFlow(uint32_t period);

  std::optional<double> nextVal(double h, double l, double c, double v);

private:
  uint32_t period{0};

  double mfvSum{0.};
  double volSum{0.};

  struct CacheVal {
    double mfv{0.};
    double vol{0.};
  };
  RangeCacheT<CacheVal> inputCache;
};

} // namespace talib
