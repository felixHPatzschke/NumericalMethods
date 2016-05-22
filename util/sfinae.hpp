#ifndef _FHP_SFINAE_HPP_INCLUDED_
#define _FHP_SFINAE_HPP_INCLUDED_

#include <type_traits>


namespace sfinae
{

	template <class _op, class... _ty, typename = decltype(std::declval<_op>()(std::declval<_ty>()...))>
	std::true_type impl_test(const _op&, const _ty&...) { return std::true_type(); }
	std::false_type impl_test(...) { return std::false_type(); }
	template <class> struct supports;
	template <class _op, class... _ty> struct supports<_op(_ty...)> : decltype(impl_test(std::declval<_op>(), std::declval<_ty>()...)){};

}

#define is_ineq_supported(type) sfinae::supports<std::less<>(type, type)>()

#endif
