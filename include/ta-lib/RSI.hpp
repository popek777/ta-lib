#pragma once

#include <cstdint>
#include <optional>

namespace talib {

class RSI {
public:
  RSI(uint32_t period = 14);

  std::optional<double> nextVal(double val);

private:
  uint32_t period{0};
  double avgGain{0.};
  double avgLoss{0.};

  uint32_t inputCnt{0};
  double prevVal{0.};
  uint32_t period_1{0};
};

} // namespace talib
