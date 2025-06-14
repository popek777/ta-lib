#pragma once

#include <ta-lib/EMA.hpp>

#include <optional>

namespace talib {

class MACD {
public:
  MACD(uint32_t shortPeriod = 12, uint32_t longPeriod = 26, uint32_t signalPeriod = 9);

  struct Value {
    double macd;
    double signal;
  };
  std::optional<Value> nextVal(double);

private:
  EMA shortEma;
  EMA longEma;
  EMA signalEma;
};

} // namespace talib
