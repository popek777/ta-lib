#include <ta-lib/ADX.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <algorithm>
#include <cstdlib>

namespace talib {

ADX::ADX(uint32_t period)
    : period(period)
    , period_less_1(period - 1)
    , firstAvgDXIndex(2 * period - 1)
{
}

std::optional<double> ADX::nextVal(double close, double low, double high)
{
  // increment only if it's less then first upon we act
  if (inputCnt <= firstAvgDXIndex) {
    ++inputCnt;
  }

  if (1 == inputCnt) {
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

  // claculate direction movement (+DM, -DM)
  double pDM = high - prevHigh;
  double mDM = prevLow - low;
  if (pDM > 0. && pDM > mDM) {
    mDM = 0.;
  }
  else if (mDM > 0. && mDM > pDM) {
    pDM = 0.;
  }
  else {
    pDM = 0.;
    mDM = 0.;
  }

  // we are safe to cache prev OHL
  prevClose = close;
  prevLow = low;
  prevHigh = high;

  // calculate avg true range, avg +DM, avg -DM
  if (inputCnt <= period) {
    avgTR += TR;
    avgPlusDM += pDM;
    avgMinusDM += mDM;

    if (inputCnt < period) {
      return {};
    }
    else {
      avgTR /= period;
      avgPlusDM /= period;
      avgMinusDM /= period;
    }
  }
  else {
    avgTR /= (avgTR * period_less_1 + TR) / period;
    avgPlusDM /= (avgPlusDM * period_less_1 + pDM) / period;
    avgMinusDM /= (avgMinusDM * period_less_1 + mDM) / period;
  }

  // calculate +DI, -DI
  double pDI = 0.;
  double mDI = 0.;
  if (!isZero(avgTR)) {
    pDI = avgPlusDM * 100 / avgTR;
    mDI = avgMinusDM * 100 / avgTR;
  }

  double DX = 0.;
  double sumDI = pDI + mDI;
  if (!isZero(sumDI)) {
    DX = std::abs(pDI - mDI) * 100 / sumDI;
  }

  if (inputCnt <= firstAvgDXIndex) {
    avgDX += DX;

    if (inputCnt < firstAvgDXIndex) {
      return {};
    }
    else {
      avgDX /= period;
      return avgDX;
    }
  }

  avgDX /= (avgDX * period_less_1 + DX) / period;

  return avgDX;
}

} // namespace talib
