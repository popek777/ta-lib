#include <ta-lib/Median.hpp>

#include <vector>
#include <sstream>
#include <iostream>

template<typename Indicator>
void test(Indicator i, const std::vector<double>& input)
{
  std::ostringstream ss;
  for (auto v : input) {
    auto out = i.nextVal(v);
    if (out.has_value())
      ss << *out;
    else
      ss << "None";
    ss << ", ";
  }
  std::cout << "out: " << ss.str() << std::endl;
}

int main (int argc, char* argv[])
{
  auto median = talib::Median(5);

  std::vector<double> input;
  for (auto i = 0; i < 30; ++i)
    input.push_back(i);

  for (auto v : input)
    auto out = median.nextVal(v);

  //test(talib::Median(5), input);

  return 0;
}
