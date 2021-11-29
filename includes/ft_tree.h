/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:35:26 by                   #+#    #+#             */
/*   Updated: 2021/11/29 23:23:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_TREE_H
#define FT_CONTAINERS_FT_TREE_H

# include <memory>
# include "ft_memory.hpp"
# include "ft_utility.hpp"

namespace ft
{
//    prototypes
    template<class VoidPtr> class _tree_node_base;
    template<class Pointer> class _tree_end_node;

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
    struct _tree_node_types<NodePtr, _tree_node<T, VoidPtr>>:
            public _tree_node_base_types<VoidPtr>,
                   _tree_key_value_types<T>,
                   _tree_map_pointer_types<T, VoidPtr>
    {
        typedef _tree_node_base_types<VoidPtr> _base;
        typedef _tree_key_value_types<T> _key_base;
        typedef _tree_map_pointer_types<T, VoidPtr> _map_pointer_base;
    public:
        typedef typename pointer_traits<NodePtr>::element_type _node_type;
        typedef _NodePtr _node_pointer;
        typedef T _node_value_type;
        typedef typename _rebind_pointer<VoidPtr, _node_value_type>::type _node_type_pointer;
        typedef typename _tree_map_pointer_types<T, VoidPtr> _map_pointer_base;
        typedef typename conditioinal<is_pointer<_node_pointer>::value,
            typename _base::_end_node_pointer, _node_pointer>::type _iter_pointer;
    };

//    make_tree_node_types
    template<class ValueT, class VoidPtr>
    struct _make_tree_node_types
    {
        typedef typename _rebind_pointer<VoidPtr, _tree_node<ValueT, ValuePtr> >::type _NodePtr;
        typedef _tree_node_types<_NodePtr> type;
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
        typedef typename allocator_type::rebind<_node>::other _node_allocator;
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
        const _node_allocator& _node_alloc() const {return _pair1_.second();} // ?

        _iter_pointer& _begin_node() {return _begin_node_;} // ?

        const _iter_pointer& _begin_node() const {return _begin_node_} // ?
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
    };
}
#endif
