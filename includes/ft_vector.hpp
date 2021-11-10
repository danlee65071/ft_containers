/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:02:37 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/10 14:58:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_VECTOR_HPP
#define FT_CONTAINERS_FT_VECTOR_HPP

# include <memory>
# include "ft_iterator.hpp"
# include "ft_utility.hpp"
# include <algorithm>
# include <limits>
# include <stdexcept>
# include "ft_type_traits.hpp"
# include <type_traits>

#include <vector>

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::iterator_traits<pointer> iterator;
		typedef ft::iterator_traits<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>
				const_reverse_iterator;

//      constructors
/***********************************************************************************************************************/
//      default constructor
        explicit vector(const allocator_type& alloc = allocator_type()): begin(0), end(0), capacity(0), alloc(alloc) {}
//      range constructor
        template<class InputIterator, typename enable_if<!is_integral<InputIterator>::value,
                typename iterator_traits<InputIterator>::iterator_category::value>::type >
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
//      fill constructor
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
//      copy constructor
        vector(const vector& x);
/***********************************************************************************************************************/

//        Member functions
/***********************************************************************************************************************/
//        max_size
        size_type max_size() const;
//        size
        size_type size() const;
//        push_back
        void push_back(const value_type& val);

    private:
        pointer begin;
        pointer end;
        pointer capacity;
        allocator_type alloc;

//        vector allocate
        void vallocate(size_type n);

//        construct at end
        void construct_at_end(size_type n, const_reference val);
/***********************************************************************************************************************/
    };

//    Implementation
/***********************************************************************************************************************/
//    Constructors
/***********************************************************************************************************************/
//    vector fill constructor
    template<class T, class Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type &val,
                                    const allocator_type &alloc): begin(0), end(0), capacity(0), alloc(alloc)
    {
        if (n > 0)
        {
            this->vallocate(n);
            this->construct_at_end(n, val);
        }
    }

//    vector range constructor
    template<class T, class Allocator>
    template<class InputIterator, typename enable_if<!is_integral<InputIterator>::value,
            typename iterator_traits<InputIterator>::iterator_category::value>::type >
    vector<T, Allocator>::vector(InputIterator first, InputIterator last,
                                    const allocator_type &alloc): begin(0), end(0), capacity(0), alloc(alloc)
    {
        for (; first != last; ++first)
            push_back(*first);
    }

//    vector copy constructor
    template<class T, class Allocator>
    vector<T, Allocator>::vector(const vector& x): begin(0), end(0), capacity(0), alloc(x.alloc)
    {
        size_type size_x = x.size();
        pointer x_begin = x.begin;

        if (size_x > 0)
        {
            this->vallocate(size_x);
            for (size_type i = 0; i < size_x; ++i, ++this->end, ++x_begin)
                this->alloc.construct(this->end, *x_begin);
        }
    }
/***********************************************************************************************************************/

//    Member functions implementation
/***********************************************************************************************************************/
//    vector max_size
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type
    vector<T, Allocator>::max_size() const
    {
        return std::min<T>(this->alloc.max_size(), std::numeric_limits<difference_type>::max());
    }

//    push_back
    template<class T, class Allocator>
    void vector<T, Allocator>::push_back(const value_type &val)
    {
        if (this->end != this->capacity)
        {
            this->alloc.construct(this->end, val);
            ++this->end;
        }
        else
        {
            size_t cap = this->capacity - this->begin;
            pointer new_begin = this->alloc.allocate(cap * 2);
            for (pointer i = this->begin; i < this->capacity; ++i)
                this->alloc.construct(i, *i);
            this->alloc.construct(new_begin + cap, val);
            for (pointer i = this->begin; i < this->capacity; ++i)
                this->alloc.destroy(i);
            this->alloc.deallocate(this->begin, cap);
            this->begin = new_begin;
            this->end = this->begin + cap;
            this->capacity = this->begin + cap * 2;
        }
    }

//    size
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type
    vector<T, Allocator>::size() const
    {
        return static_cast<size_type>(this->end - this->begin);
    }
/***********************************************************************************************************************/

//    vector allocate
    template<class T, class Allocator>
    void vector<T, Allocator>::vallocate(size_type n)
    {
        if (2 * n > max_size())
            throw std::length_error("vector");
        begin = end = this->alloc.allocate(2 * n);
        capacity = begin + 2 * n;
    }

    //    construct at end
    template<class T, class Allocator>
    inline void vector<T, Allocator>::construct_at_end(size_type n, const_reference val)
    {
        do
        {
            this->alloc.construct(this->end, val);
            --n;
            ++this->end;
        } while(n > 0);
    }
}

#endif
