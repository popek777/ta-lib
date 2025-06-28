#pragma once

#include <cstdint>
#include <optional>

namespace talib {

class ATR {
public:
  ATR(uint32_t period = 14);

  std::optional<double> nextVal(double close, double low, double high);

private:
  uint32_t period{0};
  uint32_t period_less_1{0};

  double prevClose{0.};
  double prevLow{0.};
  double prevHigh{0.};

  double avgTR{0.};

  uint32_t inputCnt{0};
};

} // namespace talib
