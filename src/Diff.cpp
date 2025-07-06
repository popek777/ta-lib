#include <ta-lib/Diff.hpp>

namespace talib {

Diff::Diff(uint32_t period)
    : inputCache(period)
{
}

std::optional<double> Diff::nextVal(double v)
{
  auto [front, filled] = inputCache.push(v);

  if (!filled || !front.has_value()) {
    return {};
  }

  return v - *front;
}

} // namespace talib
