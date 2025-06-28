#include <ta-lib/TaLibUtils.hpp>

namespace talib {

constexpr double epsilon{0.00000000000001};
bool isZero(double v) { return ((-epsilon) < v) && (v < epsilon); }

} // namespace talib
