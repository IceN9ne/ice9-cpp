#ifndef ICE9_MATH_H
#define ICE9_MATH_H

#include <cmath>

namespace ice9
{
  namespace literals::math
  {
    constexpr double operator""_deg(long double value)
    {
      return value * M_PI / 180;
    }

    constexpr double operator""_deg(unsigned long long int value)
    {
      return value * M_PI / 180;
    }

    constexpr double operator""_rad(long double value)
    {
      return value;
    }

    constexpr double operator""_rad(unsigned long long int value)
    {
      return value;
    }
  }

  namespace literals
  {
    using namespace ice9::literals::math;
  }
}

#endif // ICE9_MATH_H
