#ifndef ICE9_TYPE_TRAITS_H
#define ICE9_TYPE_TRAITS_H

#include <type_traits>

namespace ice9
{
  template <typename T>
  struct deferred_false : std::false_type
  {
  };

  template <typename T>
  inline constexpr bool deferred_false_v = deferred_false<T>::value;

  template <typename T>
  struct deferred_true : std::true_type
  {
  };

  template <typename T>
  inline constexpr bool deferred_true_v = deferred_true<T>::value;
}

#endif // ICE9_TYPE_TRAITS_H
