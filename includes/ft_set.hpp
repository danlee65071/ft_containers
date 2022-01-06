/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:40:04 by hcharlsi          #+#    #+#             */
/*   Updated: 2022/01/06 12:40:05 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CONTAINERS_FT_SET_HPP
#define FT_CONTAINERS_FT_SET_HPP

# include <functional>
# include <memory>
# include "ft_tree.hpp"
# include "ft_iterator.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	public:
		typedef T key_type;
		typedef key_type value_type;
		typedef Compare key_compare;
		typedef key_compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
	private:
		typedef _tree<value_type, value_compare, allocator_type> base;

		base tree;
	public:
		typedef typename base::iterator iterator;
		typedef typename base::const_iterator const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

		explicit set (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): tree(comp, alloc) {}

		template <class InputIterator>
		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()): tree(comp, alloc)
		{
			insert(first, last);
		}

		set (const set& x): tree(x.tree)
		{
			insert(x.begin(), x.end());
		}

		~set() {}

		set& operator= (const set& x)
		{
			tree = x.tree;
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

		pair<iterator,bool> insert (const value_type& val)
		{
			iterator i = find(val);
			bool is_exist = false;

			if (i == end())
			{
				tree.insert(val);
				is_exist = true;
			}
			return pair<iterator, bool>(find(val), is_exist);
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			tree.insert(val);
			return find(val);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		void erase (iterator position) { tree.remove(position); }

		size_type erase (const value_type& val)
		{
			iterator position = find(val);
			if (position == end())
				return 0;
			tree.remove(position);
			return 1;
		}

		void erase (iterator first, iterator last)
		{
			iterator buf;
			while (first != last)
			{
				buf = first;
				++first;
				tree.remove(buf);
			}
		}

		void swap (set& x) { tree.swap(x.tree); }

		void clear() { tree.clear(tree.get_root()); }

		key_compare key_comp() const { return tree.value_comp(); }
		value_compare value_comp() const { return value_compare(tree.value_comp()); }

		iterator find (const value_type& val) { return tree.template find_in_set(val); }

		size_type count (const value_type& val) const { return tree.count_in_set(val); }

		iterator lower_bound (const value_type& val) { return tree.lower_bound_in_set(val); }

		iterator upper_bound (const value_type& val) { return tree.upper_bound_in_set(val); }

		pair<iterator,iterator> equal_range (const value_type& val) { return tree.equal_range_in_set(val); }

		pair<const_iterator,const_iterator> equal_range (const value_type& val) const { return tree.equal_range_in_set(val); }

		allocator_type get_allocator() const { return tree.get_allocator(); }
	};
}

#endif
