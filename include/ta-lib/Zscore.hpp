#pragma once

#include <ta-lib/RangeCache.hpp>
#include <ta-lib/Variance.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class Zscore {
public:
  Zscore(uint32_t period);

  std::optional<double> nextVal(double val);

private:
  Variance var;
};

} // namespace talib
