/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_traits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:34:42 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/21 18:37:39 by                  ###   ########.fr       */
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

    //    remove_cv
    template< class T > struct remove_cv                   { typedef T type; };
    template< class T > struct remove_cv<const T>          { typedef T type; };
    template< class T > struct remove_cv<volatile T>       { typedef T type; };
    template< class T > struct remove_cv<const volatile T> { typedef T type; };

//    remove_const
    template< class T > struct remove_const                { typedef T type; };
    template< class T > struct remove_const<const T>       { typedef T type; };

//    remove_volatile
    template< class T > struct remove_volatile             { typedef T type; };
    template< class T > struct remove_volatile<volatile T> { typedef T type; };

//    is_same
    template<class T, class U>
    struct is_same : false_type {};

    template<class T>
    struct is_same<T, T> : std::true_type {};

//    is_floating_point
    template< class T >
    struct is_floating_point: integral_constant<bool, is_same<float, typename remove_cv<T>::type>::value
                                                      || is_same<double, typename remove_cv<T>::type>::value
                                                      || is_same<long double, typename remove_cv<T>::type>::value> {};

//    is_arithmetic
    template< class T >
    struct is_arithmetic: integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value> {};

//    is_pointer
    template<class T>
    struct is_pointer_helper: false_type {};

    template<class T>
    struct is_pointer_helper<T*>: true_type {};

    template<class T>
    struct is_pointer: is_pointer_helper<typename remove_cv<T>::type> {};

//    is_member_pointer
    template< class T >
    struct is_member_pointer_helper: false_type {};

    template< class T, class U >
    struct is_member_pointer_helper<T U::*>: true_type {};

    template< class T >
    struct is_member_pointer: is_member_pointer_helper<typename remove_cv<T>::type> {};

//    is_scalar
    template< class T >
    struct is_scalar : integral_constant<bool, is_arithmetic<T>::value || is_pointer<T>::value
            || is_member_pointer<T>::value> {};

//    is_array
    template<class T>
    struct is_array: false_type {};

    template<class T>
    struct is_array<T[]>: true_type {};

    template<class T, std::size_t N>
    struct is_array<T[N]>: true_type {};

//    void_t
    template<class>
    struct _void_t { typedef void type; };

//    is_union
    template <class T> struct is_union: public integral_constant<bool, __is_union(T)> {};

//    is_class
    struct _two {char lx[2];};
    namespace detail
    {
        template<class T>
        integral_constant<bool, !is_union<T>::value> test(int T::*);

        template<class>
        _two test(...);
    }

    template<class T>
    struct is_class: public integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !is_union<T>::value> {};

//    is_object
    template<class T>
    struct is_object: public integral_constant<bool, is_scalar<T>::value ||
                                                        is_array<T>::value ||
                                                        is_union<T>::value ||
                                                        is_class<T>::value > {};

}

#endif
