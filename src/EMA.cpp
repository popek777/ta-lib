#include <ta-lib/EMA.hpp>

namespace talib {

EMA::EMA(uint32_t period)
    : period(period)
    , k(2. / (period + 1))
{
}

// return value if more then period sampels had been observer
// or null if less then period samples had bee observed so far
std::optional<double> EMA::nextVal(double v)
{
  if (filled < period) {
    ++filled;
    last += v;
    return {};
  }

  if (filled == period) {
    ++filled;
    last = (last + v) / period;
    return last;
  }

  last = k * (v - last) + last;

  return last;
}

} // namespace talib
