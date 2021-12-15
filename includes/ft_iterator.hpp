/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:00:44 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/20 02:37:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include "ft_type_traits.hpp"

namespace ft
{
//    iterarot_tags
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//    Iterator
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

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
		typedef random_access_iterator_tag iterator_category;
	};

//    advance
    template<class InputIterator>
    inline void _advance(InputIterator& it,
                        typename iterator_traits<InputIterator>::difference_type n, input_iterator_tag)
    {
        for (; n > 0; --n)
            ++it;
    }

    template<class BidirectionalIterator>
    inline void _advance(BidirectionalIterator& it,
                         typename iterator_traits<BidirectionalIterator>::difference_type n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            for (; n > 0;--n)
                ++it;
        else
            for (; n < 0; ++n)
                --it;
    }

    template<class RandomAccessIterator>
    inline void _advance(RandomAccessIterator& it,
                         typename iterator_traits<RandomAccessIterator>::difference_type n,
                         random_access_iterator_tag)
    {
        it += n;
    }

    template<class Iterator, class Distance>
    inline void advance(Iterator& it, Distance n)
    {
        int int_n = static_cast<int>(n);
        _advance(it, int_n, typename iterator_traits<Iterator>::iterator_category());
    }

//	next
	template <class _InputIter>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	typename enable_if<std::__is_input_iterator<_InputIter>::value,_InputIter>::type
	next(_InputIter __x,
	typename iterator_traits<_InputIter>::difference_type __n = 1)
{
	_VSTD::advance(__x, __n);
	return __x;
}

//    distance
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n(0);
        for (; first != last; ++first)
            ++n;
        return n;
    }

    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::difference_type
    distance(Iterator first, Iterator last)
    {
        return _distance(first, last, typename iterator_traits<Iterator>::iterator_category());
    }

//	reverse_iterator
	template<class Iterator>
	class reverse_iterator: public iterator<
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
		typedef typename iterator_traits<Iterator>::iterator_category
			iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type
			difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

//		Constructors
		reverse_iterator(): current() {};
		explicit reverse_iterator(iterator_type x): current(x) {};
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other):
			current(other.base()) {};

//		Destructor
		~reverse_iterator(){};

//		Member functions
//		operator=
		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other)
		{
			this->current = static_cast<reverse_iterator<Iterator> >(other.base());
			return *this;
		};
//		base()
		iterator_type base() const
		{
			return this->current;
		};
//		operator*
		reference operator*() const
		{
			Iterator tmp = this->current;

			return *--tmp;
//			return *(this->current);
		};
//		operator->
		pointer operator->() const
		{
			return &(operator*());
		};
//		operator[]
		reference operator[] (difference_type n) const
		{
			return *(*this + n);
		};
//		operator++
		reverse_iterator& operator++()
		{
			--(this->current);
			return *this;
		};
//		operator++(int)
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);

			--(this->current);
			return tmp;
		};
//		operator--
		reverse_iterator& operator--()
		{
			++(this->current);
			return *this;
		};
//		operator--(int)
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;

			++(this->current);
			return tmp;
		};
//		operator+
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->current - n);
		};
//		operator-
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		};
//		operator+=
		reverse_iterator operator+=(difference_type n) const
		{
			this->current -= n;
			return *this;
		};
//		operator-=
		reverse_iterator operator-=(difference_type n) const
		{
			this->current += n;
			return *this;
		};
	};

//	non-member functions

//	operator ==
	template<class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs,
			const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

//	operator !=
	template<class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	}

//	operator <
	template<class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs,
				   const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base();
	}

//	operator <=
	template<class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

//	operator >
	template<class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs,
				   const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

//	operator >=
	template<class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

//	operator+(reverse_iterator)
	template<class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,
			const reverse_iterator<Iter>& it)
	{
		return reverse_iterator<Iter>(it.base() - n);
	}

//	operator-(reverse_iterator)
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}

#endif
