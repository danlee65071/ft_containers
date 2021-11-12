/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:02:37 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/12 19:42:54 by                  ###   ########.fr       */
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
		typedef typename ft::iterator_traits<pointer>::pointer iterator;
		typedef typename ft::iterator_traits<const_pointer>::pointer const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>
				const_reverse_iterator;

//      constructors
/***********************************************************************************************************************/
//      default constructor
        explicit vector(const allocator_type& alloc = allocator_type()): pbegin(0), pend(0), pcapacity(0), alloc(alloc) {}
//      range constructor
        template<class InputIterator>
        template<class enable_if<!is_integral<InputIterator>::value,
                typename iterator_traits<InputIterator>::iterator_category::value>::type>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
//      fill constructor
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
//      copy constructor
        vector(const vector& x);
/***********************************************************************************************************************/

//      destructor
/***********************************************************************************************************************/
        ~vector();
/***********************************************************************************************************************/

//        operator=
/***********************************************************************************************************************/
        vector& operator= (const vector& x);
/***********************************************************************************************************************/

//        Element access
/***********************************************************************************************************************/
//        operator[]
        reference operator[] (size_type n);
//        const operator[]
        const_reference operator[] (size_type n) const;
//        at
        reference at (size_type n);
//        front
        reference front();
//        const front
        const_reference front() const;
//        back
        reference back();
//        const back
        const_reference back() const;
/***********************************************************************************************************************/

//        Iterators
/***********************************************************************************************************************/
//        begin
        iterator begin();
//        const begin
        const_iterator begin() const;
//        end
        iterator end();
//        const end
        const_iterator end() const;
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
        pointer pbegin;
        pointer pend;
        pointer pcapacity;
        allocator_type alloc;

//        vector allocate
        void vallocate(size_type n);

//        construct at end
        void construct_at_end(size_type n, const_reference val);
//        vector deallocate
        void vdeallocate(size_type n);
/***********************************************************************************************************************/
    };

//    Implementation
/***********************************************************************************************************************/
//    Constructors
/***********************************************************************************************************************/
//    vector fill constructor
    template<class T, class Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type &val,
                                    const allocator_type &alloc): pbegin(0), pend(0), pcapacity(0), alloc(alloc)
    {
        if (n > 0)
        {
            this->vallocate(n);
            this->construct_at_end(n, val);
        }
    }

//    vector range constructor
    template<class T, class Allocator>
    template<class InputIterator>
    template<typename enable_if<!is_integral<InputIterator>::value,
            typename iterator_traits<InputIterator>::iterator_category::value>::type>
    vector<T, Allocator>::vector(InputIterator first, InputIterator last, const allocator_type &alloc)
                                         : pbegin(0), pend(0), pcapacity(0), alloc(alloc)
    {
        for (; first != last; ++first)
            push_back(*first);
    }

//    vector copy constructor
    template<class T, class Allocator>
    vector<T, Allocator>::vector(const vector& x): pbegin(0), pend(0), pcapacity(0), alloc(x.alloc)
    {
        size_type size_x = x.size();
        pointer x_begin = x.pbegin;

        if (size_x > 0)
        {
            this->vallocate(size_x);
            for (size_type i = 0; i < size_x; ++i, ++this->pend, ++x_begin)
                this->alloc.construct(this->pend, *x_begin);
        }
    }
/***********************************************************************************************************************/

//    destructor
/***********************************************************************************************************************/
    template<class T, class Allocator>
    vector<T, Allocator>::~vector()
    {
        this->vdeallocate(this->pcapacity - this->pbegin);
        this->pbegin = this->pend = this->pcapacity = NULL;
    }
/***********************************************************************************************************************/

//    operator=
/***********************************************************************************************************************/
    template<class T, class Allocator>
    vector<T, Allocator>& vector<T, Allocator>::operator=(const vector &x)
    {
        if (this != &x)
        {
            this->alloc = x.alloc;
            this->vdeallocate(this->pcapacity - this->pbegin);
            this->pbegin = this->pend = this->pcapacity = 0;
            for (pointer i = x.pbegin; i < x.pend; ++i)
                this->push_back(*i);
        }
        return *this;
    }
