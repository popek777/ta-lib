#include "ta-lib/TaLibUtils.hpp"
#include <ta-lib/ChaikinMoneyFlow.hpp>

namespace talib {

ChaikinMoneyFlow::ChaikinMoneyFlow(uint32_t period)
    : inputCache(period)
{
}

std::optional<double> ChaikinMoneyFlow::nextVal(double h, double l, double c, double v)
{
  volSum += v;

  double hl = h - l;
  double mfv = !isZero(hl) ? v * ((c - l) - (h - c)) / hl : 0.;

  mfvSum += mfv;

  auto [front, filled] = inputCache.push({mfv, v});

  if (!filled) {
    return {};
  }

  volSum -= front.vol;
  mfvSum -= front.mfv;

  return mfvSum / volSum;
}

} // namespace talib
