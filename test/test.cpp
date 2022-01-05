/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:15:28 by hcharlsi          #+#    #+#             */
/*   Updated: 2022/01/06 02:37:50 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include "../includes/ft_memory.hpp"
#include "../includes/ft_tree.hpp"
#include "__tree"

int main()
{
	typedef std::less<int> compare;
	typedef std::allocator<int> allocator;

	std::less<int> cmp;
	std::allocator<int> alloc;
	ft::_tree<int, compare, allocator> t(cmp, alloc);
	t.insert(3);
	t.insert(1);
	t.insert(2);

	ft::_tree<int, compare, allocator>::iterator it(t.begin());
	std::cout << *it << std::endl;
	std::cout << *(++it) << std::endl;
	std::cout << *(++it) << std::endl;


//	std::__tree<int, compare, allocator> t1(cmp, alloc);
//	t1.__insert_unique(3);
//	t1.__insert_unique(1);
////	t.insert(2);
//
//	std::__tree<int, compare, allocator>::iterator it1(t1.begin());
//	std::cout << *it1 << std::endl;
//	std::cout << *(--it1) << std::endl;
}
