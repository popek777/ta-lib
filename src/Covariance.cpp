#include <ta-lib/Covariance.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <cmath>

namespace talib {

Covariance::Covariance(uint32_t period)
    : period(period)
    , inputCache(period)
{
}

std::optional<double> Covariance::nextVal(double x, double y)
{
  double xy = x * y;

  runningXSum += x;
  runningYSum += x;
  runningXYSum += xy;

  auto [front, filled] = inputCache.push({x, y, xy});

  if (!filled) {
    return {};
  }

  runningXSum -= front.x;
  runningYSum -= front.y;
  runningXYSum -= front.xy;

  // (population) covariance equation:
  // 1/N * sum(x*y) - (1/N * sum(x)) * (1/N * sum(y)) -> 1/N * (sum(x*y) - 1/N *(sum(x) * sum(y)))
  return (runningXYSum - (runningXSum * runningYSum) / period) / period;
}

} // namespace talib
