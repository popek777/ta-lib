#include <ta-lib/PctChange.hpp>

namespace talib {

PctChange::PctChange(uint32_t period)
    : inputCache(period)
{
}

std::optional<double> PctChange::nextVal(double v)
{
  auto [front, filled] = inputCache.push(v);

  if (!filled || !front.has_value()) {
    return {};
  }

  return (v - *front) / (*front);
}

} // namespace talib
