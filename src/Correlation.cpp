#include <ta-lib/Correlation.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <cmath>

namespace talib {

Correlation::Correlation(uint32_t period)
    : period(period)
    , inputCache(period)
{
}

std::optional<double> Correlation::nextVal(double x, double y)
{
  double x2 = x * x;
  double y2 = y * y;
  double xy = x * y;

  sumX += x;
  sumY += y;
  sumX2 += x2;
  sumY2 += y2;
  sumXY += xy;

  auto [front, filled] = inputCache.push({x, y, x2, y2, xy});

  if (!filled) {
    return {};
  }

  sumX -= front.x;
  sumY -= front.y;
  sumX2 -= front.x2;
  sumY2 -= front.y2;
  sumXY -= front.xy;

  double numerator = period * sumXY - sumX * sumY;
  double denomX = period * sumX2 - sumX * sumX;
  double denomY = period * sumY2 - sumY * sumY;

  if (isZeroOrNeg(denomX)) {
    denomX = 0;
  }
  if (isZeroOrNeg(denomY)) {
    denomY = 0;
  }
  double denom = std::sqrt(denomX * denomY);

  if (isZero(denom)) {
    return 1.;
  }

  double corr = numerator / denom;
  if (corr > 1.) {
    corr = 1.;
  }
  else if (corr < -1.) {
    corr = -1.;
  }
  return corr;
}

} // namespace talib
