/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <hcharlsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:35:26 by                   #+#    #+#             */
/*   Updated: 2022/01/01 22:14:26 by hcharlsi         ###   ########.fr       */
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
	template<class NodePtr>
	inline bool tree_is_left_child(NodePtr x)
	{
		return x == x->parent->left;
	}

	template <class NodePtr>
	inline NodePtr tree_min(NodePtr x)
	{
		while (x->left != NULL)
			x = x->left;
		return x;
	}

	template <class NodePtr>
	inline NodePtr tree_max(NodePtr x)
	{
		while (x->right != NULL)
			x = x->right;
		return x;
	}

	template <class NodePtr>
	inline NodePtr tree_next_iter(NodePtr x)
	{
		if (x->right != NULL)
			return tree_min(x->right);
		while (!tree_is_left_child(x))
			x = x->parent;
		return x->parent;
	}

	template <class NodePtr>
	inline NodePtr tree_prev_iter(NodePtr x)
	{
		if (x->left != NULL)
			return tree_max(x->left);
		while (tree_is_left_child(x))
			x = x->parent;
		return x->parent;
	}

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

		tree_node(node_ptr l, node_ptr r, node_ptr p, value_type val, bool color):
			left(l), right(r), parent(p), value(val), is_black(color)
		{}

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
		tree_iterator(tree_iterator const& p): ptr(p.ptr) {}

		reference operator*() const
		{
			return ptr->value;
		}

		reference operator->() const
		{
			return *this;
		}

        tree_iterator& operator++()
		{
			this->ptr = tree_next_iter<NodePtr>(ptr);
			return *this;
		}

		tree_iterator operator++(int)
		{
			tree_iterator tmp(*this);

			++(*this);
			return tmp;
		}

		tree_iterator& operator--()
		{
			this->ptr = tree_prev_iter<NodePtr>(ptr);
			return *this;
		}

		tree_iterator operator--(int)
		{
			tree_iterator tmp(*this);

			--(*this);
			return tmp;
		}

		friend bool operator==(const tree_iterator& x, const tree_iterator& y)
		{
			return x.ptr == y.ptr;
		}

		friend bool operator!=(const tree_iterator& x, const tree_iterator& y)
		{
			return !(x == y);
		}

	private:
		explicit tree_iterator(node_ptr p): ptr(p) {}
		template <class, class, class> friend class _tree;
		template <class, class> friend class tree_const_iterator;
		template <class> friend class map_iterator;
		template <class, class, class, class> friend class map;
		template <class, class, class> friend class set;
	};

	template <class T, class NodePtr>
	class tree_const_iterator
	{
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef NodePtr node_ptr;
		typedef value_type& reference;

	private:
		typedef tree_iterator<T, NodePtr> non_const_it;
		node_ptr ptr;

	public:
		tree_const_iterator(non_const_it const& p): ptr(p.ptr) {}

		reference operator*() const
		{
			return ptr->value;
		}

		reference operator->() const
		{
			return *this;
		}

		tree_const_iterator& operator++()
		{
			this->ptr = tree_next_iter<NodePtr>(ptr);
			return *this;
		}

		tree_const_iterator operator++(int)
		{
			tree_const_iterator tmp(*this);

			++(*this);
			return tmp;
		}

		tree_const_iterator& operator--()
		{
			this->ptr = tree_prev_iter<NodePtr>(ptr);
			return *this;
		}

		tree_const_iterator operator--(int)
		{
			tree_const_iterator tmp(*this);

			--(*this);
			return tmp;
		}

		friend bool operator==(const tree_const_iterator& x, const tree_const_iterator& y)
		{
			return x.ptr == y.ptr;
		}

		friend bool operator!=(const tree_const_iterator& x, const tree_const_iterator& y)
		{
			return !(x == y);
		}

	private:
		explicit tree_const_iterator(node_ptr p): ptr(p) {}

		template <class, class, class> friend class _tree;
		template <class> friend class map_const_iterator;
		template <class, class, class, class> friend class map;
		template <class, class, class> friend class set;
	};

	template <class T, class Compare, class Allocator>
	class _tree
	{
	public:
		typedef T value_type;
		typedef Compare value_compare;
		typedef Allocator allocator_type;
		typedef tree_node<T> node;
		typedef typename node::node_ptr node_ptr;
		typedef tree_iterator<T, node_ptr> iterator;
		typedef tree_const_iterator<T, node_ptr> const_iterator;
		typedef typename allocator_type::size_type size_type;

	private:
		value_compare cmp;
		allocator_type alloc;
		node_ptr root;
		node_ptr begin_root;
		node_ptr end_root;
		size_type tree_size;

	public:
		explicit _tree(value_compare const& comp,
					   allocator_type const& allocator);

		_tree(_tree const& t): cmp(t.cmp), alloc(t.alloc), root(t.root),
			end_root(t.end_root), tree_size(t.tree_size), begin_root(t.root) {}

//		~_tree();

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		void insert(const value_type& value);

		void remove(const value_type& key);
	private:
		void fix_insert(node_ptr t);
		void fix_remove(node_ptr node, node_ptr parent);
		void tree_left_rotate(node_ptr x);
		void tree_right_rotate(node_ptr x);
	};

	template <class T, class Compare, class Allocator>
	_tree<T, Compare, Allocator>::_tree(const value_compare &comp, const allocator_type &allocator):
			cmp(comp), alloc(allocator), root(NULL),
				begin_root(NULL) ,end_root(NULL), tree_size(0)
	{}

	template <class T, class Compare, class Allocator>
	typename _tree<T, Compare, Allocator>::iterator
	_tree<T, Compare, Allocator>::begin()
	{
		this->begin_root = this->root;
		while (this->begin_root->left != NULL)
			this->begin_root = this->begin_root->left;
		return (iterator)this->begin_root;
	}

	template <class T, class Compare, class Allocator>
	typename _tree<T, Compare, Allocator>::const_iterator
	_tree<T, Compare, Allocator>::begin() const
	{
		this->begin_root = this->root;
		while (this->begin_root->left != NULL)
			this->begin_root = this->begin_root->left;
	}

	template <class T, class Compare, class Allocator>
	typename _tree<T, Compare, Allocator>::iterator
	_tree<T, Compare, Allocator>::end()
	{
		this->end_root = this->root;
		while (this->end_root->right != NULL)
			this->end_root = this->end_root->right;
		node_ptr t = reinterpret_cast<node_ptr>(this->alloc.allocate(sizeof(node)));
		t->parent = this->end_root;
		t->left = NULL;
		t->right = NULL;
		t->value = 0;
		this->end_root->right = t;
		this->end_root = this->end_root->right;
		return (iterator)this->end_root;
	}

	template <class T, class Compare, class Allocator>
	typename _tree<T, Compare, Allocator>::const_iterator
	_tree<T, Compare, Allocator>::end() const
	{
		this->end_root = this->root;
		while (this->end_root->right != NULL)
			this->end_root = this->end_root->right;
		node_ptr t = reinterpret_cast<node_ptr>(this->alloc.allocate(sizeof(node)));
		t->parent = this->end_root;
		t->left = NULL;
		t->right = NULL;
		t->value = 0;
		this->end_root->right = t;
		this->end_root = this->end_root->right;
		return (iterator)this->end_root;
	}

	template <class T, class Compare, class Allocator>
	void _tree<T, Compare, Allocator>::insert(const value_type &value)
	{
		node_ptr t = reinterpret_cast<node_ptr>(this->alloc.allocate(sizeof(node)));

		t->parent = NULL;
		t->left = NULL;
		t->right = NULL;
		this->alloc.construct(&t->value, value);
		t->is_black = false;
		if (this->root == NULL)
		{
			this->root = t;
			t->parent = NULL;
		}
		else
		{
			node_ptr p = this->root;
			node_ptr q = NULL;
			while (p != NULL)
			{
				q = p;
				if (p->value < t->value)
					p = p->right;
				else
					p = p->left;
			}
			t->parent = q;
			if (q->value < t->value)
				q->right = t;
			else
				q->left = t;
		}
		fix_insert(t);
	}

	template <class T, class Compare, class Allocator>
	void _tree<T, Compare, Allocator>::fix_insert(node_ptr t)
	{
		if (t == this->root)
		{
			t->is_black = true;
			return;
		}
		node_ptr parent = t->parent;
		node_ptr grand_parent = parent->parent;
		node_ptr uncle = grand_parent == NULL ? NULL : grand_parent->right;

		while (!parent->is_black)
		{
			if (parent == grand_parent->left)
			{
				if (uncle && uncle->is_black == false)
				{
					parent->is_black = true;
					uncle->is_black = true;
					grand_parent->is_black = false;
					t = grand_parent;
				}
				else
				{
					if (parent && t == parent->right)
					{
						t = parent;
						tree_left_rotate(t);
					}
					parent->is_black = true;
					grand_parent->is_black = true;
					tree_right_rotate(grand_parent);
				}
			}
			else
			{
				if (uncle && uncle->is_black == false)
				{
					parent->is_black = true;
					uncle->is_black = true;
					grand_parent->is_black = false;
					t = grand_parent;
				}
				else
				{
					if (t == parent->left)
					{
						t = t->parent;
						tree_right_rotate(t);
					}
					parent->is_black = true;
					grand_parent->is_black = false;
					tree_left_rotate(grand_parent);
				}
			}
		}
		root->is_black = true;
	}

	template <class T, class Compare, class Allocator>
	void _tree<T, Compare, Allocator>::tree_left_rotate(node_ptr x)
	{
		node_ptr y = x->right;

		x->right = y->left;
		if (y->left != NULL)
			y->left->parent = x;
		if (y != NULL) y->parent = x->parent;
		if (x->parent) {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		else
			this->root = y;
		y->left = x;
		if (x != NULL)
			x->parent = y;
	}

	template <class T, class Compare, class Allocator>
	void _tree<T, Compare, Allocator>::tree_right_rotate(node_ptr x)
	{
		node_ptr y = x->left;

		x->left = y->right;
		if (y->right != NULL)
			y->right->parent = x;
		if (y != NULL)
			y->parent = x->parent;
		if (x->parent)
		{
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		}
		else
			this->root = y;
		y->right = x;
		if (x != NULL)
			x->parent = y;
	}

	template <class T, class Compare, class Allocator>
	void _tree<T, Compare, Allocator>::remove(const value_type &key)
	{
		node_ptr p = this->root;
		node_ptr child, parent;
		bool color;

		while (p->value != key)
		{
			if (p->value < key)
				p = p->right;
			else
				p = p->left;
		}
		if (p->left != NULL && p->right != NULL)
		{
			node_ptr replace = p;
			replace = p->right;
			while (replace->left != NULL)
				replace = replace->left;
			if (p->parent != NULL)
			{
				if (p->parent->left == p)
					p->parent->left = replace;
				else
					p->parent->right = replace;
			} else
				this->root = replace;
			child = replace->right;
			parent = replace->parent;
			color = replace->is_black;
			if (parent == p)
				parent = replace;
			else
			{
				if (child != NULL)
					child->parent = parent;
				parent->left = child;

				replace->right = p->right;
				p->right->parent = replace;
			}
			replace->parent = p->parent;
			replace->is_black = p->is_black;
			replace->left = p->left;
			p->left->parent = replace;
			if (color)
				fix_remove(child, parent);
			this->alloc.destroy(&p->value);
			this->alloc.deallocate(reinterpret_cast<int *>(p), 1);
			return;
		}
		if (p->left != NULL)
			child = p->left;
		else
			child = p->right;
		parent = p->parent;
		color = p->is_black;
		if (child)
			child->parent = parent;
		if (parent)
		{
			if (p == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			this->root = child;

		if (color)
			fix_remove(child, parent);
		this->alloc.destroy(&p->value);
		this->alloc.deallocate(reinterpret_cast<int *>(p), 1);
	}

	template <class T, class Compare, class Allocator>
	void _tree<T, Compare, Allocator>::fix_remove(node_ptr node,
												  node_ptr parent)
	{
		node_ptr othernode;
		while ((!node) || (node->is_black && node != this->root))
		{
			if (parent->left == node)
			{
				othernode = parent->right;
				if (!othernode)
					break ;
				if (!othernode->is_black)
				{
					othernode->is_black = true;
					parent->is_black = false;
					tree_left_rotate(parent);
					othernode = parent->right;
				}
				else
				{
					if (!(othernode->right) || othernode->right->is_black)
					{
						if (othernode->left)
							othernode->left->is_black = true;
						othernode->is_black = false;
						if (othernode->right)
							tree_right_rotate(othernode);
						othernode = parent->right;
					}
					othernode->is_black = parent->is_black;
					parent->is_black = true;
					if (othernode->right)
						othernode->right->is_black = false;
					tree_left_rotate(parent);
					node = this->root;
					break;
				}
			}
			else
			{
				othernode = parent->left;
				if (!othernode->is_black)
				{
					othernode->is_black = true;
					parent->is_black = false;
					tree_right_rotate(parent);
					othernode = parent->left;
				}
				if ((!othernode->left || othernode->left->is_black) && (!othernode->right || othernode->right->is_black))
				{
					othernode->is_black = false;
					node = parent;
					parent = node->parent;
				}
				else
				{
					if (!(othernode->left) || othernode->left->is_black)
					{
						if (othernode->right)
							othernode->right->is_black = true;
						othernode->is_black = false;
						if (othernode->right)
							tree_left_rotate(othernode);
						othernode = parent->left;
					}
					othernode->is_black = parent->is_black;
					parent->is_black = true;
					if (othernode->left)
						othernode->left->is_black = true;
					tree_right_rotate(parent);
					node = this->root;
					break;
				}
			}
		}
		if (node)
			node->is_black = true;
	}
}
#endif
