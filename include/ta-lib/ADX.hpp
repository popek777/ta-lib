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
  uint32_t firstAvgDXIndex{0};

  double prevClose{0.};
  double prevLow{0.};
  double prevHigh{0.};

  double prevAvgTR{0.};
  double prevAvgPlusDM{0.};
  double prevAvgMinusDM{0.};
  double prevAvgDX{0.};

  uint32_t inputCnt{0};
};

} // namespace talib
