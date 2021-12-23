/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:15:28 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/27 20:31:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include "../includes/ft_memory.hpp"
#include "../includes/ft_tree.hpp"

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
//	std::cout << *(++it) << std::endl;
//	std::cout << *(++it) << std::endl;
}