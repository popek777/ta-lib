#include <ta-lib/SortedWindow.hpp>

#include <algorithm>

namespace talib {

SortedWindow::SortedWindow(std::size_t size) { buffer.reserve(size); }

void SortedWindow::push(std::optional<double> obsoleteValue, double newValue)
{
  if (obsoleteValue.has_value()) {
    if (auto it = std::find(buffer.begin(), buffer.end(), *obsoleteValue); it != buffer.end()) {
      buffer.erase(it);
    }
  }
  buffer.insert(std::lower_bound(buffer.begin(), buffer.end(), newValue), newValue);
}

} // namespace talib
