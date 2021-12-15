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
# include <algorithm>
# include <__config>

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

//    _tree_next
    template <class NodePtr>
    NodePtr _tree_next(NodePtr x)
    {
        if (x->_right != nullptr)
            return _tree_min(x->_right);
        while (!_tree_is_left_child(x))
            x = x->_parent_unsafe();
        return x->_parent_unsafe();
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

//    _tree_left_rotate
    template <class NodePtr>
    void _tree_left_rotate(NodePtr x)
    {
        NodePtr y = x->_right;
        x->_right = y->_left;
        if (x->_right != nullptr)
            x->_right->_set_parent(x);
        y->_parent_ = x->_parent;
        if (_tree_is_left_child(x))
            x->_parent->_left = y;
        else
            x->_parent_unsafe()->_right = y;
        y->_left_ = x;
        x->_set_parent(y);
    }

//    _tree_right_rotate
    template <class NodePtr>
    void _tree_right_rotate(NodePtr x)
    {
        NodePtr y = x->_left;
        x->_left = y->_right;
        if (x->_left != nullptr)
            x->_left->_set_parent(x);
        y->_parent = x->_parent;
        if (_tree_is_left_child(x))
            x->_parent->_left = y;
        else
            x->_parent_unsafe()->_right_ = y;
        y->_right = x;
        x->_set_parent(y);
    }

//    _tree_balance_after_insert
    template <class NodePtr>
    void _tree_balance_after_insert(NodePtr root, NodePtr x)
    {
        x->_is_black = x == root;
        while (x != root && !x->_parent_unsafe()->_is_black)
        {
            if (_tree_is_left_child(x->_parent_unsafe()))
            {
                NodePtr y = x->_parent_unsafe()->_parent_unsafe()->_right;
                if (y != nullptr && !y->_is_black)
                {
                    x = x->_parent_unsafe();
                    x->_is_black = true;
                    x = x->_parent_unsafe();
                    x->_is_black_ = x == root;
                    y->_is_black = true;
                }
                else
                {
                    if (!_tree_is_left_child(x))
                    {
                        x = x->_parent_unsafe();
                        _tree_left_rotate(x);
                    }
                    x = x->_parent_unsafe();
                    x->_is_black = true;
                    x = x->_parent_unsafe();
                    x->_is_black = false;
                    _tree_right_rotate(x);
                    break;
                }
            }
            else
            {
                NodePtr y = x->_parent_unsafe()->_parent->_left;
                if (y != nullptr && !y->_is_black)
                {
                    x = x->_parent_unsafe();
                    x->_is_black = true;
                    x = x->_parent_unsafe();
                    x->_is_black = x == root;
                    y->_is_black = true;
                }
                else
                {
                    if (_tree_is_left_child(x))
                    {
                        x = x->_parent_unsafe();
                        _tree_right_rotate(x);
                    }
                    x = x->_parent_unsafe();
                    x->_is_black = true;
                    x = x->_parent_unsafe();
                    x->_is_black = false;
                    _tree_left_rotate(x);
                    break;
                }
            }
        }
    }

//    _tree_remove
template <class NodePtr>
void _tree_remove(NodePtr root, NodePtr z)
{
    NodePtr y = (z->_left == nullptr || z->_right == nullptr) ? z : _tree_next(z);
    NodePtr x = y->_left != nullptr ? y->_left : y->_right;
    NodePtr w = nullptr;

    if (x != nullptr)
        x->_parent = y->_parent;
    if (_tree_is_left_child(y))
    {
        y->_parent->_left = x;
        if (y != root)
            w = y->_parent_unsafe()->_right;
        else
            root = x;
    }
    else
    {
        y->_parent_unsafe()->_right = x;
        w = y->_parent->_left;
    }
    bool _removed_black = y->_is_black;
    if (y != z)
    {
        y->_parent = z->_parent;
        if (_tree_is_left_child(z))
            y->_parent->_left = y;
        else
            y->_parent_unsafe()->_right = y;
        y->_left = z->_left;
        y->_left->_set_parent(y);
        y->_right = z->_right;
        if (y->_right != nullptr)
            y->_right->_set_parent(y);
        y->_is_black = z->_is_black;
        if (root == z)
            root = y;
    }
    if (_removed_black && root != nullptr)
    {
        if (x != nullptr)
            x->_is_black = true;
        else
        {
            while (true)
            {
                if (!_tree_is_left_child(w))
                {
                    if (!w->_is_black)
                    {
                        w->_is_black = true;
                        w->_parent_unsafe()->_is_black = false;
                        _tree_left_rotate(w->_parent_unsafe());
                        if (root == w->_left)
                            root = w;
                        w = w->_left->_right;
                    }
                    if ((w->_left == nullptr || w->_left->_is_black) &&
                            (w->_right == nullptr || w->_parent_unsafe()))
                    {
                        w->_is_black = false;
                        x = w->_parent_unsafe();
                        if (x == root || !x->_is_black)
                        {
                            x->_is_black = true;
                            break;
                        }
                        w = _tree_is_left_child(x) ? x->_parent_unsafe()->_right : x->_parent->_left;
                    }
                    else
                    {
                        if (w->_right == nullptr || w->_right->_is_black)
                        {
                            w->_left->_is_black = true;
                            w->_is_black = false;
                            _tree_right_rotate(w);
                            w = w->_parent_unsafe();
                        }
                        w->_is_black = w->_parent_unsafe()->_is_black;
                        w->_parent_unsafe()->_is_black = true;
                        w->_right->_is_black = true;
                        _tree_left_rotate(w->_parent_unsafe());
                        break;
                    }
                }
                else
                {
                    if (!w->_is_black)
                    {
                        w->_is_black = true;
                        w->_parent_unsafe()->_is_black = false;
                        _tree_right_rotate(w->_parent_unsafe());
                        if (root == w->_right)
                            root = w;
                        w = w->_right->_left;
                    }
                    if ((w->_left == nullptr || w->_left->_is_black) &&
                            (w->_right == nullptr || w->_right->_is_black))
                    {
                        w->_is_black = false;
                        x = w->_parent_unsafe();
                        if (!x->_is_black || x == root)
                        {
                            x->_is_black = true;
                            break;
                        }
                        w = _tree_is_left_child(x) ? x->_parent_unsafe()->_right : x->_parent->_left;
                    }
                    else
                    {
                        if (w->_left == nullptr || w->_left->_is_black)
                        {
                            w->_right->_is_black = true;
                            w->_is_black = false;
                            _tree_left_rotate(w);
                            w = w->_parent_unsafe();
                        }
                        w->_is_black = w->_parent_unsafe()->_is_black;
                        w->_parent_unsafe()->_is_black = true;
                        w->_left->_is_black = true;
                        _tree_right_rotate(w->_parent_unsafe());
                        break;
                    }
                }
            }
        }
    }
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
        typedef typename conditional<is_pointer<_end_node_pointer>::value,
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
        typedef typename conditional<is_pointer<_node_pointer>::value,
            typename _base::_end_node_pointer, _node_pointer>::type _iter_pointer;
    };

//    make_tree_node_types
    template<class ValueT, class VoidPtr>
    struct _make_tree_node_types
    {
        typedef typename _rebind_pointer<VoidPtr, _tree_node<ValueT, VoidPtr> >::type _NodePtr;
        typedef _tree_node_types<_NodePtr> type;
    };

    //    tree_node_destructor
    template <class _Allocator>
    class _tree_node_destructor
    {
        typedef _Allocator                                      allocator_type;

    public:
        typedef typename allocator_type::pointer                pointer;
    private:
        typedef _tree_node_types<pointer> _NodeTypes;
        allocator_type& __na_;

        _tree_node_destructor& operator=(const _tree_node_destructor&);

    public:
        bool __value_constructed;

        explicit _tree_node_destructor(allocator_type& __na, bool __val = false): __na_(__na),
        __value_constructed(__val)
        {}

        void operator()(pointer __p)
        {
            if (__value_constructed)
                allocator_type::destroy(__na_, _NodeTypes::__get_ptr(__p->__value_));
            if (__p)
                allocator_type::deallocate(__na_, __p, 1);
        }

        template <class> friend class __map_node_destructor;
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
        explicit _tree_iterator(_end_node_pointer p): _ptr(p) {}
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

        _node_pointer _root() const
        {
            return static_cast<_node_pointer>(_end_node()->_left);
        }

        _node_base_pointer* _root_ptr() const
        {
            return addressof(_end_node()->_left);
        }

		explicit _tree(const value_compare& comp):
				_begin_node_(_iter_pointer()),
				_pair1_(_default_init_tag(), _node_allocator(comp)),
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

        typedef _tree_node_destructor<_node_allocator> Dp;
        typedef unique_ptr<_node, Dp> _node_holder;

        void _insert_node_at(_parent_pointer parent, _node_base_pointer& child, _node_base_pointer new_node);

        iterator _insert_multi(const _container_value_type& v)
        {
            _parent_pointer parent;
            _node_base_pointer& child = _find_leaf_high(parent, _NodeTypes::_get_key(v));
            _node_holder h = _construct_node(v);
            _insert_node_at(parent, child, static_cast<_node_base_pointer>(h.get()));
            return iterator(h.release());
        }

        iterator _insert_multi(const_iterator p, const _container_value_type& v)
        {
            _parent_pointer parent;
            _node_base_pointer& child = _find_leaf(p, parent, _NodeTypes::_get_key(v));
            _node_holder h = _construct_node(v);
            _insert_node_at(parent, child, static_cast<_node_base_pointer>(h.get()));
            return iterator(h.release());
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

        ~_tree();

        iterator begin() {return iterator(_begin_node());}
        const_iterator begin() const {return const_iterator(_begin_node());}
        iterator end() {return iterator(_end_node());}
        const_iterator end() const {return const_iterator(_end_node());}

        size_type max_size() const
        {
            return std::min<size_type>(_node_allocator::max_size(_node_alloc()),
                                       std::numeric_limits<difference_type>::max());
        }

        void clear();

        void swap(_tree& t);

        template <class Key, class Args>
        pair<iterator, bool> _emplace_unique_key_args(Key const& k, Args& args);

        template <class Key, class Args>
        iterator _emplace_hint_unique_key_args(const_iterator, Key const&, Args&);

        pair<iterator, bool> _insert_unique(const _container_value_type& v)
        {
            return _emplace_unique_key_args(_NodeTypes::_get_key(v), v);
        }

        iterator _insert_unique(const_iterator p, const _container_value_type& v)
        {
            return _emplace_hint_unique_key_args(p, _NodeTypes::_get_key(v), v);
        }

        pair<iterator, bool> _node_insert_unique(_node_pointer nd);

        iterator _node_insert_unique(const_iterator p, _node_pointer nd);

        iterator _node_insert_multi(_node_pointer n)
		{
			_parent_pointer  _parent;
			_node_base_pointer& _child = _find_leaf_high(_parent, _NodeTypes::_get_key(n->_value));
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

        iterator _remove_node_pointer(_node_pointer);

        iterator erase(const_iterator p);

        iterator erase(const_iterator f, const_iterator l);

        template <class Key>
        size_type _erase_unique(const Key& k);

        template <class Key>
        size_type _erase_multi(const Key& k);

        template <class Key>
        iterator find(const Key& v);

        template <class Key>
        const_iterator find(const Key& v) const;

        template <class Key>
        size_type _count_unique(const Key& k) const;

        template <class Key>
        size_type _count_multi(const Key& k) const;

        template <class Key>
        iterator lower_bound(const Key& v)
        {
            return _lower_bound(v, _root(), _end_node());
        }

        template <class Key>
        iterator _lower_bound(const Key& v, _node_pointer root, _iter_pointer result);

        template <class Key>
        const_iterator lower_bound(const Key& v) const
        {
            return _lower_bound(v, _root(), _end_node());
        }

        template <class Key>
        const_iterator _lower_bound(const Key& v, _node_pointer root, _iter_pointer result) const;

        template <class Key>
        iterator upper_bound(const Key& v)
        {
            return _upper_bound(v, _root(), _end_node());
        }

        template <class Key>
        iterator _upper_bound(const Key& v, _node_pointer root, _iter_pointer result);

        template <class Key>
        const_iterator upper_bound(const Key& v) const
        {
            return _upper_bound(v, _root(), _end_node());
        }

        template <class Key>
        const_iterator _upper_bound(const Key& v, _node_pointer __root, _iter_pointer result) const;

        template <class Key>
        pair<iterator, iterator>
        _equal_range_unique(const Key& k);

        template <class Key>
        pair<const_iterator, const_iterator>
        _equal_range_unique(const Key& k) const;

        template <class Key>
        _node_base_pointer& _find_equal(_parent_pointer& parent, const Key& v);

        template <class Key>
        pair<iterator, iterator>
        _equal_range_multi(const Key& k);

        template <class Key>
        pair<const_iterator, const_iterator>
        _equal_range_multi(const Key& k) const;

        _node_holder remove(const_iterator p);
	private:
        void _copy_assign_alloc(const _tree& t) {}

        template <class Key>
        inline _node_base_pointer& _find_equal(_parent_pointer& parent, const Key& v) const
        {
            return const_cast<_tree*>(this)->_find_equal(parent, v);
        }

        template <class Key>
        _node_base_pointer& _find_equal(const_iterator hint, _parent_pointer& parent, _node_base_pointer& dummy,
                                        const Key& v);

        _node_holder _construct_node(const _container_value_type& v);

        void destroy(_node_pointer nd);

		_node_base_pointer& _find_leaf_low(_parent_pointer& _parent, const key_type& v)
		{
			_node_pointer n = _root();
			if (n != nullptr)
			{
				while (true)
				{
					if (value_comp()(n->_value, v))
					{
						if (n->_right != 0)
							n = static_cast<_node_pointer>(n->_right);
						else
						{
							_parent = static_cast<_parent_pointer>(n);
							return n->_right;
						}
					}
					else
					{
						if (n->_left != 0)
							n = static_cast<_node_pointer>(n->_left);
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
			_node_pointer n = _root();
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
						_parent = static_cast<_parent_pointer>(hint._ptr);
						return _parent->_left;
					}
					else
					{
						_parent = static_cast<_parent_pointer>(prior._ptr);
						return static_cast<_node_base_pointer>(prior._ptr)->_right;
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

			static _node_pointer _detach_next(_node_pointer _cache)
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

        template <class, class, class, class> friend class map;
    };

    template <class T, class Compare, class Allocator>
    void _tree<T, Compare, Allocator>::_insert_node_at(
            _parent_pointer parent, _node_base_pointer& child,
            _node_base_pointer new_node)
    {
        new_node->_left_   = nullptr;
        new_node->_right_  = nullptr;
        new_node->_parent_ = parent;
        child = new_node;
        if (_begin_node()->_left != nullptr)
            _begin_node() = static_cast<_iter_pointer>(_begin_node()->_left);
        _tree_balance_after_insert(_end_node()->_left, child);
        ++size();
    }

    template <class T, class Compare, class Allocator>
    _tree<T, Compare, Allocator>::~_tree()
    {
        destroy(_root());
    }

    template <class T, class Compare, class Allocator>
    void _tree<T, Compare, Allocator>::destroy(_node_pointer nd)
    {
        if (nd != nullptr)
        {
            destroy(static_cast<_node_pointer>(nd->_left));
            destroy(static_cast<_node_pointer>(nd->_right));
            _node_allocator& na = _node_alloc();
            _node_allocator::destroy(na, _NodeTypes::_get_ptr(nd->_value));
            _node_allocator::deallocate(na, nd, 1);
        }
    }

    template <class T, class Compare, class Allocator>
    void _tree<T, Compare, Allocator>::clear()
    {
        destroy(_root());
        size() = 0;
        _begin_node() = _end_node();
        _end_node()->_left = nullptr;
    }

    template <class T, class Compare, class Allocator>
    void _tree<T, Compare, Allocator>::swap(_tree& t)
    {
        std::swap(_begin_node_, t._begin_node_);
        std::swap(_pair1_.first(), t._pair1_.first());
        _pair3_.swap(t._pair3_);
        if (size() == 0)
            _begin_node() = _end_node();
        else
            _end_node()->_left->_parent = static_cast<_parent_pointer>(_end_node());
        if (t.size() == 0)
            t._begin_node() = t._end_node();
        else
            t._end_node()->_left->_parent = static_cast<_parent_pointer>(t._end_node());
    }

    template <class T, class Compare, class Allocator>
    template <class Key, class Args>
    pair<typename _tree<T, Compare, Allocator>::iterator, bool>
    _tree<T, Compare, Allocator>::_emplace_unique_key_args(const Key & k, Args &args)
    {
        _parent_pointer parent;
        _node_base_pointer& child = _find_equal(parent, k);
        _node_pointer r = static_cast<_node_pointer>(child);
        bool inserted = false;
        if (child == nullptr)
        {
            _node_holder h = _construct_node(args);
            _insert_node_at(parent, child, static_cast<_node_base_pointer>(h.get()));
            r = h.release();
            inserted = true;
        }
        return pair<iterator, bool>(iterator(r), inserted);
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::_node_base_pointer&
    _tree<T, Compare, Allocator>::_find_equal(_parent_pointer &parent, const Key &v)
    {
        _node_pointer nd = _root();
        _node_base_pointer* nd_ptr = _root_ptr();
        if (nd != nullptr)
        {
            while(true)
            {
                if (value_comp()(v, nd->_value))
                {
                    if (nd->_left != nullptr)
                    {
                        nd_ptr = addressof(nd->_left);
                        nd = static_cast<_node_pointer>(nd->_left);
                    }
                    else
                    {
                        parent = static_cast<_parent_pointer>(nd);
                        return parent->_left;
                    }
                }
                else if (value_comp()(nd->_value, v))
                {
                    if (nd->_right != nullptr)
                    {
                        nd_ptr = addressof(nd->_right);
                        nd = static_cast<_node_pointer>(nd->_right);
                    }
                    else
                    {
                        parent = static_cast<_parent_pointer>(nd);
                        return nd->_right;
                    }
                }
                else
                {
                    parent = static_cast<_parent_pointer>(nd);
                    return *nd_ptr;
                }
            }
        }
        parent = static_cast<_parent_pointer>(_end_node());
        return parent->_left;
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::_node_base_pointer&
    _tree<T, Compare, Allocator>::_find_equal(const_iterator hint, _parent_pointer &parent, _node_base_pointer &dummy,
                                              const Key& v)
    {
        if (hint == end() || value_comp()(v, *hint))
        {
            const_iterator prior = hint;
            if (prior == begin() || value_comp()(*--prior, v))
            {
                if (hint._ptr->_left == nullptr)
                {
                    parent = static_cast<_parent_pointer>(hint._ptr);
                    return parent->_left;
                }
                else
                {
                    parent = static_cast<_parent_pointer>(prior._ptr);
                    return static_cast<_node_base_pointer>(prior._ptr)->_right;
                }
            }
            return _find_equal(parent, v);
        }
        else if (value_comp()(*hint, v))
        {
            const_iterator _next = next(hint);
            if (_next == end() || value_comp()(v, *_next))
            {
                if (hint._get_np()->_right = nullptr)
                {
                    parent = static_cast<_parent_pointer>(hint._ptr);
                    return static_cast<_node_base_pointer>(hint._ptr)->_right;
                }
                else
                {
                    parent = static_cast<_parent_pointer>(_next._ptr);
                    return parent->_left;
                }
            }
            return _find_equal(parent, v);
        }
        parent = static_cast<_parent_pointer>(hint._ptr);
        dummy = static_cast<_node_base_pointer>(hint._ptr);
        return dummy;
    }

    template <class T, class Compare, class Allocator>
    typename _tree<T, Compare, Allocator>::_node_holder
    _tree<T, Compare, Allocator>::_construct_node(const _container_value_type &v)
    {
        _node_allocator& na = _node_alloc();
        _node_holder h(allocator_type::allocate(na, 1), Dp(na));
        allocator_type::construct(na, _NodeTypes::_get_ptr(h->_value), v);
        h.get_deleter().__value_constructed = true;
        return _LIBCPP_EXPLICIT_MOVE(h);
    }

    template <class T, class Compare, class Allocator>
    template <class Key, class Args>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::_emplace_hint_unique_key_args(const_iterator p, Key const& k, Args& args)
    {
        _parent_pointer parent;
        _node_base_pointer dummy;
        _node_base_pointer& child = _find_equal(p, parent, dummy, k);
        _node_pointer r = static_cast<_node_pointer>(child);
        if (child == nullptr)
        {
            _node_holder h = _construct_node(args);
            _insert_node_at(parent, child, static_cast<_node_base_pointer>(h.get()));
            r = h.release();
        }
        return iterator(r);
    }

    template <class T, class Compare, class Allocator>
    pair<typename _tree<T, Compare, Allocator>::iterator, bool>
    _tree<T, Compare, Allocator>::_node_insert_unique(_node_pointer nd)
    {
        _parent_pointer parent;
        _node_base_pointer& child = _find_equal(parent, nd->_value);
        _node_pointer r = static_cast<_node_pointer>(child);
        bool inserted = false;
        if (child == nullptr)
        {
            _insert_node_at(parent, child, static_cast<_node_base_pointer>(nd));
            r = nd;
            inserted = true;
        }
        return pair<iterator, bool>(iterator(r), inserted);
    }

    template <class T, class Compare, class Allocator>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::_node_insert_unique(const_iterator p, _node_pointer nd)
    {
        _parent_pointer parent;
        _node_base_pointer dummy;
        _node_base_pointer& child = _find_equal(p, parent, nd->_value);
        _node_pointer r = static_cast<_node_pointer>(child);
        if (child == nullptr)
        {
            _insert_node_at(parent, child, static_cast<_node_base_pointer>(nd));
            r = nd;
        }
        return iterator(r);
    }

    template <class T, class Compare, class Allocator>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::_remove_node_pointer(_node_pointer ptr)
    {
        iterator r(ptr);
        ++r;
        if (_begin_node() == ptr)
            _begin_node() = r._ptr;
        --size();
        _tree_remove(_end_node()->_left, static_cast<_node_base_pointer>(ptr));
        return r;
    }

    template <class T, class Compare, class Allocator>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::erase(const_iterator p)
    {
        _node_pointer np = p._get_np();
        iterator r = _remove_node_pointer(np);
        _node_allocator& na = _node_alloc();
        allocator_type::destroy(na, _NodeTypes::_get_ptr(const_cast<_node_value_type&>(*p)));
        allocator_type::deallocate(na, np, 1);
        return r;
    }

    template <class T, class Compare, class Allocator>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::erase(const_iterator f, const_iterator l)
    {
        while (f != l)
            f = erase(f);
        return iterator(l._ptr);
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::size_type
    _tree<T, Compare, Allocator>::_erase_unique(const Key &k)
    {
        iterator i = find(k);
        if (i == end())
            return 0;
        erase(i);
        return 1;
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::size_type
    _tree<T, Compare, Allocator>::_erase_multi(const Key &k)
    {
        pair<iterator, iterator> p = _equal_range_multi(k);
        size_type r = 0;
        for (; p.first != p.second; ++r)
            p.first = erase(p.first);
        return r;
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::find(const Key& v)
    {
        iterator p = _lower_bound(v, _root(), _end_node());
        if (p != end() && !value_comp()(v, *p))
            return p;
        return end();
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::const_iterator
    _tree<T, Compare, Allocator>::find(const Key& v) const
    {
        const_iterator p = _lower_bound(v, _root(), _end_node());
        if (p != end() && !value_comp()(v, *p))
            return p;
        return end();
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::size_type
    _tree<T, Compare, Allocator>::_count_unique(const Key &k) const
    {
        _node_pointer rt = _root();
        while (rt != nullptr)
        {
            if (value_comp()(k, rt->_value))
                rt = static_cast<_node_pointer>(rt->_left);
            else if (value_comp()(rt->_value, k))
                rt = static_cast<_node_pointer>(rt->_right);
            else
                return 1;
        }
        return 0;
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::size_type
    _tree<T, Compare, Allocator>::_count_multi(const Key &k) const
    {
        _iter_pointer result = _end_node();
        _node_pointer rt = _root();
        while (rt != nullptr)
        {
            if (value_comp()(k, rt->_value))
            {
                result = static_cast<_iter_pointer>(rt);
                rt = static_cast<_node_pointer>(rt->_left);
            }
            else if (value_comp()(rt->_value, k))
                rt = static_cast<_node_pointer>(rt->_right);
            else
                return distance(
                        _lower_bound(k, static_cast<_node_pointer>(rt->_left), static_cast<_iter_pointer>(rt)),
                        _upper_bound(k, static_cast<_node_pointer>(rt->_right), result));
        }
        return 0;
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::_lower_bound(const Key& v, _node_pointer root, _iter_pointer result)
    {
        while (root != nullptr)
        {
            if (!value_comp()(root->__value_, v))
            {
                result = static_cast<_iter_pointer>(_root);
                root = static_cast<_node_pointer>(root->_left);
            }
            else
                root = static_cast<_node_pointer>(root->_right);
        }
        return iterator(result);
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::const_iterator
    _tree<T, Compare, Allocator>::_lower_bound(const Key& v, _node_pointer root, _iter_pointer result) const
    {
        while (root != nullptr)
        {
            if (!value_comp()(root->__value_, v))
            {
                result = static_cast<_iter_pointer>(_root);
                root = static_cast<_node_pointer>(root->_left);
            }
            else
                root = static_cast<_node_pointer>(root->_right);
        }
        return const_iterator(result);
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::iterator
    _tree<T, Compare, Allocator>::_upper_bound(const Key& v, _node_pointer root, _iter_pointer result)
    {
        while (root != nullptr)
        {
            if (value_comp()(v, root->_value))
            {
                result = static_cast<_iter_pointer>(root);
                root = static_cast<_node_pointer>(root->_left);
            }
            else
                root = static_cast<_node_pointer>(root->_right);
        }
        return iterator(result);
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    typename _tree<T, Compare, Allocator>::const_iterator
    _tree<T, Compare, Allocator>::_upper_bound(const Key& v, _node_pointer root, _iter_pointer result) const
    {
        while (root != nullptr)
        {
            if (value_comp()(v, root->_value))
            {
                result = static_cast<_iter_pointer>(root);
                root = static_cast<_node_pointer>(root->_left);
            }
            else
                root = static_cast<_node_pointer>(root->_right);
        }
        return const_iterator(result);
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    pair<typename _tree<T, Compare, Allocator>::iterator,
            typename _tree<T, Compare, Allocator>::iterator>
    _tree<T, Compare, Allocator>::_equal_range_unique(const Key& k)
    {
        typedef pair<iterator, iterator> Pp;
        _iter_pointer result = _end_node();
        _node_pointer rt = _root();
        while (rt != nullptr)
        {
            if (value_comp()(k, rt->_value))
            {
                result = static_cast<_iter_pointer>(rt);
                rt = static_cast<_node_pointer>(rt->_left);
            }
            else if (value_comp()(rt->_value, k))
                rt = static_cast<_node_pointer>(rt->_right);
            else
                return Pp(iterator(rt),
                    iterator(rt->_right != nullptr ? static_cast<_iter_pointer>(__tree_min(rt->_right)) : result));
        }
        return Pp(iterator(result), iterator(result));
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    pair<typename _tree<T, Compare, Allocator>::const_iterator,
            typename _tree<T, Compare, Allocator>::const_iterator>
    _tree<T, Compare, Allocator>::_equal_range_unique(const Key& k) const
    {
        typedef pair<const_iterator, const_iterator> Pp;
        _iter_pointer result = _end_node();
        _node_pointer rt = _root();
        while (rt != nullptr)
        {
            if (value_comp()(k, rt->_value))
            {
                result = static_cast<_iter_pointer>(rt);
                rt = static_cast<_node_pointer>(rt->_left);
            }
            else if (value_comp()(rt->_value, k))
                rt = static_cast<_node_pointer>(rt->_right);
            else
                return Pp(const_iterator(rt),
                          const_iterator(rt->_right != nullptr ? static_cast<_iter_pointer>(__tree_min(rt->_right)) : result));
        }
        return Pp(const_iterator(result), const_iterator(result));
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    pair<typename _tree<T, Compare, Allocator>::iterator,
            typename _tree<T, Compare, Allocator>::iterator>
    _tree<T, Compare, Allocator>::_equal_range_multi(const Key& k)
    {
        typedef pair<iterator, iterator> Pp;
        _iter_pointer result = _end_node();
        _node_pointer rt = _root();
        while (rt != nullptr)
        {
            if (value_comp()(k, rt->_value))
            {
                result = static_cast<_iter_pointer>(rt);
                rt = static_cast<_node_pointer>(rt->_left);
            }
            else if (value_comp()(rt->_value, k))
                rt = static_cast<_node_pointer>(rt->_right);
            else
                return Pp(_lower_bound(k, static_cast<_node_pointer>(rt->_left), static_cast<_iter_pointer>(rt)),
                           _upper_bound(k, static_cast<_node_pointer>(rt->_right), result));
        }
        return Pp(iterator(result), iterator(result));
    }

    template <class T, class Compare, class Allocator>
    template <class Key>
    pair<typename _tree<T, Compare, Allocator>::const_iterator,
            typename _tree<T, Compare, Allocator>::const_iterator>
    _tree<T, Compare, Allocator>::_equal_range_multi(const Key& k) const
    {
        typedef pair<const_iterator, const_iterator> Pp;
        _iter_pointer result = _end_node();
        _node_pointer rt = _root();
        while (rt != nullptr)
        {
            if (value_comp()(k, rt->_value))
            {
                result = static_cast<_iter_pointer>(rt);
                rt = static_cast<_node_pointer>(rt->_left);
            }
            else if (value_comp()(rt->_value, k))
                rt = static_cast<_node_pointer>(rt->_right);
            else
                return Pp(_lower_bound(k, static_cast<_node_pointer>(rt->_left), static_cast<_iter_pointer>(rt)),
                          _upper_bound(k, static_cast<_node_pointer>(rt->_right), result));
        }
        return Pp(const_iterator(result), const_iterator(result));
    }

    template <class T, class Compare, class Allocator>
    typename _tree<T, Compare, Allocator>::_node_holder
    _tree<T, Compare, Allocator>::remove(const_iterator p)
    {
        _node_pointer np = p._get_np();
        if (_begin_node() == p._ptr)
        {
            if (np->_right != nullptr)
                _begin_node() = static_cast<_iter_pointer>(np->_right);
            else
                _begin_node() = static_cast<_iter_pointer>(np->parent);
        }
        --size();
        __tree_remove(_end_node()->_left,
                      static_cast<_node_base_pointer>(np));
        return __node_holder(np, Dp(_node_alloc(), true));
    }
}
#endif
