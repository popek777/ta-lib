#pragma once

#include <optional>
#include <cstdint>

namespace talib {

class EMA {
public:
  EMA(uint32_t period);

  std::optional<double> nextVal(double val);

private:
  uint32_t period{0};

  double k{0.};

  double last{0.};

  uint32_t filled{1};
};

} // namespace talib
