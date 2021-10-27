/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:02:37 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/13 16:47:10 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include "iterator"
#include <vector>

namespace ft
{
	template<class T, class Allocator = std::allocator<T>>
	class vector
	{
	private:
		T *arr;
		size_t sz;
		size_t cap;
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef Allocator::pointer pointer;
		typedef Allocator::const_pointer const_pointer;
		typedef ft::iterator_traits<pointer> iterator;
		typedef ft::iterator_traits<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::const_reverse_iterator<const_iterator>
				const_reverse_iterator;

		vector();
	};
}

#endif
