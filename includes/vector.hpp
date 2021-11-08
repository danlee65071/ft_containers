/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:02:37 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/08 19:29:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

# include <memory>
# include "ft_iterator.hpp"
# include "ft_utility.hpp"
# include <algorithm>
# include <limits>
# include <stdexcept>

#include <vector>

namespace ft
{
	template<class T, class Allocator = std::allocator<T>>
	class vector
	{
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

//      Constructors
		vector(): begin(NULL), end(NULL), end_cap(NULL, NULL) {}
        explicit vector(const Allocator& alloc): begin(NULL), end(NULL), end_cap(NULL, alloc) {}
        explicit vector(size_type count, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type()): vector(alloc)
        {
            if (count > 0)
            {
                vallocate(count);
                construct_at_end(count, x);
            }
        }
        template<class InputIt>
        vector(InputIt first, InputIt last,  const allocator_type& alloc = allocator_type())
        {

        }

//      max_size
        size_type max_size() const
        {
            return std::min<size_type>(allocator_type::max_size(this->alloc()),
                                       std::numeric_limits<difference_type>::max());
        }

//        push_back
        void push_back(const_reference x)
        {
            if (this->end != this->end_cap.first)
            {
                this->alloc()::construct(this->end, x);
                ++this->end;
            }
            else

        }

    private:
        pointer begin;
        pointer end;
        pair<pointer, allocator_type> end_cap;

        //      allocator_type
        allocator_type& alloc()
        {
            return this->end_cap.second;
        }

        const allocator_type& alloc() const
        {
            return this->end_cap.second;
        }

//        vallocate
        void vallocate(size_type n)
        {
            if (n > max_size())
                this->std::length_error("vector");
            this->begin = this->end = allocator_type::allocate(this->alloc(), n);
            this->end_cap = this->begin + n;
        }

//        construct_at_end
        void construct_at_end(size_type n, const_reference x)
        {
            allocator_type& a = this->alloc();
            do
            {
                a::construct(this->end, x);
                --n;
                ++this->end;
            } while(n > 0);
        }
    };
}

#endif
