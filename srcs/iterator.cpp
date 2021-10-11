/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 22:06:31 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/11 21:16:17 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/iterator.hpp"

namespace ft
{
//	Constructors
	template<class Iterator>
	ft::reverse_iterator<Iterator>::reverse_iterator<class Iterator>()
	{
		this->current = 0;
	}

	template<class Iterator>
	ft::reverse_iterator<Iterator>::reverse_iterator<class Iterator>(
			iterator_type x)
	{
		this->current = x;
	}

	template<class Iterator, class U>
	ft::reverse_iterator<Iterator>::reverse_iterator<class Iterator>(
			const reverse_iterator<U> &other)
	{
		this->current = other.base();
	}

//	Member functions
//	operator=
	template<class Iterator, class U>
	reverse_iterator<Iterator>& ft::reverse_iterator<Iterator>::operator=
	        (const reverse_iterator<U>& other)
	{
		if (this == other)
			return *this;
		this->current = other.base();
		return *this;
	}

//	base()
	template<class Iterator>
	iterator_type ft::reverse_iterator<Iterator>::base() const
	{
		return this->current;
	}

//	operator *
	template<class Iterator>
	reference ft::reverse_iterator<Iterator>::operator*() const
	{
		Iterator tmp = this->current;

		return *--tmp;
	}
//	operator ->
	template<class Iterator>
	pointer ft::reverse_iterator<Iterator>::operator->() const
	{
		return &(operator*());
	}
//	operator []
	template<class Iterator>
	reference
		ft::reverse_iterator<Iterator>::operator[](difference_type n) const
	{
			return base()[-n-1];
	}
//	operator ++
	template<class Iterator>
	reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator++()
	{
		--(this->current);
		return *this;
	}
//	operator ++(int)
	template<class Iterator>
	reverse_iterator <Iterator> ft::reverse_iterator<Iterator>::operator++(int)
	{
		reverse_iterator tmp = *this;

		--(this->current);
		return tmp;
	}
//	operator --
	template<class Iterator>
	reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator--()
	{
		++(this->current);
		return *this;
	}
//	operator --(int)
	template<class Iterator>
	reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator--(int)
	{
		reverse_iterator tmp = *this;

		++(this->current);
		return tmp;
	}
//	operator +
	template<class Iterator>
	reverse_iterator<Iterator>
		ft::reverse_iterator<Iterator>::operator+(difference_type n) const
	{
		reverse_iterator tmp = *this;

		tmp.current = n;
		return *tmp;
	}
//	operator -
	template<class Iterator>
	reverse_iterator <Iterator>
		ft::reverse_iterator<Iterator>::operator-(difference_type n) const
	{
		reverse_iterator tmp = *this;

		tmp.current += n;
		return *tmp;
	}

//	operator +=
	template<class Iterator>
	reverse_iterator<Iterator>
		ft::reverse_iterator<Iterator>::operator+=(difference_type n) const
	{
		this->current -= n;
		return *this;
	}

//	operator -=
	template<class Iterator>
	reverse_iterator<Iterator>
		ft::reverse_iterator<Iterator>::operator-=(difference_type n) const
	{
		this->current += n;
		return *this;
	}
}
