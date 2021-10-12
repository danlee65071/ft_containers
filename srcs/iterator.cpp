/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 22:06:31 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/12 01:01:42 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/iterator.hpp"

namespace ft
{
//	Member functions
//	Constructors
//	template<class Iterator>
//	reverse_iterator<Iterator>::reverse_iterator()
//	{
//		this->current = 0;
//	}

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(iterator_type x)
	{
		this->current = x;
	}

	template<class Iterator>
	template<class U>
	reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U> &other)
	{
		this->current = other.base();
	}

//	Member functions
//	operator=
	template<class Iterator>
	template<class U>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator=
	        (const reverse_iterator<U>& other)
	{
		if (this == other)
			return *this;
		this->current = other.base();
		return *this;
	}

//	base()
	template<class Iterator>
	typename reverse_iterator<Iterator>::iterator_type
		reverse_iterator<Iterator>::base() const
	{
		return this->current;
	}

//	operator *
	template<class Iterator>
	typename reverse_iterator<Iterator>::reference
		reverse_iterator<Iterator>::operator*() const
	{
		Iterator tmp = this->current;

		return *--tmp;
	}
//	operator ->
	template<class Iterator>
	typename reverse_iterator<Iterator>::pointer
		reverse_iterator<Iterator>::operator->() const
	{
		return &(operator*());
	}
//	operator []
	template<class Iterator>
	typename reverse_iterator<Iterator>::reference
		reverse_iterator<Iterator>::operator[](difference_type n) const
	{
			return base()[-n-1];
	}
//	operator ++
	template<class Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator++()
	{
		--(this->current);
		return *this;
	}
//	operator ++(int)
	template<class Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int)
	{
		reverse_iterator tmp = *this;

		--(this->current);
		return tmp;
	}
//	operator --
	template<class Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator--()
	{
		++(this->current);
		return *this;
	}
//	operator --(int)
	template<class Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int)
	{
		reverse_iterator tmp = *this;

		++(this->current);
		return tmp;
	}
//	operator +
	template<class Iterator>
	reverse_iterator<Iterator>
		reverse_iterator<Iterator>::operator+(difference_type n) const
	{
		reverse_iterator tmp = *this;

		tmp.current = n;
		return *tmp;
	}
//	operator -
	template<class Iterator>
	reverse_iterator<Iterator>
		reverse_iterator<Iterator>::operator-(difference_type n) const
	{
		reverse_iterator tmp = *this;

		tmp.current += n;
		return *tmp;
	}

//	operator +=
	template<class Iterator>
	reverse_iterator<Iterator>
		reverse_iterator<Iterator>::operator+=(difference_type n) const
	{
		this->current -= n;
		return *this;
	}

//	operator -=
	template<class Iterator>
	reverse_iterator<Iterator>
	        reverse_iterator<Iterator>::operator-=(difference_type n) const
	{
		this->current += n;
		return *this;
	}

//	Non-member functions
//	operator ==
//	template<class Iterator1, class Iterator2>
//	bool operator==(const reverse_iterator<Iterator1> lhs,
//						const reverse_iterator<Iterator2> rhs)
//	{
//		if (lhs.)
//	}
}
