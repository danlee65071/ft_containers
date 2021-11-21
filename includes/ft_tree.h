/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:35:26 by                   #+#    #+#             */
/*   Updated: 2021/11/21 17:06:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_TREE_H
#define FT_CONTAINERS_FT_TREE_H

# include <memory>
# include "ft_memory.hpp"

namespace ft
{
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
    };
}
#endif
