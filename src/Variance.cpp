#include <ta-lib/Variance.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <cmath>

namespace talib {

Variance::Variance(uint32_t period)
    : period(period)
    , inputCache(period)
{
}

Variance::ValueCtx Variance::calcNext(double v)
{
  runningSum += v;

  double squareVal = v * v;
  runningSquareSum += squareVal;

  auto [front, filled] = inputCache.push({v, squareVal});

  if (!filled) {
    return {{}, 0.};
  }

  runningSum -= front.val;
  runningSquareSum -= front.squareVal;

  double mean = runningSum / period;
  double variance = (runningSquareSum / period) - (mean * mean);

  return {isZeroOrNeg(variance) ? 0. : variance, // in case of  tiny negative errors
          mean};
}

std::optional<double> Variance::nextVal(double v) { return calcNext(v).var; }

} // namespace talib
