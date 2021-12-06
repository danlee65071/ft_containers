/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:35:26 by                   #+#    #+#             */
/*   Updated: 2021/12/03 23:24:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_TREE_H
#define FT_CONTAINERS_FT_TREE_H

# include <memory>
# include <__tree>
# include "ft_memory.hpp"
# include "ft_utility.hpp"
# include "ft_iterator.hpp"

namespace ft
{
//    prototypes
    template<class VoidPtr> class _tree_node_base;
    template<class Pointer> class _tree_end_node;

//    _tree_is_left_child
    template<class NodePtr>
    inline bool _tree_is_left_child(NodePtr x)
    {
        return x == x->_parent->_left;
    }

//    _tree_min
    template<class NodePtr>
    inline NodePtr _tree_min(NodePtr x)
    {
        while (x->_left != 0)
            x = x->_left;
        return x;
    }

//    _tree_max
    template<class NodePtr>
    inline NodePtr _tree_max(NodePtr x)
    {
        while (x->_right != 0)
            x = x->_right;
        return x;
    }

//    _tree_next_iter
    template<class EndNodePtr, class NodePtr>
    inline EndNodePtr _tree_next_iter(NodePtr x)
    {
        if (x->_right != 0)
            return static_cast<EndNodePtr>(_tree_min(x->_right));
        while (!_tree_is_left_child(x))
            x = x->_parent_unsafe();
        return static_cast<EndNodePtr>(x->_parent);
    }

//    _tree_prev_iter
    template<class NodePtr, class EndNodePtr>
    inline NodePtr _tree_prev_iter(EndNodePtr x)
    {
        if (x->_left != 0)
            return _tree_max(x->_left);
        NodePtr xx = static_cast<NodePtr>(x);
        while (_tree_is_left_child(xx))
            xx = xx->_parent_unsafe();
    }

//	_tree_leaf
	template<class NodePtr>
	NodePtr _tree_leaf(NodePtr x)
	{
		while (true)
		{
			if (x->_left != 0)
			{
				x = x->_left;
				continue;
			}
			if (x->_right != 0)
			{
				x = x->_right;
				continue;
			}
			break;
		}
		return x;
	}

//    _tree_node_base_types
    template<class VoidPtr>
    struct _tree_node_base_types
    {
        typedef VoidPtr _void_pointer;
        typedef _tree_node_base<_void_pointer> _node_base_type;
        typedef typename _rebind_pointer<VoidPtr, _node_base_type>::type _node_base_pointer;
        typedef _tree_end_node<_node_base_pointer>  _end_node_type;
        typedef typename _rebind_pointer<VoidPtr, _end_node_type>::type _end_node_pointer;
        typedef typename conditioinal<is_pointer<_end_node_pointer>::value,
                _end_node_pointer, _node_base_pointer>::type _parent_pointer;
    };

//    _tree_end_node
    template<class Pointer>
    class _tree_end_node
    {
    public:
        typedef Pointer pointer;
        pointer _left;

        _tree_end_node(): _left() {}
    };

//    _tree_node_base
    template<class VoidPtr>
    class _tree_node_base: _tree_node_base_types<VoidPtr>::_end_node_type
    {
        typedef _tree_node_base_types<VoidPtr> _NodeBaseTypes;
    public:
        typedef typename _NodeBaseTypes::_node_base_pointer pointer;
        typedef typename _NodeBaseTypes ::_parent_pointer _parent_pointer;

        pointer _right;
        _parent_pointer _parent;
        bool is_black;

        pointer _parent_unsafe() const
        {
            return static_cast<pointer>(_parent);
        }

        void _set_parent(pointer p)
        {
            _parent = static_cast<_parent_pointer>(p);
        }

    private:
        ~_tree_node_base();
        _tree_node_base(_tree_node_base const&);
        _tree_node_base& operator=(_tree_node_base const&);
    };

//    _tree_node
    template<class T, class VoidPtr>
    class _tree_node: public _tree_node_base<VoidPtr>
    {
    public:
        typedef T _node_value_type;

        _node_value_type  _value;
    private:
        ~_tree_node();
        _tree_node(_tree_node const&);
        _tree_node& operator=(_tree_node const&);
    };

//    _tree_key_value_types
    template<class T>
    struct _tree_key_value_types
    {
        typedef T key_type;
        typedef T _node_value_type;
        typedef T _container_value_type;
        static const bool _is_map = false;

        static key_type const& _get_key(T const& _v)
        {
            return _v;
        }

        static _container_value_type const& _get_value(_node_value_type const& _v)
        {
            return _v;
        }

        static _container_value_type* _get_ptr(_node_value_type& _n)
        {
            return addressof(_n);
        }
    };

//    _tree_map_pointer_types
    template<class T, class AllocPtr, class KVTypes = _tree_key_value_types<T>, bool = KVTypes::_is_map>
    struct _tree_map_pointer_types {};

    template<class T, class AllocPtr, class KVTypes>
    struct _tree_map_pointer_types<T, AllocPtr, KVTypes, true>
    {
        typedef typename KVTypes::_map_value_type Mv;
        typedef typename _rebind_pointer<AllocPtr, Mv>::type _map_value_type_pointer;
        typedef typename _rebind_pointer<AllocPtr, const Mv>::type _const_map_value_type_pointer;
    };

//    _tree_node_types
    template<class NodePtr, class NodeT = typename pointer_traits<NodePtr>::element_type>
    struct _tree_node_types;

    template<class NodePtr, class T, class VoidPtr>
    struct _tree_node_types<NodePtr, _tree_node<T, VoidPtr> >:
            public _tree_node_base_types<VoidPtr>,
                   _tree_key_value_types<T>,
                   _tree_map_pointer_types<T, VoidPtr>
    {
        typedef _tree_node_base_types<VoidPtr> _base;
        typedef _tree_key_value_types<T> _key_base;
        typedef _tree_map_pointer_types<T, VoidPtr> _map_pointer_base;
    public:
        typedef typename pointer_traits<NodePtr>::element_type _node_type;
        typedef NodePtr _node_pointer;
        typedef T _node_value_type;
        typedef typename _rebind_pointer<VoidPtr, _node_value_type>::type _node_value_type_pointer;
        typedef typename _rebind_pointer<VoidPtr, const _node_value_type>::type _const_node_value_type_pointer;
        typedef typename conditioinal<is_pointer<_node_pointer>::value,
            typename _base::_end_node_pointer, _node_pointer>::type _iter_pointer;
    };

//    make_tree_node_types
    template<class ValueT, class VoidPtr>
    struct _make_tree_node_types
    {
        typedef typename _rebind_pointer<VoidPtr, _tree_node<ValueT, VoidPtr> >::type _NodePtr;
        typedef _tree_node_types<_NodePtr> type;
    };

//    _tree_iterator
    template<class T, class NodePtr, class DiffType>
    class _tree_iterator
    {
        typedef _tree_node_types<NodePtr> _NodeTypes;
        typedef NodePtr _node_pointer;
        typedef typename _NodeTypes::_node_base_pointer _node_base_pointer;
        typedef typename _NodeTypes::_end_node_pointer _end_node_pointer;
        typedef typename _NodeTypes::_iter_pointer _iter_pointer;
        typedef pointer_traits<_node_pointer> _pointer_traits;

        _iter_pointer _ptr;
    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef DiffType difference_type;
        typedef value_type& reference;
        typedef typename _NodeTypes::_node_value_type_pointer pointer;

        _tree_iterator(): _ptr(0) {}

        reference operator*() const {return _get_np()->_value;}

        pointer operator->() const {return pointer_traits<pointer>::pointer_to(_get_np()->_value);}

        _tree_iterator& operator++()
        {
            _ptr = static_cast<_iter_pointer>(_tree_next_iter<_end_node_pointer>
                    (static_cast<_node_base_pointer>(_ptr)));
            return (*this);
        }

        _tree_iterator operator++(int)
        {
            _tree_iterator t(*this);

            ++(*this);
            return t;
        }

        _tree_iterator& operator--()
        {
            _ptr = static_cast<_iter_pointer>(_tree_prev_iter<_node_base_pointer>
                    (static_cast<_end_node_pointer>(_ptr)));
            return (*this);
        }

        _tree_iterator operator--(int)
        {
            _tree_iterator t(*this);

            --(*this);
            return t;
        }

        friend bool operator==(const _tree_iterator& x, const _tree_iterator& y)
        {
            return x._ptr == y._ptr;
        }

        friend bool operator!=(const _tree_iterator& x, const _tree_iterator& y)
        {
            return !(x == y);
        }
    private:
        explicit _tree_iterator(_node_pointer p): _ptr(p) {}
        explicit _tree_iterator(_end_node_pointer): _ptr(p) {}
        _node_pointer _get_np() const {return static_cast<_node_pointer>(_ptr);}
        template <class, class, class> friend class _tree;
        template <class, class, class> friend class _tree_const_iterator;
        template <class, class, class, class> friend class map;
    };

//    _tree_const_iterator
    template<class T, class NodePtr, class DiffType>
    class _tree_const_iterator
    {
        typedef _tree_node_types<NodePtr> _NodeTypes;
        typedef typename _NodeTypes::_node_pointer _node_pointer;
        typedef typename _NodeTypes::_node_base_pointer _node_base_pointer;
        typedef typename _NodeTypes::_end_node_pointer _end_node_pointer;
        typedef typename _NodeTypes::_iter_pointer _iter_pointer;
        typedef pointer_traits<_node_pointer> _pointer_traits;

        _iter_pointer _ptr;
    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef DiffType difference_type;
        typedef const value_type& reference;
        typedef typename _NodeTypes::_const_node_value_type_pointer pointer;

        _tree_const_iterator(): _ptr(0) {}
    private:
        typedef _tree_iterator<value_type, _node_pointer, difference_type> _non_const_iterator;

    public:
        _tree_const_iterator(_non_const_iterator p): _ptr(p._ptr) {}

        reference operator*() const {return _get_np()->_value;}

        pointer operator->() const {return pointer_traits<pointer>::pointer_to(_get_np()->_value);}

        _tree_const_iterator& operator++()
        {
            _ptr = static_cast<_iter_pointer>(_tree_next_iter<_end_node_pointer>
                    (static_cast<_node_base_pointer>(_ptr)));
            return *this;
        }

        _tree_const_iterator operator++(int)
        {
            _tree_const_iterator t(*this);

            ++(*this);
            return t;
        }

        _tree_const_iterator& operator--()
        {
            _ptr = static_cast<_iter_pointer>(_tree_next_iter<_node_base_pointer>
                    (static_cast<_end_node_pointer>(_ptr)));
            return *this;
        }

        _tree_const_iterator operator--(int)
        {
            _tree_const_iterator t(*this);

            --(*this);
            return t;
        }

        friend bool operator==(const _tree_const_iterator& x, const _tree_const_iterator& y)
        {return x._ptr == y._ptr;}

        friend bool operator!=(const _tree_const_iterator& x, const _tree_const_iterator& y)
        {return !(x == y);}
    private:
        explicit _tree_const_iterator(_node_pointer p): _ptr(p) {}
        explicit _tree_const_iterator(_end_node_pointer p): _ptr(p) {}
        _node_pointer _get_np() const { return static_cast<_node_pointer>(_ptr); }
        template <class, class, class> friend class _tree;
        template <class, class, class, class> friend class map;
        template <class> friend class  _map_const_iterator;
    };

//    tree
    template<class T, class Compare, class Allocator>
    class _tree
    {
    public:
        typedef T value_type;
        typedef Compare value_compare;
        typedef Allocator allocator_type;
    private:
        typedef typename _make_tree_node_types<value_type, typename allocator_type::pointer>::type _NodeTypes;
        typedef typename _NodeTypes::key_type key_type;
    public:
        typedef typename _NodeTypes::_node_value_type _node_value_type;
        typedef typename _NodeTypes::_container_value_type _container_value_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::size_type size_type;
        typedef typename Allocator::difference_type difference_type;
        typedef typename _NodeTypes::_void_pointer _void_pointer;
        typedef typename _NodeTypes::_node_type _node;
        typedef typename _NodeTypes::_node_pointer _node_pointer;
        typedef typename _NodeTypes::_node_base_type _node_base;
        typedef typename _NodeTypes::_node_base_pointer _node_base_pointer;
        typedef typename _NodeTypes::_end_node_type _end_node_t;
        typedef typename _NodeTypes::_end_node_pointer _end_node_ptr;
        typedef typename _NodeTypes::_parent_pointer _parent_pointer;
        typedef typename _NodeTypes::_iter_pointer _iter_pointer;
        typedef typename allocator_type::template rebind<_node>::other _node_allocator;
        typedef _tree_iterator<value_type, _node_pointer, difference_type> iterator;
        typedef _tree_const_iterator<value_type, _node_pointer, difference_type> const_iterator;
    private:
        _iter_pointer _begin_node_;
        pair<_end_node_t, _node_allocator> _pair1_;
        pair<size_type, value_compare> _pair3_;
    public:
        _iter_pointer _end_node()
        {
            return static_cast<_iter_pointer>(pointer_traits<_end_node_ptr>::pointer_to(_pair1_.first()));
        }

        _iter_pointer _end_node() const
        {
            return static_cast<_iter_pointer>(
                    pointer_traits<_end_node_ptr>::pointer_to(
                            const_cast<_end_node_t&>(_pair1_.first())
                            )
                    );
        }

        _node_allocator& _node_alloc() {return _pair1_.second();}
    private:
        const _node_allocator& _node_alloc() const {return _pair1_.second();}

        _iter_pointer& _begin_node() {return _begin_node_;}

        const _iter_pointer& _begin_node() const {return _begin_node_;}
    public:
        allocator_type _alloc() const {return allocator_type(_node_alloc());}
    private:
        size_type& size() {return _pair3_.first();}
    public:
        const size_type& size() const {return _pair3_.first();}

        value_compare& value_comp() {return _pair3_.second();}

        const value_compare& value_comp() const {return _pair3_.second();}

        _node_pointer __root() const
        {
            return static_cast<_node_pointer>(_end_node()->_left);
        }

        _node_base_pointer* _root_ptr() const
        {
            return addressof(_end_node()->_left);
        }

		explicit _tree(const value_comp& comp):
				_begin_node_(_iter_pointer()),
				_pair1_(_default_init_tag(), _node_allocator(a)),
				_pair3_(0, _default_init_tag())
		{
			_begin_node() = _end_node();
		}

		explicit _tree(const allocator_type& a):
			_begin_node_(_iter_pointer()),
			_pair1_(_default_init_tag(), _node_allocator(a)),
			_pair3_(0, _default_init_tag())
		{
			_begin_node() = _end_node();
		}

		_tree(const value_compare& comp, const allocator_type& a):
			_begin_node_(_iter_pointer()),
			_pair1_(_default_init_tag(),_node_allocator(a)),
			_pair3_(0, comp)
		{
			_begin_node() = _end_node();
		}

		_tree(const _tree& t):
			_begin_node_(_iter_pointer()),
			_pair1_(_default_init_tag(), t._node_alloc()),
			_pair3_(0, t.value_comp())
		{
			_begin_node() = _end_node();
		}

		_tree& operator=(const _tree& t)
		{
			if (this != &t)
			{
				value_comp() = t.value_comp();
				_copy_assign_alloc(t);
				_assign_multi(t.begin(), t.end());
			}
			return *this;
		}

		template<class ForwardIterator>
		void _assign_unique(ForwardIterator first, ForwardIterator last)
		{
			typedef iterator_traits<ForwardIterator> Itraits;
			typedef typename Itraits::value_type  ItValueType;

			if (size() != 0)
			{
				_DetachedTreeCache cache(this);

				for (; cache._get() != 0 && first != last; ++first)
				{
					if (_node_assign_unique(*first, cache._get()).second)
						cache._advance();
				}
			}
			for (; first != last; ++first)
				_insert_unique(*first);
		}

		template<class InputIterator>
		void _assign_multi(InputIterator first, InputIterator last)
		{
			typedef iterator_traits<InputIterator> Itraits;
			typedef typename Itraits::value_type ItValueType;

			if (size() != 0)
			{
				_DetachedTreeCache cache(this);
				for (; cache._get() && first != last; ++first)
				{
					cache._get()->_value = *first;
					_node_insert_multi(cache._get());
                    cache._advance();
				}
			}
			for (; first != last; ++first)
				_insert_multi(_NodeTypes::_get_value(*first));
		}

		iterator _node_insert_multi(_node_pointer n)
		{
			_parent_pointer  _parent;
			_node_base_pointer& _child = _find_leaf_high(_parent, _NodesTypes::_get_key(n->_value));
			_insert_node_at(_parent, _child, static_cast<_node_base_pointer>(n));
			return iterator(n);
		}

		iterator _node_insert_multi(const_iterator p, _node_pointer n)
		{
			_parent_pointer _parent;
			_node_base_pointer& _child = _find_leaf(p, _parent, _NodeTypes::_get_key(n->_value));
			_insert_node_at(_parent, _child, static_cast<_node_base_pointer>(n));
			return iterator(n);
		}

	private:
		_node_base_pointer& _find_leaf_low(_parent_pointer& _parent, const key_type& v)
		{
			_node_pointer n = __root();
			if (n != nullptr)
			{
				while (true)
				{
					if (value_comp()(n->_value, v))
					{
						if (n->_right != 0)
							n = static_cast<__node_pointer>(n->_right);
						else
						{
							_parent = static_cast<_parent_pointer>(n);
							return n->_right;
						}
					}
					else
					{
						if (n->_left != 0)
							n = static_cast<__node_pointer>(n->_left);
						else
						{
							_parent = static_cast<_parent_pointer>(n);
							return _parent->_left;
						}
					}
				}
			}
			_parent = static_cast<_parent_pointer>(_end_node());
			return _parent->_left;
		}

		_node_base_pointer& _find_leaf_high(_parent_pointer& _parent, const key_type& v)
		{
			_node_pointer n = __root();
			if (n != 0)
			{
				while (true)
				{
					if (value_comp()(v, n->_value))
					{
						if (n->_left != 0)
							n = static_cast<_node_pointer>(n->_left);
						else
						{
							_parent = static_cast<_parent_pointer>(n);
							return _parent->_left;
						}
					}
					else
					{
						if (n->_right != 0)
							n = static_cast<_parent_pointer>(n->_right);
						else
						{
							_parent = static_cast<_parent_pointer>(n);
							return n->_right;
						}
					}
				}
			}
			_parent = static_cast<_parent_pointer>(_end_node());
			return _parent->_left;
		}

		_node_base_pointer& _find_leaf(const_iterator hint, _parent_pointer& _parent,
									   const key_type& v)
		{
			if (hint == end() || !value_comp()(*hint, v))
			{
				const_iterator prior = hint;
				if (prior == begin() || !value_comp()(v, *--prior))
				{
					if (hint._ptr->_left == 0)
					{
						_parent = static_cast<_parent_pointer>(hint._ptr;
						return _parent->_left;
					}
					else
					{
						_parent = static_cast<_parent_pointer>(prior._ptr);
						return static_cast<__node_base_pointer>(prior._ptr)->_right;
					}
				}
				return _find_leaf_high(_parent, v);
			}
			return _find_leaf_low(_parent, v);
		}

		struct _DetachedTreeCache
		{
		private:
			_tree *_t;
			_node_pointer _cache_root;
			_node_pointer _cache_elem;

			static _node_pointer _detach_from_tree(_tree *t)
			{
				_node_pointer _cache = static_cast<_node_pointer>(t->_begin_node());
				t->_begin_node() = t->_end_node();
				t->_end_node()->_left->_parent = 0;
				t->_end_node()->_left = 0;
				t->size() = 0;
				if (_cache->_right != 0)
					_cache = static_cast<_node_pointer>(_cache->_right);
				return _cache;
			}

			static _node_pointer _detach_next(_node_pointer)
			{
				if (_cache->_parent == 0)
					return 0;
				if (_tree_is_left_child(static_cast<_node_base_pointer>(_cache)))
				{
					_cache->_parent->_left = 0;
					_cache = static_cast<_node_pointer>(_cache->_parent);
					if (_cache->_right == 0)
						return _cache;
					return static_cast<_node_pointer>(_tree_leaf(_cache->_right));
				}
				_cache->_parent_unsafe()->_right = 0;
				_cache = static_cast<_node_pointer>(_cache->_parent);
				if (_cache->_left == 0)
					return _cache;
				return static_cast<_node_pointer>(_tree_leaf(_cache->_left));
			}

		public:
			explicit _DetachedTreeCache(_tree *t): _t(t),
				_cache_root(_detach_from_tree(t))
			{
				_advance();
			}

			_node_pointer _get() const
			{
				return _cache_elem;
			}

			void _advance()
			{
				_cache_elem = _cache_root;
				if (_cache_root)
					_cache_root = _detach_next(_cache_root);
			}

			~_DetachedTreeCache()
			{
				_t->destroy(_cache_elem);
				if (_cache_root)
				{
					while (_cache_root->_parent != 0)
						_cache_root = static_cast<_node_pointer>(_cache_root->_parent);
					_t->destroy(_cache_root);
				}
			}

		};
    };
}
#endif
