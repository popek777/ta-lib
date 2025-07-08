#include <ta-lib/ATR.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <algorithm>
#include <cstdlib>

namespace talib {

ATR::ATR(uint32_t period)
    : period(period)
    , period_less_1(period - 1)
{
}

std::optional<double> ATR::nextVal(double close, double low, double high)
{
  if (0 == inputCnt) {
    ++inputCnt;

    // TR already have value at first sample
    avgTR += high - low;

    prevClose = close;
    prevLow = low;
    prevHigh = high;
    return {};
  }

  // claculate true range
  double TR = high - low;
  double TRhc = std::abs(high - prevClose);
  if (TRhc > TR) {
    TR = TRhc;
  }
  double TRlc = std::abs(low - prevClose);
  if (TRlc > TR) {
    TR = TRlc;
  }

  // we are safe to cache prev OHL
  prevClose = close;
  prevLow = low;
  prevHigh = high;

  // calculate ATR
  if (inputCnt <= period_less_1) {
    ++inputCnt;

    avgTR += TR;

    // compare against period_less_1+1 since inputCnt had been incremented
    if (inputCnt < period) {
      return {};
    }

    avgTR /= period;
    return avgTR;
  }

  avgTR = (avgTR * period_less_1 + TR) / period;
  return avgTR;
}

} // namespace talib
