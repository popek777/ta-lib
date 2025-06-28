#pragma once

#include <cstdint>
#include <optional>

namespace talib {

class ADX {
public:
  ADX(uint32_t period = 14);

  std::optional<double> nextVal(double close, double low, double high);

private:
  uint32_t period{0};
  uint32_t period_less_1{0};
  uint32_t firstAvgDXIndex{0};

  double prevClose{0.};
  double prevLow{0.};
  double prevHigh{0.};

  double avgTR{0.};
  double avgPlusDM{0.};
  double avgMinusDM{0.};
  double avgDX{0.};

  uint32_t inputCnt{0};
};

} // namespace talib
