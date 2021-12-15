/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nullptr.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:26:52 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/12/08 13:26:54 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_FT_NULLPTR_HPP
#define FT_CONTAINERS_FT_NULLPTR_HPP

namespace ft
{
    struct nullptr_t
    {
        void *_lx;

        struct _nat {int _for_bool;};

        nullptr_t(): _lx(0) {}
        nullptr_t(int _nat::*): _lx(0) {}

        operator int _nat::*() const {return 0;}

        template <class T>
        operator T* () const {return 0;}

        template <class T, class U>
        operator T U::* () const {return 0;}

        friend bool operator==(nullptr_t, nullptr_t) {return true;}
        friend bool operator!=(nullptr_t, nullptr_t) {return false;}
    };

    inline nullptr_t _get_nullptr_t() {return nullptr_t(0);}

#define nullptr _get_nullptr_t()
}

#endif
