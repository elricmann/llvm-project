//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___CXX03___COMPARE_PARTIAL_ORDER
#define _LIBCPP___CXX03___COMPARE_PARTIAL_ORDER

#include <__cxx03/__compare/compare_three_way.h>
#include <__cxx03/__compare/ordering.h>
#include <__cxx03/__compare/weak_order.h>
#include <__cxx03/__config>
#include <__cxx03/__type_traits/decay.h>
#include <__cxx03/__type_traits/is_same.h>
#include <__cxx03/__utility/forward.h>
#include <__cxx03/__utility/priority_tag.h>

#ifndef _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

#if _LIBCPP_STD_VER >= 20

// [cmp.alg]
namespace __partial_order {
void partial_order() = delete;

struct __fn {
  // NOLINTBEGIN(libcpp-robust-against-adl) partial_order should use ADL, but only here
  template <class _Tp, class _Up>
    requires is_same_v<decay_t<_Tp>, decay_t<_Up>>
  _LIBCPP_HIDE_FROM_ABI static constexpr auto __go(_Tp&& __t, _Up&& __u, __priority_tag<2>) noexcept(
      noexcept(partial_ordering(partial_order(std::forward<_Tp>(__t), std::forward<_Up>(__u)))))
      -> decltype(partial_ordering(partial_order(std::forward<_Tp>(__t), std::forward<_Up>(__u)))) {
    return partial_ordering(partial_order(std::forward<_Tp>(__t), std::forward<_Up>(__u)));
  }
  // NOLINTEND(libcpp-robust-against-adl)

  template <class _Tp, class _Up>
    requires is_same_v<decay_t<_Tp>, decay_t<_Up>>
  _LIBCPP_HIDE_FROM_ABI static constexpr auto __go(_Tp&& __t, _Up&& __u, __priority_tag<1>) noexcept(
      noexcept(partial_ordering(compare_three_way()(std::forward<_Tp>(__t), std::forward<_Up>(__u)))))
      -> decltype(partial_ordering(compare_three_way()(std::forward<_Tp>(__t), std::forward<_Up>(__u)))) {
    return partial_ordering(compare_three_way()(std::forward<_Tp>(__t), std::forward<_Up>(__u)));
  }

  template <class _Tp, class _Up>
    requires is_same_v<decay_t<_Tp>, decay_t<_Up>>
  _LIBCPP_HIDE_FROM_ABI static constexpr auto __go(_Tp&& __t, _Up&& __u, __priority_tag<0>) noexcept(
      noexcept(partial_ordering(std::weak_order(std::forward<_Tp>(__t), std::forward<_Up>(__u)))))
      -> decltype(partial_ordering(std::weak_order(std::forward<_Tp>(__t), std::forward<_Up>(__u)))) {
    return partial_ordering(std::weak_order(std::forward<_Tp>(__t), std::forward<_Up>(__u)));
  }

  template <class _Tp, class _Up>
  _LIBCPP_HIDE_FROM_ABI constexpr auto operator()(_Tp&& __t, _Up&& __u) const
      noexcept(noexcept(__go(std::forward<_Tp>(__t), std::forward<_Up>(__u), __priority_tag<2>())))
          -> decltype(__go(std::forward<_Tp>(__t), std::forward<_Up>(__u), __priority_tag<2>())) {
    return __go(std::forward<_Tp>(__t), std::forward<_Up>(__u), __priority_tag<2>());
  }
};
} // namespace __partial_order

inline namespace __cpo {
inline constexpr auto partial_order = __partial_order::__fn{};
} // namespace __cpo

#endif // _LIBCPP_STD_VER >= 20

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___CXX03___COMPARE_PARTIAL_ORDER
