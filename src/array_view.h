#ifndef ICE9_ARRAY_VIEW_H
#define ICE9_ARRAY_VIEW_H

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

namespace ice9
{
  template <typename T>
  class reverse_array_view;

  template <typename T>
  class array_view
  {
  public:
    using value_type      = T;
    using size_type       = size_t;
    using const_pointer   = const value_type*;
    using pointer         = const_pointer;
    using const_reference = const value_type&;
    using reference       = const_reference;
    using const_iterator  = const_pointer;
    using iterator        = const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = const_reverse_iterator;
    using difference_type = ptrdiff_t;

    constexpr array_view() noexcept = default;
    constexpr array_view(const array_view&) noexcept = default;
    constexpr array_view(array_view&&) noexcept = default;

    constexpr array_view& operator=(const array_view&) noexcept = default;
    constexpr array_view& operator=(array_view&&) noexcept = default;

    explicit constexpr array_view(pointer ptr, size_type len) noexcept : dataptr{ptr}, datalen{len} {}
    explicit constexpr array_view(pointer b, pointer e) noexcept : dataptr{b}, datalen(std::distance(b,e)) {}

    template <typename Cont>
    constexpr array_view(const Cont& cont):array_view{std::begin(cont),std::end(cont)} {}

    constexpr const_iterator begin() const noexcept { return dataptr; }
    constexpr const_iterator end() const noexcept { return begin() + size(); }

