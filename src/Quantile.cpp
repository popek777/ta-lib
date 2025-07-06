#include <ta-lib/Quantile.hpp>

#include <algorithm>
#include <cmath>

namespace talib {

Quantile::Quantile(double q, uint32_t period)
    : k(q * (period - 1))
    , i(static_cast<uint32_t>(std::floor(k)))
    , j(static_cast<uint32_t>(std::ceil(k)))
    , fraction(k - i)
    , inputCache(period)
    , window(period)
{
}

std::optional<double> Quantile::nextVal(double v)
{
  auto [front, filled] = inputCache.push(v);

  if (!filled) {
    window.push({}, v);
    return {};
  }

  window.push(front, v);

  double xi = window[i];
  if (i == j) {
    return xi;
  }

  double xj = window[j];
  return xi + (xj - xi) * fraction;
}

} // namespace talib
