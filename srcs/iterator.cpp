/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 22:06:31 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/10 23:36:46 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/iterator.hpp"

namespace ft
{
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
}
