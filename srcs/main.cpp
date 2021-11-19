/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:09:40 by hcharlsi          #+#    #+#             */
/*   Updated: 2021/11/19 21:40:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_containers.hpp"
#include <vector>
#include <ctime>

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

bool mypredicate (int i, int j) {
	return (i==j);
}

int main() {
    unsigned int start = clock();
//    ft::vector<int> *vec = new ft::vector<int>;
//    for (int i = 0; i < 1000000; ++i) {
//        vec->push_back(i);
//    }
//    vec->erase(vec->begin(), vec->end());
//    delete vec;
	ft::vector<int> a2;
	a2.push_back(0);
	a2.push_back(1);
	a2.push_back(2);
	a2.push_back(3);

	ft::vector<int> a3(3);
	a3.push_back(40);
	a3.push_back(41);
	a3.push_back(42);

	ft::reverse_iterator<ft::vector<int>::reverse_iterator> it1(a2.rend());
	std::cout << "it1 = " << *it1 << '\n';
	std::cout << "a2.rend = " << *a2.rend() << '\n';
	it1 = ft::reverse_iterator<ft::vector<int>::reverse_iterator>(a2.rbegin());
	std::cout << "it1 = " << *it1 << '\n';
	std::cout << "a2.rbegin = " << *(a2.rbegin()) << '\n';
	ft::reverse_iterator<ft::vector<int>::reverse_iterator> it2;
	ft::reverse_iterator<ft::vector<int>::reverse_iterator> it3(a3.rbegin());
	it2 = it3;
	std::cout << "it2 = " << *it2 << '\n';
	std::cout << "a3.rbegin = " << *(a3.rbegin()) << '\n';

	ft::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	ft::reverse_iterator<ft::vector<int>::reverse_iterator> ri1(v.rbegin()),
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
//       clear
    {
        ft::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        std::cout << "\nmyvector capacity: " << myvector.capacity() << '\n';
        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);
        std::cout << "myvector capacity: " << myvector.capacity() << '\n';
        std::cout << "myvector contains: ";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

//    erase
    {
        ft::vector<int> myvector;

        // set some values (from 1 to 10)
        for (int i=1; i<=10; i++) myvector.push_back(i);

        // erase the 6th element
        myvector.erase (myvector.begin()+5);

        // erase the first 3 elements:
        myvector.erase (myvector.begin(),myvector.begin()+3);

        std::cout << "\nmyvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

//    swap
    {
        ft::vector<int> foo (3,100);   // three ints with a value of 100
        ft::vector<int> bar (5,200);   // five ints with a value of 200

        foo.swap(bar);

        std::cout << "\nfoo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
    }

//    get_allocator
    {
        ft::vector<int> myvector;
        int * p;
        unsigned int i;

        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);

        // construct values in-place on the array:
        for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

        std::cout << "\nThe allocated array contains:";
        for (i=0; i<5; i++) std::cout << ' ' << p[i];
        std::cout << '\n';

        // destroy and deallocate:
        for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p,5);
    }

//    operator ==,!=,<,<=,>,>=
    {
        ft::vector<int> alice;
        alice.push_back(1);
        alice.push_back(2);
        alice.push_back(3);
        ft::vector<int> bob;
        bob.push_back(7);
        bob.push_back(8);
        bob.push_back(9);
        bob.push_back(10);
        ft::vector<int> eve;
        eve.push_back(1);
        eve.push_back(2);
        eve.push_back(3);

        std::cout << std::boolalpha;

        // Compare non equal containers
        std::cout << "\nalice == bob returns " << (alice == bob) << '\n';
        std::cout << "alice != bob returns " << (alice != bob) << '\n';
        std::cout << "alice <  bob returns " << (alice < bob) << '\n';
        std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
        std::cout << "alice >  bob returns " << (alice > bob) << '\n';
        std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

        std::cout << '\n';

        // Compare equal containers
        std::cout << "alice == eve returns " << (alice == eve) << '\n';
        std::cout << "alice != eve returns " << (alice != eve) << '\n';
        std::cout << "alice <  eve returns " << (alice < eve) << '\n';
        std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
        std::cout << "alice >  eve returns " << (alice > eve) << '\n';
        std::cout << "alice >= eve returns " << (alice >= eve) << '\n';
    }

//    swap non-member function
    {
        ft::vector<int> alice;
        alice.push_back(1);
        alice.push_back(2);
        alice.push_back(3);
        ft::vector<int> bob;
        bob.push_back(7);
        bob.push_back(8);
        bob.push_back(9);
        bob.push_back(10);

        // Print state before swap
        std::cout << "\nalice: ";
        for(ft::vector<int>::iterator it = alice.begin(); it != alice.end(); ++it)
            std::cout << *it << " ";
        std::cout << "\n" "bob  : ";
        for(ft::vector<int>::iterator it = bob.begin(); it != bob.end(); ++it)
            std::cout << *it << " ";
        std::cout << '\n';

        std::cout << "-- SWAP\n";
        std::swap(alice, bob);

        // Print state after swap
        std::cout << "alice: ";
        for(ft::vector<int>::iterator it = alice.begin(); it != alice.end(); ++it)
            std::cout << *it << " ";
        std::cout << "\n" "bob  : ";
        for(ft::vector<int>::iterator it = bob.begin(); it != bob.end(); ++it)
            std::cout << *it << " ";
        std::cout << '\n';
    }

    std::input

    unsigned int end = clock();
    std::cout << end - start << '\n';
    return 0;
}
