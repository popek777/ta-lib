#include <ta-lib/MACD.hpp>

namespace talib {

MACD::MACD(uint32_t shortPeriod, uint32_t longPeriod, uint32_t signalPeriod)
    : shortEma(shortPeriod)
    , longEma(longPeriod)
    , signalEma(signalPeriod)
{
}

std::optional<MACD::Value> MACD::nextVal(double v)
{
  auto s = shortEma.nextVal(v);
  auto l = longEma.nextVal(v);

  if (!l.has_value() || !s.has_value()) {
    return {};
  }

  auto macd = *s - *l;
  auto sig = signalEma.nextVal(macd);

  if (!sig.has_value()) {
    return {};
  }

  return Value{macd, *sig};
}

} // namespace talib
