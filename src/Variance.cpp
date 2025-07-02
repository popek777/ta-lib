#include <ta-lib/Variance.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <cmath>

namespace talib {

Variance::Variance(uint32_t period)
    : period(period)
    , inputCache(period)
{
}

// return value if more then period sampels had been observer
// or null if less then period samples had bee observed so far
std::optional<double> Variance::nextVal(double v)
{
  runningSum += v;

  double squareVal = v * v;
  runningSquareSum += squareVal;

  auto [front, filled] = inputCache.push({v, squareVal});

  if (!filled) {
    return {};
  }

  runningSum -= front.val;
  runningSquareSum -= front.squareVal;

  double mean = runningSum / period;
  double variance = (runningSquareSum / period) - (mean * mean);

  // in case of  tiny negative errors
  if (isZeroOrNeg(variance)) {
    return 0.;
  }

  return variance;
}

} // namespace talib
