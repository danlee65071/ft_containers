/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:02:37 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/19 20:09:01 by                  ###   ########.fr       */
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
        vector(InputIterator first,
               typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
                const allocator_type& alloc = allocator_type());
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
//        rbegin
        reverse_iterator rbegin();
//        const rbegin
        const_reverse_iterator rbegin() const;
//        rend
        reverse_iterator rend();
//        const rend
        const_reverse_iterator rend() const;
/***********************************************************************************************************************/

//        Capacity
/***********************************************************************************************************************/
//        size
        size_type size() const;
//        max_size
        size_type max_size() const;
//        resize
        void resize(size_type n, value_type val = value_type());
//        capacity
        size_type capacity() const;
//        empty
        bool empty() const;
//        reserve
        void reserve(size_type n);
/***********************************************************************************************************************/

//        Modifiers
/***********************************************************************************************************************/
//        range assign
        template<class InputIterator>
        typename enable_if<!is_integral<InputIterator>::value, void>::type
        assign(InputIterator first, InputIterator last);
//        fill assign
        void assign(size_type n, const value_type& val);
//        push_back
        void push_back(const value_type& val);
//        pop_back
        void pop_back();
//        single element insert
        iterator insert(iterator position, const value_type& val);
//        fill insert
        void insert(iterator position, size_type n, const value_type& val);
//        range insert
        template<class InputIterator>
        typename enable_if<!is_integral<InputIterator>::value, void>::type
        insert(iterator position, InputIterator first, InputIterator last);
//        erase
        iterator erase(iterator position);
//        range erase
        iterator erase(iterator first, iterator last);
//        swap
        void swap(vector &x);
//        clear
        void clear();
/***********************************************************************************************************************/

//        Allocator
/***********************************************************************************************************************/
//        get_allocator
        allocator_type get_allocator() const;
/***********************************************************************************************************************/

//        Member functions
/***********************************************************************************************************************/

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
    vector<T, Allocator>::vector(InputIterator first,
        typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
            const allocator_type &alloc): pbegin(0), pend(0), pcapacity(0), alloc(alloc)
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
        this->clear();
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

//    rbegin
    template<class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator
    vector<T, Allocator>::rbegin()
    {
        return (reverse_iterator(this->end()));
    }

//    const rbegin
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator
    vector<T, Allocator>::rbegin() const
    {
        return (rbegin(this->end()));
    }

//    rend
    template<class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator
    vector<T, Allocator>::rend()
    {
        return (reverse_iterator(this->begin()));
    }

//    const rend
    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator
    vector<T, Allocator>::rend() const
    {
        return (rend(this->begin()));
    }
/***********************************************************************************************************************/

//        Capacity
/***********************************************************************************************************************/
    //    size
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type
    vector<T, Allocator>::size() const
    {
        return static_cast<size_type>(this->pend - this->pbegin);
    }

    //    max_size
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type
    vector<T, Allocator>::max_size() const
    {
        return std::min<T>(this->alloc.max_size(), std::numeric_limits<difference_type>::max());
    }

//    resize
    template<class T, class Allocator>
    void vector<T, Allocator>::resize(size_type n, value_type val)
    {
        if (n > this->capacity())
            this->reserve(n);
        for (pointer it = this->pend; it < this->pbegin + n; ++it)
            this->alloc.construct(it, val);
        if (n < static_cast<size_type>(this->pend - this->pbegin))
            for (pointer it = this->pbegin + n; it < this->pend; ++it)
                this->alloc.destroy(it);
        this->pend = this->pbegin + n;
    }

//    capacity
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type
    vector<T, Allocator>::capacity() const
    {
        return static_cast<size_type>(this->pcapacity - this->pbegin);
    }

//    empty
    template<class T, class Allocator>
    bool vector<T, Allocator>::empty() const
    {
        return this->pbegin == this->pend;
    }

//    reserve
    template<class T, class Allocator>
    void vector<T, Allocator>::reserve(size_type n)
    {
        if (n > this->capacity())
        {
            size_t size = this->pend - this->pbegin;
            pointer new_begin;
            new_begin = this->alloc.allocate(n);
            for (size_t i = 0; i < size; ++i)
                this->alloc.construct(new_begin + i, *(this->pbegin + i));
            this->vdeallocate(this->pcapacity - this->pbegin);
            this->pbegin = new_begin;
            this->pend = this->pbegin + size;
            this->pcapacity = this->pbegin + n;
        }
    }
