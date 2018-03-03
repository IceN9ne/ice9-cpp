#ifndef ICE9_ALGORITHM_H
#define ICE9_ALGORITHM_H

#include <algorithm>

namespace ice9
{
  template <typename InputIt, typename T>
#if __cplusplus > 201703L
  constexpr
#endif
  bool
  contains(InputIt first, InputIt last, const T& value)
  {
    return std::find(first, last, value) != last;
  }

  template <typename ExecutionPolicy, typename ForwardIt, typename T>
  bool
  contains(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T& value)
  {
    return std::find(std::forward<ExecutionPolicy>(policy), first, last, value) != last;
  }

  template <typename InputIt, typename UnaryPredicate>
#if __cplusplus > 201703L
  constexpr
#endif
  bool
  contains_if(InputIt first, InputIt last, UnaryPredicate p)
  {
    return std::find_if(first, last, p) != last;
  }

  template <typename ExecutionPolicy, typename ForwardIt, typename UnaryPredicate>
  bool
  contains_if(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p)
  {
    return std::find_if(std::forward<ExecutionPolicy>(policy), first, last, p) != last;
  }

  template <typename InputIt, typename UnaryPredicate>
#if __cplusplus > 201703L
  constexpr
#endif
  bool
  contains_if_not(InputIt first, InputIt last, UnaryPredicate p)
  {
    return std::find_if_not(first, last, p) != last;
  }

  template <typename ExecutionPolicy, typename ForwardIt, typename UnaryPredicate>
  bool
  contains_if_not(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p)
  {
    return std::find_if_not(std::forward<ExecutionPolicy>(policy), first, last, p) != last;
  }
}

#endif // ICE9_ALGORITHM_H
