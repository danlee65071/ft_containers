/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:43:39 by hcharlsi          #+#    #+#             */
/*   Updated: 2022/01/06 14:43:40 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CONTAINERS_FT_STACK_HPP
#define FT_CONTAINERS_FT_STACK_HPP

# include <stack>
# include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	protected:
		container_type c;
	public:
		explicit stack (const container_type& ctnr = container_type()): c(ctnr) {}
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		value_type& top() { return c.back(); }
		const value_type& top() const { return c.back(); }
		void push (const value_type& val) { c.push_back(val); }
		void pop() { c.pop_back(); }

		template <class T1, class Container1>
		friend bool operator== (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

		template <class T1, class Container1>
		friend bool operator<  (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
	};

	template <class T1, class Container1>
	bool operator== (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class Container1>
	bool operator<  (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}

}

#endif
