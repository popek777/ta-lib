#include <ta-lib/SMA.hpp>

namespace talib {

SMA::SMA(uint32_t period)
    : period(period)
    , inputCache(period)
{
}

// return value if more then period sampels had been observer
// or null if less then period samples had bee observed so far
std::optional<double> SMA::nextVal(double v)
{
  runningSum += v;
  bool filled = inputCache.push(v);

  if (!filled) {
    return {};
  }

  runningSum -= inputCache.front();
  return runningSum / period;
}

} // namespace talib
