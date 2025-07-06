#pragma once

#include <vector>

namespace talib {

template<typename T, typename ReturnT = T>
class RangeCacheT {
public:
  RangeCacheT(std::size_t size) { buffer.reserve(size); }

  // return first element of a range (since it will be replaced with pushed value)
  // and bool indicating if range is filled
  std::pair<ReturnT, bool> push(T v)
  {
    if (buffer.size() < buffer.capacity()) {
      ++idx;
      buffer.push_back(v);

      // front (is mimicked to 0 even if buffer is filled)
      return {ReturnT{}, buffer.size() == buffer.capacity()};
    }

    idx = (idx + 1) % buffer.size();

    // since front will be removed let's return it to a caller
    auto front = buffer[idx];
    buffer[idx] = v;

    return {front, true};
  }

private:
  std::vector<T> buffer;
  std::size_t idx{static_cast<std::size_t>(-1)};
};

using RangeCache = RangeCacheT<double>;

} // namespace talib
