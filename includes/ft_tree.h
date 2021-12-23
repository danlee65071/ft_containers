/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:35:26 by                   #+#    #+#             */
/*   Updated: 2021/12/22 22:45:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_TREE_H
#define FT_CONTAINERS_FT_TREE_H

# include <memory>
# include <__tree>
# include "ft_memory.hpp"
# include "ft_utility.hpp"
# include "ft_iterator.hpp"
# include "ft_nullptr.hpp"
# include "ft_type_traits.hpp"
# include "ft_algorithm.hpp"

namespace ft
{
	template <class T>
	class tree_node
	{
	public:
		typedef tree_node<T>* node_ptr;
		typedef T value_type;

		node_ptr left;
		node_ptr right;
		node_ptr parent;
		value_type value;
		bool is_black;
	private:
		tree_node() {}
		tree_node(tree_node const&) {}
		~tree_node() {}
		tree_node& operator=(tree_node const&) {}
	};

	template <class T, class NodePtr>
	class tree_iterator
	{
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef NodePtr node_ptr;
		typedef value_type& reference;

	private:
		node_ptr ptr;

	public:
		tree_iterator() {}
		tree_iterator(tree_iterator const& p): ptr(p) {}
		~tree_iterator() {}

		reference operator*() const
		{
			return ptr->value;
		}

		value_type operator->() const
		{
			return *this;
		}
	};

	template <class T, class Compare, class Allocator>
	class _tree
	{
	public:
		typedef T value_type;
		typedef Compare value_compare;
		typedef Allocator allocator_type;
		typedef typename tree_node<T>::node_ptr node_ptr;

	private:
		value_compare cmp;
		allocator_type alloc;
		node_ptr root;

	public:
		_tree() {}

		explicit _tree(value_compare const& comp,
					   allocator_type const& allocator): cmp(comp), alloc(allocator)
		{
			this->root->parent, this->root = NULL;
		}

		_tree(_tree const& t): cmp(t.cmp), alloc(t.alloc), root(t.root) {}
	};
}
#endif
