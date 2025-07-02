#include <ta-lib/StdDev.hpp>
#include <ta-lib/TaLibUtils.hpp>

#include <cmath>

namespace talib {

StdDev::StdDev(uint32_t period)
    : var(period)
{
}

std::optional<double> StdDev::nextVal(double v)
{
  auto variance = var.nextVal(v);
  if (!variance.has_value()) {
    return {};
  }

  // in case of  tiny negative errors
  if (isZeroOrNeg(*variance)) {
    return 0.;
  }

  return std::sqrt(*variance);
}

} // namespace talib
