/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:09:40 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/14 23:03:48 by hcharlsi         ###   ########.fr       */
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

//  vector default constructor
    ft::vector<int> ft_v;
//    vector fill constructor
    ft::vector<int> fill_v(4, 45);
//    push_back
    fill_v.push_back(1);
    std::cout << "\npushback fill_v: " << fill_v.back() << '\n';
//    size
    std::cout << "fill_v size: " << fill_v.size() << '\n';

//    max_size
    std::cout << "max size my vector: " << fill_v.max_size() << '\n';

//    ft::vector<int> ft_range_v(it1, it2);

//    vector copy constructor
    ft::vector<int> copy_v(fill_v);

    for(int i = 0; i < 4; ++i)
        std::cout << copy_v[i] << '\n';
    std::cout << '\n';

    ft::vector<int> ft_v2(2, 20);

    ft_v2.push_back(11);
    for (int i = 0; i < 3; i++)
        std::cout << ft_v2[i] << '\n';
    std::cout << '\n';
//    operator=
    copy_v = ft_v2;
//    operator[]
    for (int i = 0; i < 3; i++)
    {
        std::cout << "element copy_v[" << i << "]: " << copy_v[i] << '\n';
        std::cout << "element ft_v2[" << i << "]: " << ft_v2[i] << '\n';
        std::cout << '\n';
    }

//    at
    std::cout << "at copy_v[2]: " << copy_v.at(2) << '\n';

//    front
    std::cout << "first element copy_v: " << copy_v.front() << '\n';

//    back
    std::cout << "last element copy_v: " << copy_v.back() << '\n';

//    begin
    std::cout << "\nempty_v begin: " << *copy_v.begin() << '\n';

//    end
    std::cout << "\nend iterator vector: " << *copy_v.end() << '\n';

//    range constructor
    ft::vector<int> range_v(copy_v.begin(), copy_v.end());
    std::cout << "range vector[0]: " << range_v[0] << '\n';

//    capacity
    std::cout << "\ncapacity copy_v: " << copy_v.capacity() << '\n';

//    reserve
    std::cout << "\nsize copy_v until reserve: " << copy_v.size() << '\n';
    std::cout << "capacity copy_v until reserve: " << copy_v.capacity() << '\n';
    copy_v.reserve(6);
    std::cout << "\nsize copy_v after reserve: " << copy_v.size() << '\n';
    std::cout << "capacity copy_v after reserve: " << copy_v.capacity() << '\n';

//    resize
    {
        ft::vector<int> myvector;

        // set some initial content:
        for (int i=1;i<10;i++) myvector.push_back(i);

        myvector.resize(5);
        myvector.resize(8,100);
        myvector.resize(12);

        std::cout << "myvector contains:";
        for (int i=0;i< static_cast<int>(myvector.size());i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

//    empty
    ft::vector<int> empty_v;

    std::cout << "\nempty empty_v: " << empty_v.empty() << '\n';
    std::cout << "empty copy_v: " << copy_v.empty() << '\n';

//    clear
    {
        ft::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        std::cout << "\nmyvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

//    assign
    {
        ft::vector<int> first;
        ft::vector<int> second;
        ft::vector<int> third;

        first.assign (7,100);             // 7 ints with a value of 100

        ft::vector<int>::iterator it;
        it=first.begin()+1;

        second.assign (it,first.end()-1); // the 5 central values of first

        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);   // assigning from array.

        std::cout << "\nSize of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
        std::cout << "Size of third: " << int (third.size()) << '\n';
    }

//    reverse iterators
    {
        ft::vector<int> myvector (5);  // 5 default-constructed ints

        ft::vector<int>::reverse_iterator rit = myvector.rbegin();

        int i=0;
        for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
            *rit = ++i;

        std::cout << "\nmyvector contains:";
        for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

//    pop_back
    {
        ft::vector<int> myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        while (!myvector.empty())
        {
            sum+=myvector.back();
            myvector.pop_back();
        }

        std::cout << "\nThe elements of myvector add up to " << sum << '\n';
        std::cout << "size myvector: " << myvector.size() << '\n';
    }

//    insert
    {
        ft::vector<int> myvector (3,100);
        ft::vector<int>::iterator it;

        it = myvector.begin();
        it = myvector.insert ( it , 200 );

        myvector.insert (it,2,300);

        // "it" no longer valid, get a new one:
        it = myvector.begin();
//
        ft::vector<int> anothervector (2,400);
        myvector.insert (it+2,anothervector.begin(),anothervector.end());

        int myarray [] = { 501,502,503 };
        myvector.insert (myvector.begin(), myarray, myarray+3);

        std::cout << "\nmyvector contains:";
        for (it=myvector.begin(); it<myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    return 0;
}
