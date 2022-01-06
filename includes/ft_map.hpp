/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:58 by                   #+#    #+#             */
/*   Updated: 2022/01/06 02:37:50 by hcharlsi         ###   ########.fr       */
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
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef typename TreeIterator::value_type value_type;
		typedef value_type& reference;
		typedef typename TreeIterator::pointer pointer;
	private:
		TreeIterator it;
	public:
		map_iterator(): it() {}

		map_iterator(TreeIterator i): it(i) {}

		reference operator*() const { return *it; }

		pointer operator->() const { return it.operator->(); }

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
		typedef typename TreeIterator::pointer pointer;

		map_const_iterator() {}

		map_const_iterator(TreeIterator i): it(i) {}

		reference operator*() const { return *it; }

		pointer operator->() const { return it.operator->(); }

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
		template <class, class> friend class  tree_const_iterator;
	};

	template <class Key, class T, class Compare = std::less<Key>,
	        class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
	private:
		typedef _tree<value_type, key_compare, allocator_type> base;
		typedef typename base::iterator tree_iterator;
		typedef typename base::const_iterator const_tree_iterator;
		base tree;
	public:
		typedef map_iterator<tree_iterator> iterator;
		typedef map_const_iterator<const_tree_iterator> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare
		{
			friend class map;
		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): tree(comp, alloc) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()): tree(comp, alloc)
		{
			insert(first, last);
		}

		map (const map& x): tree(x.tree)
		{
			insert(x.begin(), x.end());
		}

		~map() { }

		map& operator= (const map& x)
		{
			if (this != &x)
			{
				tree.clear(tree.get_root());
				tree.cmp = x.tree.cmp;
				tree.alloc = x.tree.alloc;
				insert(x.begin(), x.end());
			}
			return *this;
		}

		iterator begin() { return tree.begin(); }
		const_iterator begin() const { return tree.begin(); }
		iterator end() { return tree.end(); }
		const_iterator end() const { return tree.end(); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		bool empty() const { return tree.size() == 0; }

		size_type size() const { return tree.size(); }

		size_type max_size() const { return tree.max_size(); }

		mapped_type& operator[] (const key_type& k);

		pair<iterator,bool> insert (const value_type& val)
		{
			iterator i = find(val.first);
			bool is_exist = false;

			if (i == end())
			{
				tree.insert(val);
				is_exist = true;
			}
			return pair<iterator, bool>(find(val.first), is_exist);
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			tree.insert(val);
			return find(val.first);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		void erase (iterator position) { tree.remove(position.it); }

		size_type erase (const key_type& k)
		{
			iterator position = find(k);
			if (position == end())
				return 0;
			tree.remove(position.it);
			return 1;
		}

		void erase (iterator first, iterator last)
		{
			for (; first != last; ++first)
				tree.remove(first.it);
		}

		void swap (map& x) { tree.swap(x.tree); }

		void clear() { tree.clear(tree.get_root()); }

		key_compare key_comp() const { return tree.value_comp(); }

		value_compare value_comp() const { return value_compare(tree.value_comp()); }

		iterator find (const key_type& k) { return tree.find(k); }
		const_iterator find (const key_type& k) const { return tree.find(k); }

		size_type count (const key_type& k) const { return tree.count(k); }

		iterator lower_bound (const key_type& k) { return tree.lower_bound(k); }

		const_iterator lower_bound (const key_type& k) const { tree.lower_bound(k); }

		iterator upper_bound (const key_type& k) { return tree.upper_bound(k); }

		const_iterator upper_bound (const key_type& k) const { return tree.upper_bound(k); }

		pair<iterator,iterator> equal_range (const key_type& k)
		{ return tree.template equal_range(k); }

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{ return tree.template equal_range(k); }

		allocator_type get_allocator() const { return tree.get_allocator(); }
	};

	template <class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::mapped_type&
	map<Key, T, Compare, Allocator>::operator[](const key_type &k)
	{
		iterator p = find(k);
		if (p == end())
		{
			insert(value_type(k, mapped_type()));
			p = find(k);
		}
		return p.it->second;
	}

}

#endif
