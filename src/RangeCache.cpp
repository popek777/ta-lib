#include <ta-lib/RangeCache.hpp>

namespace talib {

RangeCache::RangeCache(std::size_t size) { buffer.reserve(size); }

std::pair<double, bool> RangeCache::push(double v)
{
  if (buffer.size() < buffer.capacity()) {
    ++idx;
    buffer.push_back(v);
    // front (is mimicked to 0 even if buffer is filled)
    return {0., buffer.size() == buffer.capacity()};
  }

  idx = (idx + 1) % buffer.size();

  // since front will be removed let's return it to a caller
  auto front = buffer[idx];
  buffer[idx] = v;

  return {front, true};
}

} // namespace talib
