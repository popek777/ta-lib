#pragma once

#include <vector>
#include <optional>

namespace talib {

class SortedWindow {
public:
  SortedWindow(std::size_t size);

  void push(std::optional<double> obsoleteValue, double newValue);

  double operator[](std::size_t idx) const { return buffer.at(idx); }

private:
  std::vector<double> buffer;
};

} // namespace talib
