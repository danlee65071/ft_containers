/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:15:28 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/10/13 16:47:10 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_containers.hpp"
#include <vector>

int main() {
	std::vector<int> a1(3);
	a1.push_back(0);
	a1.push_back(1);
	a1.push_back(2);

//	std::vector<int> a2(4);
//	a2.push_back(0);
//	a2.push_back(1);
//	a2.push_back(2);
//	a2.push_back(3);
//
//	std::vector<int> a3(3);
//	a3.push_back(40);
//	a3.push_back(41);
//	a3.push_back(42);

	ft::reverse_iterator<std::vector<int>::reverse_iterator> it1(a1.rbegin());
	std::cout << *it1 << '\n';
//	it1 = ft::reverse_iterator<std::vector<int>::reverse_iterator>(a2.rbegin());
//	std::cout << *it1 << '\n';
//	ft::reverse_iterator<std::vector<int>::reverse_iterator> it2;
//	it2 = a3.rbegin();
//	std::cout << *it2 << '\n';

}