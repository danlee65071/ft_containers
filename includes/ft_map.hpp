/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:58 by                   #+#    #+#             */
/*   Updated: 2021/12/22 20:41:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_MAP_HPP
#define FT_CONTAINERS_FT_MAP_HPP

# include <functional>
# include <memory>
# include "ft_utility.hpp"
# include "ft_iterator.hpp"
# include "ft_tree.hpp"
# include "ft_type_traits.hpp"
# include "ft_memory.hpp"
# include "ft_nullptr.hpp"
# include <map>

namespace ft
{
	template <class TreeIterator>
	class map_iterator
	{
	private:
		TreeIterator it;
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef typename TreeIterator::value_type value_type;
		typedef value_type& reference;
		typedef typename TreeIterator::node_ptr node_ptr;
		typedef typename TreeIterator::pointer pointer;

		map_iterator() {}

		map_iterator(TreeIterator i): it(i) {}

		reference operator*() const { return it->value; }

		pointer operator->() const { return pointer_traits<pointer>::pointer_to(it->value); }

		map_iterator& operator++()
		{
			++it;
			return *this;
		}

		map_iterator operator++(int)
		{
			map_iterator t(*this);

			++(*this);
			return t;
		}

		map_iterator& operator--()
		{
			--it;
			return *this;
		}

		map_iterator operator--(int)
		{
			map_iterator t(*this);

			--(*this);
			return t;
		}

		friend bool operator==(const map_iterator& x, const map_iterator& y)
		{
			return x.it == y.it;
		}

		friend bool operator!=(const map_iterator& x, const map_iterator& y)
		{
			return x.it != y.it;
		}

		template <class, class, class, class> friend class map;
		template <class> friend class map_const_iterator;
	};

	template <class TreeIterator>
	class map_const_iterator
	{
	private:
		TreeIterator it;
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef typename TreeIterator::value_type value_type;
		typedef value_type& reference;
		typedef typename TreeIterator::node_ptr node_ptr;
		typedef typename TreeIterator::pointer pointer;

		map_const_iterator() {}

		map_const_iterator(TreeIterator i): it(i) {}

		reference operator*() const { return it->value; }

		pointer operator->() const { return pointer_traits<pointer>::pointer_to(it->value); }

		map_const_iterator& operator++()
		{
			++it;
			return *this;
		}

		map_const_iterator operator++(int)
		{
			map_const_iterator t(*this);

			++(*this);
			return t;
		}

		map_const_iterator& operator--()
		{
			--it;
			return *this;
		}

		map_const_iterator operator--(int)
		{
			map_const_iterator t(*this);

			--(*this);
			return t;
		}

		friend bool operator==(const map_const_iterator& x, const map_const_iterator& y)
		{
			return x.it == y.it;
		}

		friend bool operator!=(const map_const_iterator& x, const map_const_iterator& y)
		{
			return x.it != y.it;
		}

		template <class, class, class, class> friend class map;
		template <class, class, class> friend class  tree_const_iterator;
	};
}

#endif
