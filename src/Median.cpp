#include <ta-lib/Median.hpp>

#include <algorithm>
#include <cmath>

namespace talib {

Median::Median(uint32_t period)
    : midIdx(period % 2 == 0 ? period / 2 - 1 : (period - 1) / 2)
    , midIdxPlus(period % 2 == 0 ? midIdx + 1 : midIdx)
    , inputCache(period)
    , window(period)
{
}

std::optional<double> Median::nextVal(double v)
{
  auto [front, filled] = inputCache.push(v);

  if (!filled) {
    window.push({}, v);
    return {};
  }

  window.push(front, v);

  double mid = window[midIdx];

  if (midIdx == midIdxPlus) {
    return mid;
  }

  return (mid + window[midIdxPlus]) / 2;
}

} // namespace talib
