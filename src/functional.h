#include <functional>
#include <type_traits>

namespace ice9
{
  template <typename T = void>
  struct even;

  template <typename T>
  struct even : public std::unary_function<bool, T>
  {
    constexpr auto operator()(const T& i) const -> std::enable_if_t<std::is_integral_v<T>, bool>
    {
      return i % 2 == 0;
    }
  };

  template <>
  struct even<void>
  {
    template <typename T>
    constexpr bool operator()(const T& i) const
    {
      return even<T>()(i);
    }
  };

  template <typename T = void>
  struct odd;

  template <typename T>
  struct odd : public std::unary_function<bool, T>
  {
    constexpr auto operator()(const T& i) const -> std::enable_if_t<std::is_integral_v<T>, bool>
    {
      return !even<T>()(i);
    }
  };

  template <>
  struct odd<void>
  {
    template <typename T>
    constexpr bool operator()(const T& i) const
    {
      return odd<T>()(i);
    }
  };
}
