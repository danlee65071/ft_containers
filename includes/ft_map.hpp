/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:58 by                   #+#    #+#             */
/*   Updated: 2021/11/20 03:09:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_MAP_HPP
#define FT_CONTAINERS_FT_MAP_HPP

# include <map>
# include <functional>
# include "ft_utility.hpp"

namespace ft
{
    template<class TreeIterator>
    class _map_iterator
    {

    };

    template < class Key, class T, class Compare = std::less<Key>,
            class Alloc = allocator<pair<const Key,T> > >
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
        typedef allocator_type::pointer pointer;
        typedef allocator_type::const_pointer const_pointer;
        typedef
    };
}

#endif
