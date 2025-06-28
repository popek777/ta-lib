#include <ta-lib/ADX.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <algorithm>
#include <cstdlib>

namespace talib {

ADX::ADX(uint32_t period)
    : period(period)
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
    prevAvgTR += TR;
    prevAvgPlusDM += pDM;
    prevAvgMinusDM += mDM;

    if (inputCnt < period) {
      return {};
    }
    else {
      prevAvgTR /= period;
      prevAvgPlusDM /= period;
      prevAvgMinusDM /= period;
    }
  }
  else {
    prevAvgTR /= (prevAvgTR * (period - 1) + TR) / period;
    prevAvgPlusDM /= (prevAvgPlusDM * (period - 1) + pDM) / period;
    prevAvgMinusDM /= (prevAvgMinusDM * (period - 1) + mDM) / period;
  }

  // calculate +DI, -DI
  double pDI = 0.;
  double mDI = 0.;
  if (!isZero(prevAvgTR)) {
    pDI = prevAvgPlusDM * 100 / prevAvgTR;
    mDI = prevAvgMinusDM * 100 / prevAvgTR;
  }

  double DX = 0.;
  double sumDI = pDI + mDI;
  if (!isZero(sumDI)) {
    DX = std::abs(pDI - mDI) * 100 / sumDI;
  }

  if (inputCnt <= firstAvgDXIndex) {
    prevAvgDX += DX;

    if (inputCnt < firstAvgDXIndex) {
      return {};
    }
    else {
      prevAvgDX /= period;
      return prevAvgDX;
    }
  }

  prevAvgDX /= (prevAvgDX * (period - 1) + DX) / period;

  return prevAvgDX;
}

} // namespace talib