/***********************************************************************************************************************/

//    Element access
/***********************************************************************************************************************/
//    operator[]
    template<class T, class Allocator>
    typename vector<T, Allocator>::reference
    vector<T, Allocator>::operator[](size_type n)
    {
        if (n > static_cast<size_type>(this->pend - this->pbegin))
            throw std::out_of_range("vector[] index out of bounds");
        return *(this->pbegin + n);
    }

//    const operator[]
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference
    vector<T, Allocator>::operator[](size_type n) const
    {
        if (n > this->pend - this->pbegin)
            throw std::out_of_range("vector[] index out of bounds");
        return *(this->pbegin + n);
    }

//    at
    template<class T, class Allocator>
    typename vector<T, Allocator>::reference
    vector<T, Allocator>::at(size_type n)
    {
        if (n >= static_cast<size_type>(this->pend - this->pbegin))
            throw std::out_of_range("vector");
        return this->pbegin[n];
    }

//    front
    template<class T, class Allocator>
    typename vector<T, Allocator>::reference
    vector<T, Allocator>::front()
    {
        return *(this->pbegin);
    }

//    const front
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference
    vector<T, Allocator>::front() const
    {
        return *(this->pbegin);
    }

//    back
    template<class T, class Allocator>
    typename vector<T, Allocator>::reference
    vector<T, Allocator>::back()
    {
        return *(this->pend - 1);
    }

//    const back
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference
    vector<T, Allocator>::back() const
    {
        return *(this->pend - 1);
    }
/***********************************************************************************************************************/

//    Iterators
/***********************************************************************************************************************/
//    begin
    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::begin()
    {
        return (this->pbegin);
    }

//    const begin
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_iterator
    vector<T, Allocator>::begin() const
    {
        return (this->pbegin);
    }

//    end
    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::end()
    {
        return this->pend;
    }

//    const end
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_iterator
    vector<T, Allocator>::end() const
    {
        return this->pend;
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
        size_t cap = this->pcapacity - this->pbegin;

        if (this->pend != this->pcapacity)
        {
            this->alloc.construct(this->pend, val);
            ++this->pend;
        }
        else
        {
            pointer new_begin = this->alloc.allocate((cap > 0 ? cap : 1) * 2);
            for (size_t i = 0; i < cap; ++i)
                this->alloc.construct(new_begin + i, *(this->pbegin + i));
            this->alloc.construct(new_begin + cap, val);
            this->vdeallocate(cap);
            this->pbegin = new_begin;
            this->pend = this->pbegin + cap + 1;
            this->pcapacity = this->pbegin + (cap > 0 ? cap : 1) * 2;
        }
    }

//    size
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type
    vector<T, Allocator>::size() const
    {
        return static_cast<size_type>(this->pend - this->pbegin);
    }
/***********************************************************************************************************************/

//    vector allocate
    template<class T, class Allocator>
    void vector<T, Allocator>::vallocate(size_type n)
    {
        if (2 * n > max_size())
            throw std::length_error("vector");
        pbegin = pend = this->alloc.allocate(2 * n);
        pcapacity = pbegin + 2 * n;
    }

    //    construct at end
    template<class T, class Allocator>
    inline void vector<T, Allocator>::construct_at_end(size_type n, const_reference val)
    {
        do
        {
            this->alloc.construct(this->pend, val);
            --n;
            ++this->pend;
        } while(n > 0);
    }

//    vector deallocate
    template<class T, class Allocator>
    void vector<T, Allocator>::vdeallocate(size_type n)
    {
        for (size_type i = 0; i < n; ++i)
            this->alloc.destroy(this->pbegin + i);
        this->alloc.deallocate(this->pbegin, n);
    }
}

#endif
