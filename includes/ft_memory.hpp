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
# include "ft_utility.hpp"
# include "ft_nullptr.hpp"

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

    template <class _Tp, class = void>
    struct __has_pointer_type : false_type {};

    template <class _Tp>
    struct __has_pointer_type<_Tp,
            typename __void_t<typename _Tp::pointer>::type> : true_type {};

    namespace __pointer_type_imp
    {

        template <class _Tp, class _Dp, bool = __has_pointer_type<_Dp>::value>
        struct __pointer_type
        {
            typedef typename _Dp::pointer type;
        };

        template <class _Tp, class _Dp>
        struct __pointer_type<_Tp, _Dp, false>
        {
            typedef _Tp* type;
        };

    }  // __pointer_type_imp

    template <class _Tp, class _Dp>
    struct __pointer_type
    {
        typedef typename __pointer_type_imp::__pointer_type<_Tp, typename remove_reference<_Dp>::type>::type type;
    };

//    conditional
    template<bool B, class If, class Then>
    struct conditional {typedef If type;};

    template<class If, class Then>
    struct conditional<false, If, Then> {typedef Then type;};

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
                _nat, element_type>::type& r)
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
        static pointer pointer_to(typename conditional<is_void<element_type>::value, _nat, element_type>::type& r)
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

//    default_delete
    template <class T>
    struct default_delete
    {
        inline default_delete() = default;
    };

//    unique_ptr
    template <class T, class Dp = default_delete<T> >
    class unique_ptr
    {
    public:
        typedef T element_type;
        typedef Dp deleter_type;
        typedef typename __pointer_type<T, deleter_type>::type pointer;

    private:
        pair<pointer, deleter_type> _ptr;
        struct _nat {int _for_bool;};
    private:
        unique_ptr(unique_ptr&);
        template <class U, class E> unique_ptr(unique_ptr<U, E>&);
        unique_ptr& operator=(unique_ptr&);
        template <class U, class E> unique_ptr& operator=(unique_ptr<U, E>&);
    public:
        unique_ptr(): _ptr(pointer()) {}
        unique_ptr(nullptr_t): _ptr(pointer()) {}
        explicit unique_ptr(pointer p): _ptr(p) {}
        operator _rv<unique_ptr>()
        {
            return _rv<unique_ptr>(*this);
        }
        unique_ptr(_rv<unique_ptr> u): _ptr(u->release(), forward<deleter_type>(u->get_deleter())) {}

        template <class U, class E>
        E& operator=(unique_ptr<U, E> u)
        {
            reset(u.release());
            _ptr.second() = forward<E>(u.get_deleter());
            return *this;
        }

        unique_ptr(pointer p, deleter_type d): _ptr(move(p), move(d)) {}
        ~unique_ptr() { reset(); }
        unique_ptr& operator=(nullptr_t)
        {
            reset();
            return *this;
        }
        typename add_lvalue_reference<T>::type
        operator*() const
        {
            return *_ptr.first();
        }

        pointer operator->() const
        {
            return _ptr.first();
        }

        pointer get() const
        {
            return _ptr.first();
        }

        deleter_type& get_deleter()
        {
            return _ptr.second();
        }

        const deleter_type& get_deleter() const
        {
            return _ptr.second();
        }

        operator bool() const
        {
            return _ptr.first() != nullptr;
        }

        pointer release()
        {
            pointer __t = _ptr.first();
            _ptr.first() = pointer();
            return __t;
        }

        void reset(pointer __p = pointer())
        {
            pointer __tmp = _ptr.first();
            _ptr.first() = __p;
            if (__tmp)
                _ptr.second()(__tmp);
        }

        void swap(unique_ptr& __u)
        {
            _ptr.swap(__u._ptr);
        }
    };

    template <class _Tp, class _Dp>
    class unique_ptr<_Tp[], _Dp> {
    public:
        typedef _Tp element_type;
        typedef _Dp deleter_type;
        typedef typename __pointer_type<_Tp, deleter_type>::type pointer;

    private:
        pair<pointer, deleter_type> __ptr_;

        template <class _From>
        struct _CheckArrayPointerConversion : is_same<_From, pointer> {};

        template <class _FromElem>
        struct _CheckArrayPointerConversion<_FromElem*>
                : integral_constant<bool,
                        is_same<_FromElem*, pointer>::value ||
                        (is_same<pointer, element_type*>::value)
                >
        {};
    private:
        template <class _Up> explicit unique_ptr(_Up);

        unique_ptr(unique_ptr&);
        template <class _Up> unique_ptr(unique_ptr<_Up>&);

        unique_ptr& operator=(unique_ptr&);
        template <class _Up> unique_ptr& operator=(unique_ptr<_Up>&);
    public:
        unique_ptr() : __ptr_(pointer()) {}
        unique_ptr(nullptr_t) : __ptr_(pointer()) {}
        explicit unique_ptr(pointer __p) : __ptr_(__p) {}

        unique_ptr(pointer __p, deleter_type __d)
                : __ptr_(__p, forward<deleter_type>(__d)) {}

        unique_ptr(nullptr_t, deleter_type __d)
                : __ptr_(pointer(), forward<deleter_type>(__d)) {}

        operator _rv<unique_ptr>() {
            return _rv<unique_ptr>(*this);
        }

        unique_ptr(_rv<unique_ptr> __u)
                : __ptr_(__u->release(),
                         forward<deleter_type>(__u->get_deleter())) {}

        unique_ptr& operator=(_rv<unique_ptr> __u) {
            reset(__u->release());
            __ptr_.second() = forward<deleter_type>(__u->get_deleter());
            return *this;
        }
    public:
        ~unique_ptr() { reset(); }
        unique_ptr& operator=(nullptr_t)
        {
            reset();
            return *this;
        }

        typename add_lvalue_reference<_Tp>::type
        operator[](size_t __i) const {
            return __ptr_.first()[__i];
        }

        pointer get() const  {
            return __ptr_.first();
        }


        deleter_type& get_deleter()  {
            return __ptr_.second();
        }

        const deleter_type& get_deleter() const  {
            return __ptr_.second();
        }

        operator bool() const
        {
            return __ptr_.first() != nullptr;
        }

        pointer release()
        {
            pointer __t = __ptr_.first();
            __ptr_.first() = pointer();
            return __t;
        }

        template <class _Pp>
        typename enable_if<
                _CheckArrayPointerConversion<_Pp>::value
        >::type
        reset(_Pp __p)
        {
            pointer __tmp = __ptr_.first();
            __ptr_.first() = __p;
            if (__tmp)
                __ptr_.second()(__tmp);
        }

        void reset(nullptr_t = nullptr)
        {
            pointer __tmp = __ptr_.first();
            __ptr_.first() = nullptr;
            if (__tmp)
                __ptr_.second()(__tmp);
        }

        void swap(unique_ptr& __u)
        {
            __ptr_.swap(__u.__ptr_);
        }

    };

}

#endif
