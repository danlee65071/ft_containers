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
    template <class Allocator>
    class _map_node_destructor
    {
        typedef Allocator                          allocator_type;
    public:
        typedef typename allocator_type::pointer    pointer;

    private:
        allocator_type& _na;
    public:
        bool _first_constructed;
        bool _second_constructed;
        explicit _map_node_destructor(allocator_type& na): _na(na),
                  _first_constructed(false),
                  _second_constructed(false)
        {}
        void operator()(pointer p)
        {
            if (_second_constructed)
                allocator_type::destroy(_na, addressof(p->_value._get_value().second));
            if (_first_constructed)
                allocator_type::destroy(_na, addressof(p->_value._get_value().first));
            if (p)
                allocator_type::deallocate(_na, p, 1);
        }
    };

    template <class Key, class CP, class Compare, bool = is_empty<Compare>::value>
    class _map_value_compare
    {
    public:
//        _map_value_compare(): Compare() {}
//
//        _map_value_compare(Compare c): Compare(c) {}

        const Compare& key_comp() const { return *this; }

        bool operator()(const CP& x, const CP& y) const
        {
            return static_cast<const Compare&>(*this)(x._get_value().first, y._get_value().first);
        }

        bool operator()(const CP& x, const Key& y) const
        {
            return static_cast<const Compare&>(*this)(x._get_value().first, y);
        }

        bool operator()(const Key& x, const CP& y) const
        {
            return static_cast<const Compare&>(*this)(x, y._get_value().first);
        }

        void swap(_map_value_compare& y)
        {
            std::swap(static_cast<Compare&>(*this), static_cast<Compare&>(y));
        }
    };

    template <class Key, class T, class Compare, class Allocator>
    class map;
    template <class TreeIterator> class _map_const_iterator;

    template <class Key, class T>
    struct _value_type
    {
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const key_type, mapped_type> value_type;
    private:
        value_type _cc;
    public:
        value_type& _get_value() { return _cc; }
        const value_type& _get_value() const { return _cc; }
    private:
        _value_type();
        _value_type(_value_type const&);
        _value_type operator=(_value_type const&);
        ~_value_type();
    };

    template<class TreeIterator>
    class _map_iterator
    {
    private:
        typedef typename TreeIterator::_NodeTypes _NodeTypes;
        typedef typename TreeIterator::_pointer_traits _pointer_traits;

        TreeIterator it;
    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef typename _NodeTypes::_node_value_type value_type;
        typedef typename TreeIterator::difference_type difference_type;
        typedef const value_type& reference;
        typedef typename _NodeTypes::_map_pointer_base pointer;

        _map_iterator(){}
        _map_iterator(TreeIterator other): it(other) {}

        reference operator*() const { return it->_get_value(); }
        pointer operator->() const { return it; }

        _map_iterator& operator++() { ++it; return *this; }
        _map_iterator operator++(int)
        {
            _map_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        _map_iterator& operator--() {--it; return *this;}
        _map_iterator operator--(int)
        {
            _map_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        friend bool operator==(const _map_iterator& x, const _map_iterator& y)
        {return x.it == y.it;}

        friend bool operator!=(const _map_iterator& x, const _map_iterator& y)
        {return x.it != y.it;}

        template <class, class, class, class> friend class map;
        template <class> friend class _map_const_iterator;
    };

    template <class TreeIterator>
    class _map_const_iterator
    {
    private:
        typedef typename TreeIterator::_NodeTypes _NodeTypes;
        typedef typename TreeIterator::_pointer_traits _pointer_traits;

        TreeIterator _i;
    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef typename _NodeTypes::_map_value_type value_type;
        typedef typename TreeIterator::difference_type difference_type;
        typedef const value_type& reference;
        typedef typename _NodeTypes::_const_map_value_type_pointer pointer;

        _map_const_iterator() {}

        _map_const_iterator(TreeIterator i): _i(i) {}

        _map_const_iterator(_map_iterator<typename TreeIterator::_non_const_iterator> i): _i(i._i) {}

        reference operator*() const { return _i->_get_value(); }

        pointer operator->() const { return pointer_traits<pointer>::pointer_to(_i->_get_value()); }

        _map_const_iterator& operator++() { ++_i; return *this; }

        _map_const_iterator operator++(int)
        {
            _map_const_iterator _t(*this);
            ++(*this);
            return _t;
        }

        _map_const_iterator& operator--() {--_i; return *this;}

        _map_const_iterator operator--(int)
        {
            _map_const_iterator _t(*this);
            --(*this);
            return _t;
        }

        friend bool operator==(const _map_const_iterator& x, const _map_const_iterator& y) { return x._i == y._i; }

        friend bool operator!=(const _map_const_iterator& x, const _map_const_iterator& y) { return x._i != y._i; }

        template <class, class, class, class> friend class map;
        template <class, class, class> friend class _tree_const_iterator;
    };

    template < class Key, class T, class Compare = std::less<Key>,
            class Alloc = std::allocator<pair<const Key,T> > >
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
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        class  value_compare
        {
            friend class map;
        protected:
            Compare comp;
            value_compare (Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };
    private:
        typedef _value_type<key_type, mapped_type> _value_type;
        typedef _map_value_compare<key_type, _value_type, key_compare> _vc;
        typedef _tree<_value_type, _vc, allocator_type> _base;
        typedef typename _base::_node _node;
        typedef typename _base::_node_allocator _node_allocator;
        typedef typename _base::_node_pointer _node_pointer;
        typedef typename _base::_node_base_pointer _node_base_pointer;
        typedef typename _base::_parent_pointer _parent_pointer;
        typedef _map_node_destructor<_node_allocator> Dp;
        typedef unique_ptr<_node, Dp> _node_holder;

        _node_holder _construct_node_with_key(const key_type& k);

        _base __tree;
    public:
        typedef _map_iterator<typename _base::iterator> iterator;
        typedef _map_const_iterator<typename _base::const_iterator> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

        map(): __tree(_vc()) {}

        explicit map(const key_compare& comp): __tree(_vc(comp)) {}

        explicit map (const key_compare& comp, const allocator_type& alloc):
            __tree(_vc(comp), typename _base::allocator_type(alloc)) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()): __tree(_vc(comp), typename _base::allocator_type(alloc))
        {
            insert(first, last);
        }

        map (const map& x): __tree(x.__tree)
        {
            insert(x.begin(), x.end());
        }

        iterator begin() { return __tree.begin(); }

        const_iterator begin() const { return __tree.begin(); }

        iterator end() { return __tree.end(); }

        const_iterator end() const { return __tree.end(); }

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        bool empty() const { return __tree.size() == 0; }

        size_type size() const { return __tree.size(); }

        size_type max_size() const  { return __tree.max_size(); }

        mapped_type& operator[] (const key_type& k);

        pair<iterator,bool> insert (const value_type& val) { return __tree._insert_unique(val); }

        iterator insert (iterator position, const value_type& val) {return __tree._insert_unique(position.__i, val);}

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            for (const_iterator e = end(); first != last; ++first)
                insert(e.__i, *first);
        }

        void erase (iterator position) {return __tree.erase(position.__i);}

        size_type erase (const key_type& k) {return __tree._erase_unique(k);}

        void erase (iterator first, iterator last) {return __tree.erase(first.__i, last.__i);}

        void swap (map& x) {__tree.swap(x.__tree);}

        void clear() {__tree.clear();}

        key_compare key_comp() const {return __tree.value_comp().key_comp();}

        value_compare value_comp() const {return value_compare(__tree.value_comp().key_comp());}

        iterator find (const key_type& k) {return __tree.find(k);}

        const_iterator find (const key_type& k) const {return __tree.find(k);}

        size_type count (const key_type& k) const {return __tree._count_unique(k);}

        iterator lower_bound (const key_type& k) {return __tree.lower_bound(k);}

        const_iterator lower_bound (const key_type& k) const {return __tree.lower_bound(k);}

        iterator upper_bound (const key_type& k) {return __tree.upper_bound(k);}

        const_iterator upper_bound (const key_type& k) const {return __tree.upper_bound(k);}

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const {return __tree._equal_range_unique(k);}

        pair<iterator,iterator> equal_range (const key_type& k) {return __tree.__equal_range_unique(k);}

        allocator_type get_allocator() const {return allocator_type(__tree._alloc());}
    };

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::_node_holder
    map<Key, T, Compare, Alloc>::_construct_node_with_key(const key_type& k)
    {
        _node_allocator& na = __tree._node_alloc();
        _node_holder h(_node_allocator::allocate(na, 1), Dp(na));
        _node_allocator::construct(na, addressof(h->_value._get_value().first), k);
        h.get_deleter()._first_constructed = true;
        _node_allocator::construct(na, addressof(h->_value._get_value().second));
        h.get_deleter()._second_constructed = true;
        return move(h);
    }

    template <class Key, class T, class Compare, class Alloc>
    T& map<Key, T, Compare, Alloc>::operator[](const key_type& k)
    {
        _parent_pointer parent;
        _node_base_pointer& child = __tree._find_equal(parent, k);
        _node_pointer r = static_cast<_node_pointer>(child);
        if (child == nullptr)
        {
            _node_holder h = _construct_node_withkey(k);
            __tree._insert_node_at(parent, child, static_cast<_node_base_pointer>(h.get()));
            r = h.release();
        }
        return r->_value._get_value().second;
    }
}

#endif
