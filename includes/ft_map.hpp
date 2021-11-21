/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:58 by                   #+#    #+#             */
/*   Updated: 2021/11/21 16:24:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_MAP_HPP
#define FT_CONTAINERS_FT_MAP_HPP

# include <map>
# include <functional>
# include <memory>
# include "ft_utility.hpp"
# include "ft_iterator.hpp"

namespace ft
{
    template<class TreeIterator>
    class _map_iterator
    {
    private:
        typedef typename TreeIterator::_NodeTypes _NodeTypes;
        typedef typename TreeIterator::_pointer_traits _pointer_traits;

        TreeIterator it;
    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef typename _NodeTypes::__map_value_type value_type;
        typedef typename TreeIterator::difference_type difference_type;
        typedef const value_type& reference;
        typedef typename _NodeTypes::__const_map_value_type_pointer pointer;

        _map_iterator(){}
        _map_iterator(TreeIterator other): it(other) {}

        reference operator*() const { return it->__get_value(); }
        pointer operator->() const { return it; }

        _map_iterator& operator++() { ++it; return *this; }
        _map_iterator operator++(int)
        {
            _map_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        _map_iterator& operator--() {--it; return *this;}
        _map_iterator operator--(int)
        {
            _map_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        friend bool operator==(const _map_iterator& x, const _map_iterator& y)
        {return x.it == y.it;}

        friend bool operator!=(const _map_iterator& x, const _map_iterator& y)
        {return x.it != y.it;}

        template <class, class, class, class> friend class map;
    };

    template < class Key, class T, class Compare = std::less<Key>,
            class Alloc = std::allocator<pair<const Key,T> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef value_type& reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef const value_type& const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef
    };
}

#endif
