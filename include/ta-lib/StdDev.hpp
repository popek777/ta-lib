#pragma once

#include <ta-lib/Variance.hpp>

#include <optional>
#include <cstdint>

namespace talib {

class StdDev {
public:
  StdDev(uint32_t period);

  std::optional<double> nextVal(double val);

private:
  Variance var;
};

} // namespace talib
