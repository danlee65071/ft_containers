/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:00:44 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/12 00:57:42 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>
#include <memory>

namespace ft
{
//	iterator traits
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

//	reverse_iterator
	template<class Iterator>
	class reverse_iterator: public std::iterator<
	        typename iterator_traits<Iterator>::iterator_category,
	        typename iterator_traits<Iterator>::value_type,
	        typename iterator_traits<Iterator>::difference_type,
	        typename iterator_traits<Iterator>::pointer,
	        typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
	public:
//		Member types
		typedef Iterator iterator_type;
//		typedef typename iterator_traits<Iterator>::iterator_category
//			iterator_category;
//		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type
			difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

//		Constructors
		reverse_iterator(): current() {};
		explicit reverse_iterator(iterator_type x);
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other);

//		Destructor
		~reverse_iterator(){};

//		Member functions
		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other);
		iterator_type base() const;
		reference operator*() const;
		pointer operator->() const;
		reference operator[] (difference_type n) const;
		reverse_iterator& operator++();
		reverse_iterator operator++(int);
		reverse_iterator& operator--();
		reverse_iterator operator--(int);
		reverse_iterator operator+(difference_type n) const;
		reverse_iterator operator-(difference_type n) const;
		reverse_iterator operator+=(difference_type n) const;
		reverse_iterator operator-=(difference_type n) const;
	};

//	template <class Iterator1, class Iterator2>
//	bool operator==(const reverse_iterator<Iterator1> lhs,
//					const reverse_iterator<Iterator2> rhs);
}

#endif
