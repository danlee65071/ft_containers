/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:47:53 by                   #+#    #+#             */
/*   Updated: 2021/11/21 18:52:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_MEMORY_HPP
#define FT_CONTAINERS_FT_MEMORY_HPP

# include "ft_type_traits.hpp"

namespace ft
{
//	_default_init_tag
	struct _default_init_tag {};

//    has_element_type
    template<class T, class = void>
    struct _has_element_type: false_type {};

    template<class T>
    struct _has_element_type<T, typename _void_t<typename T::element_type>::type>: true_type {};

//    _pointer_element_type
    template<class Ptr, bool = _has_element_type<Ptr>::value>
    struct _pointer_element_type;

    template<class Ptr>
    struct _pointer_element_type<Ptr, true>
    {
        typedef typename Ptr::element_type type;
    };

//    _has_difference_type
    template<class T, class = void>
    struct _has_difference_type: false_type {};

    template <class T>
    struct _has_difference_type<T, typename _void_t<typename T::difference_type>::type> : true_type {};

//    _pointer_traits_difference_type
    template<class Ptr, bool = _has_difference_type<Ptr>::value>
    struct _pointer_traits_difference_type
    {
        typedef ptrdiff_t type;
    };

    template<class Ptr>
    struct _pointer_traits_difference_type<Ptr, true>
    {
        typedef typename Ptr::difference_type type;
    };

//    conditional
    template<bool B, class If, class Then>
    struct conditioinal {typedef If type;};

    template<class If, class Then>
    struct conditioinal<false, If, Then> {typedef Then type;};

//    _is_void
    template <class _Tp> struct _is_void       : public false_type {};
    template <>          struct _is_void<void> : public true_type {};

//    is_void
    template<class T>
    struct is_void: public _is_void<typename remove_cv<T>::type> {};

//    _has_rebind
    template<class T, class U>
    struct _has_rebind
    {
    private:
        struct _two {char _lx; char _lxx;};

        template<class X>
        static _two _test(...);

        template<class X>
        static char _test(typename X::template rebind<U>* = 0);
    public:
        static const bool value = sizeof(_test<T>(0)) == 1;
    };

//    pointer_traits_rebind
    template<class T, class U, bool = _has_rebind<T, U>::value>
    struct _pointer_traits_rebind
    {
        typedef typename T::template rebind<U>::other type;
    };

//    pointer_traits
    template<class Ptr>
    struct pointer_traits
    {
        typedef Ptr pointer;
        typedef typename _pointer_element_type<pointer>::type element_type;
        typedef typename _pointer_traits_difference_type<pointer>::type difference_type;

        template <class U>
        struct rebind
        {
            typedef typename _pointer_traits_rebind<pointer, U>::type other;
        };

    private:
        struct _nat{};
    public:
        static pointer pointer_to(typename conditional<is_void<element_type>::value,
                __nat, element_type>::type& r)
        {return pointer::pointer_to(r);}
    };

    template<class T>
    struct pointer_traits<T*>
    {
        typedef T* pointer;
        typedef T element_type;
        typedef ptrdiff_t difference_type;

        template <class U>
        struct rebind
        {
            typedef U* other;
        };

    private:
        struct _nat{};
    public:
        static pointer pointer_to(typename conditioinal<is_void<element_type>::value, _nat, element_type>::type& r)
        {
            return addressof(r);
        }
    };

//    addressof
    template<class T>
    typename enable_if<is_object<T>::value, T*>::type addressof(T& arg)
    {
        return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
    }

//    _rebind_pointer
    template<class From, class To>
    struct _rebind_pointer
    {
            typedef typename pointer_traits<From>::template rebind<To>::other  type;
    };
}

#endif
