#include <ta-lib/Zscore.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <cmath>

namespace talib {

Zscore::Zscore(uint32_t period)
    : var(period)
{
}

std::optional<double> Zscore::nextVal(double v)
{
  auto varCtx = var.calcNext(v);

  if (!varCtx.var.has_value()) {
    return {};
  }

  // in case of  tiny negative errors
  // var is zero -> stddev is zero -> zscore is zero
  if (isZeroOrNeg(*varCtx.var)) {
    return 0.;
  }

  return (v - varCtx.mean) / std::sqrt(*varCtx.var);
}

} // namespace talib