    constexpr const_iterator cbegin() const noexcept { return begin(); }
    constexpr const_iterator cend() const noexcept { return end(); }

    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator{end()}; }
    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator{begin()}; }

    constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    constexpr const_reverse_iterator crend() const noexcept { return rend(); }

    constexpr size_type size() const noexcept { return datalen; }
    constexpr size_type length() const noexcept { return size(); }

    constexpr bool empty() const noexcept { return size() == 0; }

    constexpr const_reference operator[](size_type pos) const noexcept { return *(begin() + pos); }
    constexpr const_reference at(size_type pos) const
    {
      // FIXME: throw std::out_of_range if pos >= datalen
      return *(begin() + pos);
    }

    constexpr const_reference front() const noexcept { return *begin(); }
    constexpr const_reference back() const noexcept { return *(end() - 1); }

    constexpr const_pointer data() const noexcept { return dataptr; }

    constexpr void swap(array_view& av) noexcept { std::swap(dataptr, av.data_ptr); std::swap(datalen, av.datalen); }

    constexpr reverse_array_view<T> reverse() const noexcept { return reverse_array_view{*this}; }

    constexpr bool starts_with(array_view av) const noexcept { if (av.size() > size()) return false; return std::equal(begin(), end(), av.begin()); }
    constexpr bool ends_with(array_view av) const noexcept { if (av.size() > size()) return false; return std::equal(rbegin(), rend(), av.rbegin()); }

    constexpr array_view<T>& remove_prefix(size_type n)
    {
      // FIXME: if n >= datalen
      dataptr += n;
      datalen -= n;
      return *this;
    }
    constexpr array_view<T>& remove_suffix(size_type n)
    {
      // FIXME: if n >= datalen
      datalen -= n;
      return *this;
    }

    std::vector<array_view<T>> split(array_view delem) const
    {
      std::vector<array_view<T>> results;
      if (delem.size() > size())
        return results;

      auto temp = begin();
      for (auto it = temp; it != end(); ++it) {
        if (std::equal(delem.begin(), delem.end(), it)) {
          results.emplace_back(temp, it);
          std::advance(it, static_cast<ptrdiff_t>(delem.size()) - 1);
          temp = std::next(it);
        }
        else if (std::distance(it, end()) <= static_cast<ptrdiff_t>(delem.size())) {
          results.emplace_back(temp, end());
          break;
        }
      }

      return results;
    }

  private:
    pointer dataptr = nullptr;
    size_type datalen = 0;
  };

  template <typename T>
  constexpr bool operator==(array_view<T> lhs, array_view<T> rhs) noexcept
  {
    if (lhs.size() != rhs.size())
      return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  template <typename T>
  constexpr bool operator==(array_view<T> lhs, reverse_array_view<T> rhs) noexcept
  {
    if (lhs.size() != rhs.size())
      return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }


  template <typename T>
  constexpr bool operator!=(array_view<T> lhs, array_view<T> rhs) noexcept
  {
    return !(lhs == rhs);
  }

  template <typename T>
  constexpr bool operator!=(array_view<T> lhs, reverse_array_view<T> rhs) noexcept
  {
    return !(lhs == rhs);
  }

  template <typename T>
  class reverse_array_view : private array_view<T>
  {
  public:
    using typename array_view<T>::value_type;
    using typename array_view<T>::size_type;
    using typename array_view<T>::const_pointer;
    using typename array_view<T>::pointer;
    using typename array_view<T>::const_reference;
    using typename array_view<T>::reference;
    using const_iterator = typename array_view<T>::const_reverse_iterator;
    using iterator       = typename array_view<T>::reverse_iterator;
    using const_reverse_iterator = typename array_view<T>::const_iterator;
    using reverse_iterator       = typename array_view<T>::iterator;
    using typename array_view<T>::difference_type;

    constexpr reverse_array_view() noexcept = default;
    constexpr reverse_array_view(const reverse_array_view&) noexcept = default;
    constexpr reverse_array_view(reverse_array_view&&) noexcept = default;

    constexpr reverse_array_view<T>& operator=(const reverse_array_view&) noexcept = default;
    constexpr reverse_array_view<T>& operator=(reverse_array_view&&) noexcept = default;

    explicit constexpr reverse_array_view(array_view<T> av) noexcept : array_view<T>{av}{}
    explicit constexpr reverse_array_view(pointer ptr, size_type len) noexcept : array_view<T>{ptr,len} {}

    constexpr const_iterator begin() const noexcept { return array_view<T>::rbegin(); }
    constexpr const_iterator end() const noexcept { return array_view<T>::rend(); }

    constexpr const_iterator cbegin() const noexcept { return array_view<T>::crbegin(); }
    constexpr const_iterator cend() const noexcept { return array_view<T>::crend(); }

    constexpr const_reverse_iterator rbegin() const noexcept { return array_view<T>::begin(); }
    constexpr const_reverse_iterator rend() const noexcept { return array_view<T>::end(); }

    constexpr const_reverse_iterator crbegin() const noexcept { return array_view<T>::cbegin(); }
    constexpr const_reverse_iterator crend() const noexcept { return array_view<T>::cend(); }

    using array_view<T>::size;
    using array_view<T>::length;
    using array_view<T>::empty;

    constexpr const_reference operator[](size_type pos) const noexcept { return *(begin() + pos); }
    constexpr const_reference at(size_type pos) const
    {
      // FIXME: throw std::out_of_range if pos >= datalen
      return *(begin() + pos);
    }

    constexpr const_reference front() const noexcept { return array_view<T>::back(); }
    constexpr const_reference back() const noexcept { return array_view<T>::front(); }

    using array_view<T>::data;

    using array_view<T>::swap;

    constexpr array_view<T> reverse() const noexcept { return array_view{data(), size()}; }

    using array_view<T>::starts_with;
    using array_view<T>::ends_with;

    constexpr reverse_array_view<T>& remove_prefix(size_type n) const noexcept
    {
      array_view<T>::remove_suffix(n);
      return *this;
    }
    constexpr reverse_array_view<T>& remove_suffix(size_type n) const noexcept
    {
      array_view<T>::remove_prefix(n);
      return *this;
    }
  };

  template <typename T>
  bool operator==(reverse_array_view<T> lhs, reverse_array_view<T> rhs) noexcept
  {
    if (lhs.size() != rhs.size())
      return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  template <typename T>
  bool operator==(reverse_array_view<T> lhs, array_view<T> rhs) noexcept
  {
    if (lhs.size() != rhs.size())
      return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  template <typename T>
  bool operator!=(reverse_array_view<T> lhs, reverse_array_view<T> rhs) noexcept
  {
    return !(lhs == rhs);
  }

  template <typename T>
  bool operator!=(reverse_array_view<T> lhs, array_view<T> rhs) noexcept
  {
    return !(lhs == rhs);
  }

  template <typename T>
  array_view(const T* ptr, size_t len) -> array_view<T>;

  template <typename T>
  array_view(const T* begin, const T* end) -> array_view<T>;

  template <typename Cont>
  array_view(Cont cont) -> array_view<typename Cont::value_type>;

  template <typename T>
  reverse_array_view(const T* ptr, size_t len) -> reverse_array_view<T>;
}

#endif // ICE9_ARRAY_VIEW_H