/***********************************************************************************************************************/

//        Modifiers
/***********************************************************************************************************************/
//        range assign
    template<class T, class Allocator>
    template<class InputIterator>
    typename enable_if<!is_integral<InputIterator>::value, void>::type
    vector<T, Allocator>::assign(InputIterator first, InputIterator last)
    {
        this->clear();
        for(; first != last; ++first)
            this->push_back(*first);
    }

//    fill assign
    template<class T, class Allocator>
    void vector<T, Allocator>::assign(size_type n, const value_type &val)
    {
        this->clear();
        for(size_type i = 0; i < n; ++i)
            this->push_back(val);
    }

//    push_back
    template<class T, class Allocator>
    void vector<T, Allocator>::push_back(const value_type &val)
    {
        size_type cap = this->pcapacity - this->pbegin;
        if (this->pend == this->pcapacity)
            this->reserve(2 * (cap > 0 ? cap : 1));
        this->alloc.construct(this->pend, val);
        ++this->pend;
    }

//    pop_back
    template<class T, class Allocator>
    void vector<T, Allocator>::pop_back()
    {
        this->alloc.destroy(this->pend - 1);
        --this->pend;
    }

//    single element insert
    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::insert(iterator position, const value_type &val)
    {
        if (position == this->pend - 1)
            this->push_back(val);
        else
        {
        	size_type n_alloc = (this->size() + 1 < this->capacity()) ?
								this->capacity() : this->capacity() * 2;
			pointer new_begin = this->alloc.allocate(n_alloc);
            size_type i = 0;
            for (; i < static_cast<size_type>(position - this->pbegin); ++i)
                this->alloc.construct(new_begin + i, *(this->pbegin + i));
			this->alloc.construct(new_begin + i, val);
            for (; i < this->size(); ++i)
                this->alloc.construct(new_begin + i + 1, *(this->pbegin + i));
            this->clear();
			this->pbegin = new_begin;
			this->pend = new_begin + i + 1;
			this->pcapacity = new_begin + n_alloc;
        }
        return this->pbegin;
    }

//    fill insert
    template<class T, class Allocator>
    void vector<T, Allocator>::insert(iterator position, size_type n, const value_type &val)
    {
        if (position == this->pend - 1)
            for (size_type i = 0; i < n; ++i)
                this->push_back(val);
        else
        {
			size_type n_alloc = (this->size() + 1 < this->capacity()) ?
								this->capacity() : this->capacity() * 2;
			pointer new_begin = this->alloc.allocate(n_alloc);
			size_type i = 0;
			size_type j = 0;
			for (; i < static_cast<size_type>(position - this->pbegin); ++i)
				this->alloc.construct(new_begin + i, *(this->pbegin + i));
            for (pointer it = position; it < position + n; ++it, ++j)
                this->alloc.construct(new_begin + i + j, val);
            for (; i < this->size(); ++i)
                this->alloc.construct(new_begin + i + j, *(this->pbegin + i));
            this->clear();
            this->pbegin = new_begin;
            this->pend = new_begin + i + j;
            this->pcapacity = new_begin + n_alloc;
        }
    }

//    range insert
    template<class T, class Allocator>
    template<class InputIterator>
	typename enable_if<!is_integral<InputIterator>::value, void>::type
    vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
    {
        if (position == this->pend - 1)
            for (InputIterator it = first; it != last; ++it)
                this->push_back(*it);
        else
        {
			size_type n_alloc = (this->size() + 1 < this->capacity()) ?
								this->capacity() : this->capacity() * 2;
			pointer new_begin = this->alloc.allocate(n_alloc);
			size_type i = 0;
            size_type j = 0;
			for (; i < static_cast<size_type>(position - this->pbegin); ++i)
				this->alloc.construct(new_begin + i, *(this->pbegin + i));
            for (InputIterator it = first; it != last; ++it, ++j)
                this->alloc.construct(new_begin + i + j, *it);
            for (; i < this->size(); ++i)
				this->alloc.construct(new_begin + i + j, *(this->pbegin + i));
            this->clear();
			this->pbegin = new_begin;
			this->pend = new_begin + i + j;
			this->pcapacity = new_begin + n_alloc;
        }
    }

