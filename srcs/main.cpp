/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:09:40 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/05 19:06:46 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <iostream>
//#include <string>
//#include <deque>
//#if 1 //CREATE A REAL STL EXAMPLE
//	#include <map>
//	#include <stack>
//	#include <vector>
//	namespace ft = std;
//#else
//	#include <map.hpp>
//	#include <stack.hpp>
//	#include <vector.hpp>
//#endif
//
//#include <stdlib.h>
//
//#define MAX_RAM 4294967296
//#define BUFFER_SIZE 4096
//struct Buffer
//{
//	int idx;
//	char buff[BUFFER_SIZE];
//};
//
//
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))
//
//template<typename T>
//class MutantStack : public ft::stack<T>
//{
//public:
//	MutantStack() {}
//	MutantStack(const MutantStack<T>& src) { *this = src; }
//	MutantStack<T>& operator=(const MutantStack<T>& rhs)
//	{
//		this->c = rhs.c;
//		return *this;
//	}
//	~MutantStack() {}
//
//	typedef typename ft::stack<T>::container_type::iterator iterator;
//
//	iterator begin() { return this->c.begin(); }
//	iterator end() { return this->c.end(); }
//};
//
//int main(int argc, char** argv) {
//	if (argc != 2)
//	{
//		std::cerr << "Usage: ./test seed" << std::endl;
//		std::cerr << "Provide a seed please" << std::endl;
//		std::cerr << "Count value:" << COUNT << std::endl;
//		return 1;
//	}
//	const int seed = atoi(argv[1]);
//	srand(seed);
//
//	ft::vector<std::string> vector_str;
//	ft::vector<int> vector_int;
//	ft::stack<int> stack_int;
//	ft::vector<Buffer> vector_buffer;
//	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
//	ft::map<int, int> map_int;
//
//	for (int i = 0; i < COUNT; i++)
//	{
//		vector_buffer.push_back(Buffer());
//	}
//
//	for (int i = 0; i < COUNT; i++)
//	{
//		const int idx = rand() % COUNT;
//		vector_buffer[idx].idx = 5;
//	}
//	ft::vector<Buffer>().swap(vector_buffer);
//
//	try
//	{
//		for (int i = 0; i < COUNT; i++)
//		{
//			const int idx = rand() % COUNT;
//			vector_buffer.at(idx);
//			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
//		}
//	}
//	catch(const std::exception& e)
//	{
//		//NORMAL ! :P
//	}
//
//	for (int i = 0; i < COUNT; ++i)
//	{
//		map_int.insert(ft::make_pair(rand(), rand()));
//	}
//
//	int sum = 0;
//	for (int i = 0; i < 10000; i++)
//	{
//		int access = rand();
//		sum += map_int[access];
//	}
//	std::cout << "should be constant with the same seed: " << sum << std::endl;
//
//	{
//		ft::map<int, int> copy = map_int;
//	}
//	MutantStack<char> iterable_stack;
//	for (char letter = 'a'; letter <= 'z'; letter++)
//		iterable_stack.push(letter);
//	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
//	{
//		std::cout << *it;
//	}
//	std::cout << std::endl;
//	return (0);
//}

//reverse_iterator test

#include "../includes/ft_containers.hpp"
#include <vector>

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

bool mypredicate (int i, int j) {
	return (i==j);
}

int main() {
	std::vector<int> a2(4);
	a2.push_back(0);
	a2.push_back(1);
	a2.push_back(2);
	a2.push_back(3);

	std::vector<int> a3(3);
	a3.push_back(40);
	a3.push_back(41);
	a3.push_back(42);

	ft::reverse_iterator<std::vector<int>::reverse_iterator> it1(a2.rend());
	std::cout << "it1 = " << *it1 << '\n';
	std::cout << "a2.rend = " << *(a2.rend()) << '\n';
	it1 = ft::reverse_iterator<std::vector<int>::reverse_iterator>(a2.rbegin());
	std::cout << "it1 = " << *it1 << '\n';
	std::cout << "a2.rbegin = " << *(a2.rbegin()) << '\n';
	ft::reverse_iterator<std::vector<int>::reverse_iterator> it2;
	ft::reverse_iterator<std::vector<int>::reverse_iterator> it3(a3.rbegin());
	it2 = it3;
	std::cout << "it2 = " << *it2 << '\n';
	std::cout << "a3.rbegin = " << *(a3.rbegin()) << '\n';

	std::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	ft::reverse_iterator<std::vector<int>::reverse_iterator> ri1(v.rbegin()),
			ri2(v.rend());
	std::cout << (ri2 - ri1) << ' ';
	std::cout << (ri1 - ri2) << '\n';

	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;

	if (ft::is_integral<int>() )
		std::cout << "int is an integral type" << std::endl;

	// same result as:
	if ( ft::is_integral<int>::value)
		std::cout << "int is an integral type" << std::endl;
//	lexicographical_compare
	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << "\n\n";

//	equal
	int myints[] = {20,40,60,80,100};
	std::vector<int>myvector (myints,myints+5);

	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;

	if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n\n";

//	pair constructors
	ft::pair <std::string,double> product1;                     // default
	// constructor
	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> product3 (product2);          // copy
	// constructor

	product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using
	// make_pair (move)

	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

//	make_pair
	ft::pair<int,int> f;
	ft::pair<int,int> b;

	f = ft::make_pair (10,20);
	b = ft::make_pair (10.5,'A'); // ok: implicit conversion from
	// pair<double,char>

	std::cout << "foo: " << f.first << ", " << f.second << '\n';
	std::cout << "bar: " << b.first << ", " << b.second << '\n';
	return 0;
}
