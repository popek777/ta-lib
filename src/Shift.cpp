#include <ta-lib/Shift.hpp>

namespace talib {

Shift::Shift(uint32_t period)
    : inputCache(period)
{
}

std::optional<double> Shift::nextVal(double v)
{
  auto [front, _] = inputCache.push(v);
  // no matter if it's filled or not. Just return front
  return front;
}

} // namespace talib