//    erase
    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::erase(iterator position)
    {
        size_type next_pos = static_cast<size_type>(position - this->pbegin);
        if (position == this->pend - 1)
            this->pop_back();
        else
        {
            size_type cap = this->capacity();
            pointer new_begin = this->alloc.allocate(cap);
            size_type i = 0;
            for (; i < static_cast<size_type>(position - this->pbegin); ++i)
                this->alloc.construct(new_begin + i, *(this->pbegin + i));
            ++i;
            for (;i < this->size(); ++i)
                this->alloc.construct(new_begin + i - 1, *(this->pbegin + i));
            this->clear();
            this->pbegin = new_begin;
            this->pend = new_begin + i - 1;
            this->pcapacity = new_begin + cap;

        }
        return reinterpret_cast<iterator>(this->pbegin + next_pos);
    }

//    range erase
    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::erase(iterator first, iterator last)
    {
        size_type cap = this->capacity();
        size_type next_pos = last - this->pbegin;
        size_type qnty_erase = static_cast<size_type>(last - first);
        pointer new_begin = this->alloc.allocate(cap);
        size_type i = 0;
        for (; i < static_cast<size_type>(first - this->pbegin); ++i)
            this->alloc.construct(new_begin + i, *(this->pbegin + i));
        i += qnty_erase;
        for (; i < this->size(); ++i)
            this->alloc.construct(new_begin + i - qnty_erase, *(this->pbegin + i));
        this->clear();
        this->pbegin = new_begin;
        this->pend = new_begin + i - qnty_erase;
        this->pcapacity = new_begin + cap;
        return reinterpret_cast<iterator>(this->pbegin + next_pos);
    }

//    swap
    template<class T, class Allocator>
    void vector<T, Allocator>::swap(vector<T, Allocator> &x)
    {
        pointer tmp_begin = x.pbegin;
        pointer tmp_end = x.pend;
        pointer tmp_capacity = x.pcapacity;
        allocator_type tmp_alloc = x.alloc;

        x.pbegin = this->pbegin;
        x.pend = this->pend;
        x.pcapacity = this->pcapacity;
        x.alloc = this->alloc;
        this->pbegin = tmp_begin;
        this->pend = tmp_end;
        this->pcapacity = tmp_capacity;
        this->alloc = tmp_alloc;
    }

//    clear
    template<class T, class Allocator>
    void vector<T, Allocator>::clear()
    {
        this->vdeallocate(this->pcapacity - this->pbegin);
        this->pbegin = this->pend = this->pcapacity = 0;
    }
/***********************************************************************************************************************/

//    Allocator
/***********************************************************************************************************************/
//    get_allocator
    template<class T, class Allocator>
    typename vector<T, Allocator>::allocator_type
    vector<T, Allocator>::get_allocator() const
    {
        return allocator_type(this->alloc);
    }
/***********************************************************************************************************************/

//    Private functions
/***********************************************************************************************************************/
//    vector allocate
    template<class T, class Allocator>
    void vector<T, Allocator>::vallocate(size_type n)
    {
        if (2 * n > max_size())
            throw std::length_error("vector");
        this->pbegin = this->pend = this->alloc.allocate(2 * n);
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
/***********************************************************************************************************************/

//    Non-member functions
/***********************************************************************************************************************/
//    operator==
    template<class T, class Allocator>
    inline bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
    }

//    operator!=
    template<class T, class Allocator>
    inline bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        return !(lhs == rhs);
    }

//    operator<
    template<class T, class Allocator>
    inline bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

//    operator<=
    template<class T, class Allocator>
    inline bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        return !(rhs < lhs);
    }

//    operator>
    template<class T, class Allocator>
    inline bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        return rhs < lhs;
    }

//    operator>=
    template<class T, class Allocator>
    inline bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        return !(lhs < rhs);
    }

//    swap
    template<class T, class Allocator>
    inline void swap(vector<T, Allocator>&lhs, vector<T, Allocator>&rhs)
    {
        lhs.swap(rhs);
    }
/***********************************************************************************************************************/
}

#endif
