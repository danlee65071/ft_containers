/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_traits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:34:42 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/14 22:09:27 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_TYPE_TRAITS_HPP
#define FT_CONTAINERS_FT_TYPE_TRAITS_HPP

#include <type_traits>

namespace ft
{
//	enable_if false
	template<bool B, class T = void>
	struct enable_if
	{};

//	enable_if true
	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

//	integral_constant
	template<class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const {return value;}
	};

//	true_type
	typedef integral_constant<bool, true> true_type;
//	false_type
	typedef integral_constant<bool, false> false_type;

//	is_integral
	template<class T> struct is_integral: public false_type {};
	template<> struct is_integral<bool>: public true_type {};
	template<> struct is_integral<char>: public true_type {};
	template<> struct is_integral<signed char>: public true_type {};
	template<> struct is_integral<unsigned char>: public true_type {};
	template<> struct is_integral<wchar_t>: public true_type {};
	template<> struct is_integral<char16_t>: public true_type {};
	template<> struct is_integral<char32_t>: public true_type {};
	template<> struct is_integral<short>: public true_type {};
	template<> struct is_integral<unsigned short>: public true_type {};
	template<> struct is_integral<int>: public true_type {};
	template<> struct is_integral<unsigned int>: public true_type {};
	template<> struct is_integral<long>: public true_type {};
	template<> struct is_integral<unsigned long>: public true_type {};
	template<> struct is_integral<long long>: public true_type {};
	template<> struct is_integral<unsigned long long>: public true_type {};
}

#endif
