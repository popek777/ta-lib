#include <ta-lib/RangeCache.hpp>

namespace talib {

RangeCache::RangeCache(std::size_t size) { buffer.reserve(size); }

bool RangeCache::push(double v)
{
  if (buffer.size() < buffer.capacity()) {
    buffer.push_back(v);
    return false;
  }

  idx = (idx + 1) % buffer.size();
  buffer[idx] = v;
  return true;
}

double RangeCache::front() const { return buffer[(idx + 1) % buffer.size()]; }

} // namespace talib
