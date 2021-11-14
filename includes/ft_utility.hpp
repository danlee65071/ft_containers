/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:18:21 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/14 22:09:27 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_UTILITY_HPP
#define FT_CONTAINERS_FT_UTILITY_HPP

#include "utility"

namespace ft
{
//	pair
	template<class T1, class T2>
	struct pair
	{
//		member types
		typedef T1 first_type;
		typedef T2 second_type;

//		member objects
		T1 first;
		T2 second;

//		Constructors
		pair(): first(), second() {}
		pair(const T1& x, const T2& y): first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2>& p): first(p.first), second(p.second) {}

//		operator =
		pair& operator=(const pair& other)
		{
			this->first = other.first;
			this->second = other.second;
			return *this;
		}
	};

//	non-member functions
//	operator==
	template<class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return  lhs.first == rhs.first && lhs.second == rhs.second;
	}

//	operator!=
	template<class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

//	operator<
	template<class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first)
			&& lhs.second < rhs.second));
	}

//	operator<=
	template<class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

//	operator>
	template<class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs < lhs;
	}

//	operator>=
	template<class T1, class T2>
	bool operator>=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

//	make_pair
	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}
}

#endif
