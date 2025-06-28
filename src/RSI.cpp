#include <ta-lib/RSI.hpp>
#include <ta-lib/TaLibUtils.hpp>

namespace talib {

RSI::RSI(uint32_t period)
    : period(period)
    , period_1(period - 1)
{
}

std::optional<double> RSI::nextVal(double v)
{
  if (inputCnt <= period) {
    ++inputCnt;

    if (1 == inputCnt) {
      prevVal = v;
      return {};
    }

    if (v > prevVal) {
      avgGain += (v - prevVal);
    }
    else {
      avgLoss += (prevVal - v);
    }

    if (inputCnt <= period) {
      prevVal = v;
      return {};
    }

    avgGain /= period;
    avgLoss /= period;
  }
  else {

    double change = v - prevVal;
    avgGain = avgGain * (period_1) + (change > 0 ? change : 0);
    avgLoss = avgLoss * (period_1) - (change < 0 ? change : 0);
  }

  prevVal = v;
  if (isZero(avgLoss)) {
    return 100.;
  }
  return 100. - 100. / (1. + (avgGain / avgLoss));
}

} // namespace talib
