/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:00:44 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/10 23:41:57 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>

namespace ft
{
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class Iterator>
	class reverse_iterator: public std::iterator<
	        typename ft::iterator_traits<Iterator>::iterator_category,
	        typename ft::iterator_traits<Iterator>::value_type,
	        typename ft::iterator_traits<Iterator>::difference_type,
	        typename ft::iterator_traits<Iterator>::pointer,
	        typename ft::iterator_traits<Iterator>::reference,>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator iterator_type;
		typedef ft::iterator_traits<Iterator>::iterator_category
			iterator_category;
		typedef ft::iterator_traits<Iterator>::value_type value_type;
		typedef ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef ft::iterator_traits<Iterator>::pointer pointer;
		typedef ft::iterator_traits<Iterator>::reference reference;

//		Constructors
		reverse_iterator();
		explicit reverse_iterator(iterator_type x);
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other);

//		Destructor
		~reverse_iterator();


	};
}

#endif
