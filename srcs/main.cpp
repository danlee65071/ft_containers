/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:09:40 by hcharlsi          #+#    #+#             */
/*   Updated: 2022/01/06 02:37:50 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_containers.hpp"
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <ctime>

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

bool mypredicate (int i, int j) {
	return (i==j);
}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
    bool operator() (const char& lhs, const char& rhs) const
    {return lhs<rhs;}
};

bool fncomp (int lhs, int rhs) {return lhs<rhs;}
struct classcomp_char {
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

int main() {
    unsigned int start_ft = clock();

	std::cout << "ft\n";
	{
		{
			ft::vector<int> *vec = new ft::vector<int>;
			for (int i = 0; i < 1000000; ++i)
			{
				vec->push_back(i);
			}
			vec->erase(vec->begin(), vec->end());
			delete vec;
		}
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

		if (ft::is_integral<int>())
			std::cout << "int is an integral type" << std::endl;

		// same result as:
		if (ft::is_integral<int>::value)
			std::cout << "int is an integral type" << std::endl;
//	lexicographical_compare
		char foo[] = "Apple";
		char bar[] = "apartment";

		std::cout << std::boolalpha;

		std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

		std::cout << "Using default comparison (operator<): ";
		std::cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9);
		std::cout << '\n';

		std::cout << "Using mycomp as comparison object: ";
		std::cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
		std::cout << "\n\n";

//	equal
		int myints[] = {20, 40, 60, 80, 100};
		std::vector<int> myvector(myints, myints + 5);

		if (ft::equal(myvector.begin(), myvector.end(), myints))
			std::cout << "The contents of both sequences are equal.\n";
		else
			std::cout << "The contents of both sequences differ.\n";

		myvector[3] = 81;

		if (ft::equal(myvector.begin(), myvector.end(), myints, mypredicate))
			std::cout << "The contents of both sequences are equal.\n";
		else
			std::cout << "The contents of both sequences differ.\n\n";

//	pair constructors
		ft::pair<std::string, double> product1;                     // default
		// constructor
		ft::pair<std::string, double> product2("tomatoes", 2.30);   // value init
		ft::pair<std::string, double> product3(product2);          // copy
		// constructor

		product1 = ft::make_pair(std::string("lightbulbs"), 0.99);   // using
		// make_pair (move)

		product2.first = "shoes";                  // the type of first is string
		product2.second = 39.90;                   // the type of second is double

		std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
		std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
		std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

//	make_pair
		ft::pair<int, int> f;
		ft::pair<int, int> b;

		f = ft::make_pair(10, 20);
		b = ft::make_pair(10.5, 'A'); // ok: implicit conversion from
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

		for (int i = 0; i < 4; ++i)
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
			for (int i = 1; i < 10; i++) myvector.push_back(i);

			myvector.resize(5);
			myvector.resize(8, 100);
			myvector.resize(12);

			std::cout << "myvector contains:";
			for (int i = 0; i < static_cast<int>(myvector.size()); i++)
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
			myvector.push_back(100);
			myvector.push_back(200);
			myvector.push_back(300);

			std::cout << "\nmyvector contains:";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';

			myvector.clear();
			myvector.push_back(1101);
			myvector.push_back(2202);

			std::cout << "myvector contains:";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    assign
		{
			ft::vector<int> first;
			ft::vector<int> second;
			ft::vector<int> third;

			first.assign(7, 100);             // 7 ints with a value of 100

			ft::vector<int>::iterator it;
			it = first.begin() + 1;

			second.assign(it, first.end() - 1); // the 5 central values of first

			int myints[] = {1776, 7, 4};
			third.assign(myints, myints + 3);   // assigning from array.

			std::cout << "\nSize of first: " << int(first.size()) << '\n';
			std::cout << "Size of second: " << int(second.size()) << '\n';
			std::cout << "Size of third: " << int(third.size()) << '\n';
		}

//    reverse iterators
		{
			ft::vector<int> myvector(5);  // 5 default-constructed ints

			ft::vector<int>::reverse_iterator rit = myvector.rbegin();

			int i = 0;
			for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
				*rit = ++i;

			std::cout << "\nmyvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}

//    pop_back
		{
			ft::vector<int> myvector;
			int sum(0);
			myvector.push_back(100);
			myvector.push_back(200);
			myvector.push_back(300);

			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}

			std::cout << "\nThe elements of myvector add up to " << sum << '\n';
			std::cout << "size myvector: " << myvector.size() << '\n';
		}

//    insert
		{
			ft::vector<int> myvector(3, 100);
			ft::vector<int>::iterator it;

			it = myvector.begin();
			it = myvector.insert(it, 200);

			myvector.insert(it, 2, 300);

			// "it" no longer valid, get a new one:
			it = myvector.begin();
//
			ft::vector<int> anothervector(2, 400);
			myvector.insert(it + 2, anothervector.begin(), anothervector.end());

			int myarray[] = {501, 502, 503};
			myvector.insert(myvector.begin(), myarray, myarray + 3);

			std::cout << "\nmyvector contains:";
			for (it = myvector.begin(); it < myvector.end(); it++)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
//       clear
		{
			ft::vector<int> myvector;
			myvector.push_back(100);
			myvector.push_back(200);
			myvector.push_back(300);

			std::cout << "\nmyvector capacity: " << myvector.capacity() << '\n';
			std::cout << "myvector contains:";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';

			myvector.clear();
			myvector.push_back(1101);
			myvector.push_back(2202);
			std::cout << "myvector capacity: " << myvector.capacity() << '\n';
			std::cout << "myvector contains: ";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    erase
		{
			ft::vector<int> myvector;

			// set some values (from 1 to 10)
			for (int i = 1; i <= 10; i++) myvector.push_back(i);

			// erase the 6th element
			myvector.erase(myvector.begin() + 5);

			// erase the first 3 elements:
			myvector.erase(myvector.begin(), myvector.begin() + 3);

			std::cout << "\nmyvector contains:";
			for (unsigned i = 0; i < myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    swap
		{
			ft::vector<int> foo(3, 100);   // three ints with a value of 100
			ft::vector<int> bar(5, 200);   // five ints with a value of 200

			foo.swap(bar);

			std::cout << "\nfoo contains:";
			for (unsigned i = 0; i < foo.size(); i++)
				std::cout << ' ' << foo[i];
			std::cout << '\n';

			std::cout << "bar contains:";
			for (unsigned i = 0; i < bar.size(); i++)
				std::cout << ' ' << bar[i];
			std::cout << '\n';
		}

//    get_allocator
		{
			ft::vector<int> myvector;
			int *p;
			unsigned int i;

			// allocate an array with space for 5 elements using vector's allocator:
			p = myvector.get_allocator().allocate(5);

			// construct values in-place on the array:
			for (i = 0; i < 5; i++) myvector.get_allocator().construct(&p[i], i);

			std::cout << "\nThe allocated array contains:";
			for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
			std::cout << '\n';

			// destroy and deallocate:
			for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
			myvector.get_allocator().deallocate(p, 5);
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
			for (ft::vector<int>::iterator it = alice.begin(); it != alice.end(); ++it)
				std::cout << *it << " ";
			std::cout << "\n" "bob  : ";
			for (ft::vector<int>::iterator it = bob.begin(); it != bob.end(); ++it)
				std::cout << *it << " ";
			std::cout << '\n';

			std::cout << "-- SWAP\n";
			std::swap(alice, bob);

			// Print state after swap
			std::cout << "alice: ";
			for (ft::vector<int>::iterator it = alice.begin(); it != alice.end(); ++it)
				std::cout << *it << " ";
			std::cout << "\n" "bob  : ";
			for (ft::vector<int>::iterator it = bob.begin(); it != bob.end(); ++it)
				std::cout << *it << " ";
			std::cout << '\n';
		}

		{
			ft::vector<int> my_vector;
			for (int i = 0; i < 10; i++) my_vector.push_back(i * 10);

			ft::vector<int>::iterator it = my_vector.begin();

			ft::advance(it, 5);

			std::cout << "\niterator advance:\nThe sixth element in mylist is: " << *it << '\n';
		}

		{
			ft::vector<int> mylist;
			for (int i = 0; i < 10; i++) mylist.push_back(i * 10);

			ft::vector<int>::iterator first = mylist.begin();
			ft::vector<int>::iterator last = mylist.end();

			std::cout << "\ndistance:\nThe distance is: " << ft::distance(first, last) << '\n';
		}


		std::cout << "map\n\n";
		{
			ft::map<char, int> first;

			first['a'] = 10;
			first['b'] = 30;
			first['c'] = 50;
			first['d'] = 70;

			ft::map<char, int> second(first.begin(), first.end());

//       ft::map<char,int> third (second);

			ft::map<char, int, classcomp> fourth;                 // class as Compare

			bool (*fn_pt)(char, char) = fncomp;
			ft::map<char, int, bool (*)(char, char)> fifth(fn_pt);
		}
		{
			ft::map<char, int> first;
			ft::map<char, int> second;

			first['x'] = 8;
			first['y'] = 16;
			first['z'] = 32;

			second = first;                // second now contains 3 ints
			first = ft::map<char, int>();  // and first is now empty

			std::cout << "Size of first: " << first.size() << '\n';
			std::cout << "Size of second: " << second.size() << '\n';
		}
		{
			ft::map<char, int> mymap;

			mymap['b'] = 100;
			mymap['a'] = 200;
			mymap['c'] = 300;

			// show content:
			for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

		}
		{
			ft::map<char, int> mymap;

			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;

			// show content:
			ft::map<char, int>::reverse_iterator rit;
			for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << '\n';

		}
		{
			ft::map<char, int> mymap;

			mymap['a'] = 10;
			mymap['b'] = 20;
			mymap['c'] = 30;

			while (!mymap.empty())
			{
				std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
				mymap.erase(mymap.begin());
			}
		}

		{
			ft::map<char, int> mymap;
			mymap['a'] = 101;
			mymap['b'] = 202;
			mymap['c'] = 302;

			std::cout << "mymap.size() is " << mymap.size() << '\n';

		}
		{
			int i;
			ft::map<int, int> mymap;

			if (mymap.max_size() > 1000)
			{
				for (i = 0; i < 1000; i++) mymap[i] = 0;
				std::cout << "The map contains 1000 elements.\n";
			} else std::cout << "The map could not hold 1000 elements.\n";

		}
		{
			ft::map<char, std::string> mymap;

			mymap['a'] = "an element";
			mymap['b'] = "another element";
			mymap['c'] = mymap['b'];

			std::cout << "mymap['a'] is " << mymap['a'] << '\n';
			std::cout << "mymap['b'] is " << mymap['b'] << '\n';
			std::cout << "mymap['c'] is " << mymap['c'] << '\n';
			std::cout << "mymap['d'] is " << mymap['d'] << '\n';

			std::cout << "mymap now contains " << mymap.size() << " elements.\n";

		}

		{
			ft::map<char, int> mymap;

			// first insert function version (single parameter):
			mymap.insert(ft::pair<char, int>('a', 100));
			mymap.insert(ft::pair<char, int>('z', 200));

			ft::pair<ft::map<char, int>::iterator, bool> ret;
			ret = mymap.insert(ft::pair<char, int>('z', 500));
			if (ret.second == false)
			{
				std::cout << "element 'z' already existed";
				std::cout << " with a value of " << ret.first->second << '\n';
			}

			// second insert function version (with hint position):
			ft::map<char, int>::iterator it = mymap.begin();
			mymap.insert(it, ft::pair<char, int>('b', 300));  // max efficiency inserting
			mymap.insert(it, ft::pair<char, int>('c', 400));  // no max efficiency inserting

			// third insert function version (range insertion):
			ft::map<char, int> anothermap;
			anothermap.insert(mymap.begin(), mymap.find('c'));

			// showing contents:
			std::cout << "mymap contains:\n";
			for (it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "anothermap contains:\n";
			for (it = anothermap.begin(); it != anothermap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}

		{
			ft::map<char, int> mymap;
			ft::map<char, int>::iterator it;

			// insert some values:
			mymap['a'] = 10;
			mymap['b'] = 20;
			mymap['c'] = 30;
			mymap['d'] = 40;
			mymap['e'] = 50;
			mymap['f'] = 60;

			it = mymap.find('b');
			mymap.erase(it);                   // erasing by iterator

			mymap.erase('c');                  // erasing by key

			it = mymap.find('e');

			mymap.erase(it, mymap.end());    // erasing by range
			// show content:
			for (it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		{
			ft::map<char, int> foo, bar;

			foo['x'] = 100;
			foo['y'] = 200;

			bar['a'] = 11;
			bar['b'] = 22;
			bar['c'] = 33;

			foo.swap(bar);

			std::cout << "foo contains:\n";
			for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "bar contains:\n";
			for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

		}
		{
			ft::map<char, int> mymap;

			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;

			std::cout << "mymap contains:\n";
			for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			mymap.clear();
			mymap['a'] = 1101;
			mymap['b'] = 2202;

			std::cout << "mymap contains:\n";
			for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

		}
		{
			ft::map<char, int> mymap;

			ft::map<char, int>::key_compare mycomp = mymap.key_comp();

			mymap['a'] = 100;
			mymap['b'] = 200;
			mymap['c'] = 300;

			std::cout << "mymap contains:\n";

			char highest = mymap.rbegin()->first;     // key value of last element

			ft::map<char, int>::iterator it = mymap.begin();
			do
			{
				std::cout << it->first << " => " << it->second << '\n';
			} while (mycomp((*it++).first, highest));

			std::cout << '\n';

		}

		{
			ft::map<char, int> mymap;

			mymap['x'] = 1001;
			mymap['y'] = 2002;
			mymap['z'] = 3003;

			std::cout << "mymap contains:\n";

			ft::pair<char, int> highest = *mymap.rbegin();          // last element

			ft::map<char, int>::iterator it = mymap.begin();
			do
			{
				std::cout << it->first << " => " << it->second << '\n';
			} while (mymap.value_comp()(*it++, highest));

		}

		{
			ft::map<char, int> mymap;
			ft::map<char, int>::iterator it;

			mymap['a'] = 50;
			mymap['b'] = 100;
			mymap['c'] = 150;
			mymap['d'] = 200;

			it = mymap.find('b');
			if (it != mymap.end())
				mymap.erase(it);

			// print content:
			std::cout << "elements in mymap:" << '\n';
			std::cout << "a => " << mymap.find('a')->second << '\n';
			std::cout << "c => " << mymap.find('c')->second << '\n';
			std::cout << "d => " << mymap.find('d')->second << '\n';

		}
		{
			ft::map<char, int> mymap;
			char c;

			mymap['a'] = 101;
			mymap['c'] = 202;
			mymap['f'] = 303;

			for (c = 'a'; c < 'h'; c++)
			{
				std::cout << c;
				if (mymap.count(c) > 0)
					std::cout << " is an element of mymap.\n";
				else
					std::cout << " is not an element of mymap.\n";
			}

		}

		{
			ft::map<char, int> mymap;
			ft::map<char, int>::iterator itlow, itup;

			mymap['a'] = 20;
			mymap['b'] = 40;
			mymap['c'] = 60;
			mymap['d'] = 80;
			mymap['e'] = 100;

			itlow = mymap.lower_bound('b');  // itlow points to b
			itup = mymap.upper_bound('d');   // itup points to e (not d!)

			mymap.erase(itlow, itup);        // erases [itlow,itup)

			// print content:
			for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';


		}
		{
			ft::map<char, int> mymap;

			mymap['a'] = 10;
			mymap['b'] = 20;
			mymap['c'] = 30;

			ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
			ret = mymap.equal_range('b');

			std::cout << "lower bound points to: ";
			std::cout << ret.first->first << " => " << ret.first->second << '\n';

			std::cout << "upper bound points to: ";
			std::cout << ret.second->first << " => " << ret.second->second << '\n';


		}

		{
			int psize;
			ft::map<char, int> mymap;
			ft::pair<const char, int> *p;

			// allocate an array of 5 elements using mymap's allocator:
			p = mymap.get_allocator().allocate(5);

			// assign some values to array
			psize = sizeof(ft::map<char, int>::value_type) * 5;

			std::cout << "The allocated array has a size of " << psize << " bytes.\n";

			mymap.get_allocator().deallocate(p, 5);

		}

		std::cout << "\nset\n";
		{
			{
				ft::set<int> first;                           // empty set of ints

				int myints[] = {10, 20, 30, 40, 50};
				ft::set<int> second(myints, myints + 5);        // range

				ft::set<int> third(second);                  // a copy of second

				ft::set<int> fourth(second.begin(), second.end());  // iterator ctor.

				ft::set<int, classcomp_char> fifth;                 // class as Compare

				bool (*fn_pt)(int, int) = fncomp;
				ft::set<int, bool (*)(int, int)> sixth(fn_pt);  // function pointer as Compare

			}
			{
				int myints[] = {12, 82, 37, 64, 15};
				ft::set<int> first(myints, myints + 5);   // set with 5 ints
				ft::set<int> second;                    // empty set

				second = first;                          // now second contains the 5 ints
				first = ft::set<int>();                 // and first is empty

				std::cout << "Size of first: " << int(first.size()) << '\n';
				std::cout << "Size of second: " << int(second.size()) << '\n';
			}
			{
				int myints[] = {75, 23, 65, 42, 13};
				ft::set<int> myset(myints, myints + 5);

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;

				std::cout << '\n';

			}
			{
				int myints[] = {21, 64, 17, 78, 49};
				ft::set<int> myset(myints, myints + 5);

				ft::set<int>::reverse_iterator rit;

				std::cout << "myset contains:";
				for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
					std::cout << ' ' << *rit;

				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				myset.insert(20);
				myset.insert(30);
				myset.insert(10);

				std::cout << "myset contains:";
				while (!myset.empty())
				{
					std::cout << ' ' << *myset.begin();
					myset.erase(myset.begin());
				}
				std::cout << '\n';

			}
			{
				ft::set<int> myints;
				std::cout << "0. size: " << myints.size() << '\n';

				for (int i = 0; i < 10; ++i) myints.insert(i);
				std::cout << "1. size: " << myints.size() << '\n';

				myints.insert(100);
				std::cout << "2. size: " << myints.size() << '\n';

				myints.erase(5);
				std::cout << "3. size: " << myints.size() << '\n';

			}
			{
				int i;
				ft::set<int> myset;

				if (myset.max_size() > 1000)
				{
					for (i = 0; i < 1000; i++) myset.insert(i);
					std::cout << "The set contains 1000 elements.\n";
				} else std::cout << "The set could not hold 1000 elements.\n";

			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator it;
				ft::pair<ft::set<int>::iterator, bool> ret;

				// set some initial values:
				for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50

				ret = myset.insert(20);               // no new element inserted

				if (ret.second == false) it = ret.first;  // "it" now points to element 20

				myset.insert(it, 25);                 // max efficiency inserting
				myset.insert(it, 24);                 // max efficiency inserting
				myset.insert(it, 26);                 // no max efficiency inserting

				int myints[] = {5, 10, 15};              // 10 already in set, not inserted
				myset.insert(myints, myints + 3);

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator it;

				// insert some values:
				for (int i = 1; i < 10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

				it = myset.begin();
				++it;                                         // "it" points now to 20

				myset.erase(it);

				myset.erase(40);

				it = myset.find(60);
				myset.erase(it, myset.end());

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				int myints[] = {12, 75, 10, 32, 20, 25};
				ft::set<int> first(myints, myints + 3);     // 10,12,75
				ft::set<int> second(myints + 3, myints + 6);  // 20,25,32

				first.swap(second);

				std::cout << "first contains:";
				for (ft::set<int>::iterator it = first.begin(); it != first.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

				std::cout << "second contains:";
				for (ft::set<int>::iterator it = second.begin(); it != second.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				ft::set<int> myset;

				myset.insert(100);
				myset.insert(200);
				myset.insert(300);

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

				myset.clear();
				myset.insert(1101);
				myset.insert(2202);

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				ft::set<int> myset;
				int highest;

				ft::set<int>::key_compare mycomp = myset.key_comp();

				for (int i = 0; i <= 5; i++) myset.insert(i);

				std::cout << "myset contains:";

				highest = *myset.rbegin();
				ft::set<int>::iterator it = myset.begin();
				do
				{
					std::cout << ' ' << *it;
				} while (mycomp(*(++it), highest));

				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				ft::set<int>::value_compare mycomp = myset.value_comp();

				for (int i = 0; i <= 5; i++) myset.insert(i);

				std::cout << "myset contains:";

				int highest = *myset.rbegin();
				ft::set<int>::iterator it = myset.begin();
				do
				{
					std::cout << ' ' << *it;
				} while (mycomp(*(++it), highest));

				std::cout << '\n';
			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator it;

				// set some initial values:
				for (int i = 1; i <= 5; i++) myset.insert(i * 10);    // set: 10 20 30 40 50

				it = myset.find(20);
				myset.erase(it);
				myset.erase(myset.find(40));

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				// set some initial values:
				for (int i = 1; i < 5; ++i) myset.insert(i * 3);    // set: 3 6 9 12

				for (int i = 0; i < 10; ++i)
				{
					std::cout << i;
					if (myset.count(i) != 0)
						std::cout << " is an element of myset.\n";
					else
						std::cout << " is not an element of myset.\n";
				}
			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator itlow, itup;

				for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

				itlow = myset.lower_bound(30);                //       ^
				itup = myset.upper_bound(60);                 //                   ^

				myset.erase(itlow, itup);                     // 10 20 70 80 90

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

				ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> ret;
				ret = myset.equal_range(30);

				std::cout << "the lower bound points to: " << *ret.first << '\n';
				std::cout << "the upper bound points to: " << *ret.second << '\n';
			}
			{
				ft::set<int> myset;
				int *p;
				unsigned int i;

				// allocate an array of 5 elements using myset's allocator:
				p = myset.get_allocator().allocate(5);

				// assign some values to array
				for (i = 0; i < 5; i++) p[i] = (i + 1) * 10;

				std::cout << "The allocated array contains:";
				for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
				std::cout << '\n';

				myset.get_allocator().deallocate(p, 5);
			}
		}
		std::cout << "\nstack\n";
		{
			std::deque<int> mydeque(3, 100);          // deque with 3 elements
			ft::vector<int> myvector(2, 200);        // vector with 2 elements

			ft::stack<int> first;                    // empty stack
			ft::stack<int> second(mydeque);         // stack initialized to copy of deque

			ft::stack<int, ft::vector<int> > third;  // empty stack using vector
			ft::stack<int, ft::vector<int> > fourth(myvector);

			std::cout << "size of first: " << first.size() << '\n';
			std::cout << "size of second: " << second.size() << '\n';
			std::cout << "size of third: " << third.size() << '\n';
			std::cout << "size of fourth: " << fourth.size() << '\n';
		}
		{
			ft::stack<int> mystack;
			int sum(0);

			for (int i = 1; i <= 10; i++) mystack.push(i);

			while (!mystack.empty())
			{
				sum += mystack.top();
				mystack.pop();
			}

			std::cout << "total: " << sum << '\n';
		}
		{
			ft::stack<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i = 0; i < 5; i++) myints.push(i);
			std::cout << "1. size: " << myints.size() << '\n';

			myints.pop();
			std::cout << "2. size: " << myints.size() << '\n';
		}
		{
			ft::stack<int> mystack;

			mystack.push(10);
			mystack.push(20);

			mystack.top() -= 5;

			std::cout << "mystack.top() is now " << mystack.top() << '\n';
		}
		{
			ft::stack<int> mystack;

			for (int i = 0; i < 5; ++i) mystack.push(i);

			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
				std::cout << ' ' << mystack.top();
				mystack.pop();
			}
			std::cout << '\n';
		}
		{
			ft::stack<int> mystack;

			for (int i = 0; i < 5; ++i) mystack.push(i);

			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
				std::cout << ' ' << mystack.top();
				mystack.pop();
			}
			std::cout << '\n';
		}
	}
	unsigned int end_ft = clock();
	std::cout << "std\n";
	unsigned int start_std = clock();
	{
		{
			std::vector<int> *vec = new std::vector<int>;
			for (int i = 0; i < 1000000; ++i)
			{
				vec->push_back(i);
			}
			vec->erase(vec->begin(), vec->end());
			delete vec;
		}
		std::vector<int> a2;
		a2.push_back(0);
		a2.push_back(1);
		a2.push_back(2);
		a2.push_back(3);

		std::vector<int> a3(3);
		a3.push_back(40);
		a3.push_back(41);
		a3.push_back(42);

		std::reverse_iterator<std::vector<int>::reverse_iterator> it1(a2.rend());
		std::cout << "it1 = " << *it1 << '\n';
		std::cout << "a2.rend = " << *a2.rend() << '\n';
		it1 = std::reverse_iterator<std::vector<int>::reverse_iterator>(a2.rbegin());
		std::cout << "it1 = " << *it1 << '\n';
		std::cout << "a2.rbegin = " << *(a2.rbegin()) << '\n';
		std::reverse_iterator<std::vector<int>::reverse_iterator> it2;
		std::reverse_iterator<std::vector<int>::reverse_iterator> it3(a3.rbegin());
		it2 = it3;
		std::cout << "it2 = " << *it2 << '\n';
		std::cout << "a3.rbegin = " << *(a3.rbegin()) << '\n';

		std::vector<int> v;
		v.push_back(0);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		std::reverse_iterator<std::vector<int>::reverse_iterator> ri1(v.rbegin()),
				ri2(v.rend());
		std::cout << (ri2 - ri1) << ' ';
		std::cout << (ri1 - ri2) << '\n';

		std::cout << "is_integral:" << std::endl;
		std::cout << "char: " << std::is_integral<char>::value << std::endl;
		std::cout << "int: " << std::is_integral<int>::value << std::endl;
		std::cout << "float: " << std::is_integral<float>::value << std::endl;

		if (std::is_integral<int>())
			std::cout << "int is an integral type" << std::endl;

		// same result as:
		if (std::is_integral<int>::value)
			std::cout << "int is an integral type" << std::endl;
//	lexicographical_compare
		char foo[] = "Apple";
		char bar[] = "apartment";

		std::cout << std::boolalpha;

		std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

		std::cout << "Using default comparison (operator<): ";
		std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9);
		std::cout << '\n';

		std::cout << "Using mycomp as comparison object: ";
		std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
		std::cout << "\n\n";

//	equal
		int myints[] = {20, 40, 60, 80, 100};
		std::vector<int> myvector(myints, myints + 5);

		if (std::equal(myvector.begin(), myvector.end(), myints))
			std::cout << "The contents of both sequences are equal.\n";
		else
			std::cout << "The contents of both sequences differ.\n";

		myvector[3] = 81;

		if (std::equal(myvector.begin(), myvector.end(), myints, mypredicate))
			std::cout << "The contents of both sequences are equal.\n";
		else
			std::cout << "The contents of both sequences differ.\n\n";

//	pair constructors
		std::pair<std::string, double> product1;                     // default
		// constructor
		std::pair<std::string, double> product2("tomatoes", 2.30);   // value init
		std::pair<std::string, double> product3(product2);          // copy
		// constructor

		product1 = std::make_pair(std::string("lightbulbs"), 0.99);   // using
		// make_pair (move)

		product2.first = "shoes";                  // the type of first is string
		product2.second = 39.90;                   // the type of second is double

		std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
		std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
		std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

//	make_pair
		std::pair<int, int> f;
		std::pair<int, int> b;

		f = std::make_pair(10, 20);
		b = std::make_pair(10.5, 'A'); // ok: implicit conversion from
		// pair<double,char>

		std::cout << "foo: " << f.first << ", " << f.second << '\n';
		std::cout << "bar: " << b.first << ", " << b.second << '\n';

//  vector default constructor
		std::vector<int> std_v;
//    vector fill constructor
		std::vector<int> fill_v(4, 45);
//    push_back
		fill_v.push_back(1);
		std::cout << "\npushback fill_v: " << fill_v.back() << '\n';
//    size
		std::cout << "fill_v size: " << fill_v.size() << '\n';

//    max_size
		std::cout << "max size my vector: " << fill_v.max_size() << '\n';

//    std::vector<int> std_range_v(it1, it2);

//    vector copy constructor
		std::vector<int> copy_v(fill_v);

		for (int i = 0; i < 4; ++i)
			std::cout << copy_v[i] << '\n';
		std::cout << '\n';

		std::vector<int> std_v2(2, 20);

		std_v2.push_back(11);
		for (int i = 0; i < 3; i++)
			std::cout << std_v2[i] << '\n';
		std::cout << '\n';
//    operator=
		copy_v = std_v2;
//    operator[]
		for (int i = 0; i < 3; i++)
		{
			std::cout << "element copy_v[" << i << "]: " << copy_v[i] << '\n';
			std::cout << "element std_v2[" << i << "]: " << std_v2[i] << '\n';
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
		std::vector<int> range_v(copy_v.begin(), copy_v.end());
		std::cout << "range vector[0]: " << range_v[0] << '\n';

//    capacity
		std::cout << "\ncapacity copy_v: " << copy_v.capacity() << '\n';

//    reserve
		std::cout << "\nsize copy_v until reserve: " << copy_v.size() << '\n';
		std::cout << "capacity copy_v until reserve: " << copy_v.capacity() << '\n';
		copy_v.reserve(6);
		std::cout << "\nsize copy_v astder reserve: " << copy_v.size() << '\n';
		std::cout << "capacity copy_v astder reserve: " << copy_v.capacity() << '\n';

//    resize
		{
			std::vector<int> myvector;

			// set some initial content:
			for (int i = 1; i < 10; i++) myvector.push_back(i);

			myvector.resize(5);
			myvector.resize(8, 100);
			myvector.resize(12);

			std::cout << "myvector contains:";
			for (int i = 0; i < static_cast<int>(myvector.size()); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    empty
		std::vector<int> empty_v;

		std::cout << "\nempty empty_v: " << empty_v.empty() << '\n';
		std::cout << "empty copy_v: " << copy_v.empty() << '\n';

//    clear
		{
			std::vector<int> myvector;
			myvector.push_back(100);
			myvector.push_back(200);
			myvector.push_back(300);

			std::cout << "\nmyvector contains:";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';

			myvector.clear();
			myvector.push_back(1101);
			myvector.push_back(2202);

			std::cout << "myvector contains:";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    assign
		{
			std::vector<int> first;
			std::vector<int> second;
			std::vector<int> third;

			first.assign(7, 100);             // 7 ints with a value of 100

			std::vector<int>::iterator it;
			it = first.begin() + 1;

			second.assign(it, first.end() - 1); // the 5 central values of first

			int myints[] = {1776, 7, 4};
			third.assign(myints, myints + 3);   // assigning from array.

			std::cout << "\nSize of first: " << int(first.size()) << '\n';
			std::cout << "Size of second: " << int(second.size()) << '\n';
			std::cout << "Size of third: " << int(third.size()) << '\n';
		}

//    reverse iterators
		{
			std::vector<int> myvector(5);  // 5 default-constructed ints

			std::vector<int>::reverse_iterator rit = myvector.rbegin();

			int i = 0;
			for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
				*rit = ++i;

			std::cout << "\nmyvector contains:";
			for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}

//    pop_back
		{
			std::vector<int> myvector;
			int sum(0);
			myvector.push_back(100);
			myvector.push_back(200);
			myvector.push_back(300);

			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}

			std::cout << "\nThe elements of myvector add up to " << sum << '\n';
			std::cout << "size myvector: " << myvector.size() << '\n';
		}

//    insert
		{
			std::vector<int> myvector(3, 100);
			std::vector<int>::iterator it;

			it = myvector.begin();
			it = myvector.insert(it, 200);

			myvector.insert(it, 2, 300);

			// "it" no longer valid, get a new one:
			it = myvector.begin();
//
			std::vector<int> anothervector(2, 400);
			myvector.insert(it + 2, anothervector.begin(), anothervector.end());

			int myarray[] = {501, 502, 503};
			myvector.insert(myvector.begin(), myarray, myarray + 3);

			std::cout << "\nmyvector contains:";
			for (it = myvector.begin(); it < myvector.end(); it++)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
//       clear
		{
			std::vector<int> myvector;
			myvector.push_back(100);
			myvector.push_back(200);
			myvector.push_back(300);

			std::cout << "\nmyvector capacity: " << myvector.capacity() << '\n';
			std::cout << "myvector contains:";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';

			myvector.clear();
			myvector.push_back(1101);
			myvector.push_back(2202);
			std::cout << "myvector capacity: " << myvector.capacity() << '\n';
			std::cout << "myvector contains: ";
			for (unsigned i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    erase
		{
			std::vector<int> myvector;

			// set some values (from 1 to 10)
			for (int i = 1; i <= 10; i++) myvector.push_back(i);

			// erase the 6th element
			myvector.erase(myvector.begin() + 5);

			// erase the first 3 elements:
			myvector.erase(myvector.begin(), myvector.begin() + 3);

			std::cout << "\nmyvector contains:";
			for (unsigned i = 0; i < myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}

//    swap
		{
			std::vector<int> foo(3, 100);   // three ints with a value of 100
			std::vector<int> bar(5, 200);   // five ints with a value of 200

			foo.swap(bar);

			std::cout << "\nfoo contains:";
			for (unsigned i = 0; i < foo.size(); i++)
				std::cout << ' ' << foo[i];
			std::cout << '\n';

			std::cout << "bar contains:";
			for (unsigned i = 0; i < bar.size(); i++)
				std::cout << ' ' << bar[i];
			std::cout << '\n';
		}

//    get_allocator
		{
			std::vector<int> myvector;
			int *p;
			unsigned int i;

			// allocate an array with space for 5 elements using vector's allocator:
			p = myvector.get_allocator().allocate(5);

			// construct values in-place on the array:
			for (i = 0; i < 5; i++) myvector.get_allocator().construct(&p[i], i);

			std::cout << "\nThe allocated array contains:";
			for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
			std::cout << '\n';

			// destroy and deallocate:
			for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
			myvector.get_allocator().deallocate(p, 5);
		}

//    operator ==,!=,<,<=,>,>=
		{
			std::vector<int> alice;
			alice.push_back(1);
			alice.push_back(2);
			alice.push_back(3);
			std::vector<int> bob;
			bob.push_back(7);
			bob.push_back(8);
			bob.push_back(9);
			bob.push_back(10);
			std::vector<int> eve;
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
			std::vector<int> alice;
			alice.push_back(1);
			alice.push_back(2);
			alice.push_back(3);
			std::vector<int> bob;
			bob.push_back(7);
			bob.push_back(8);
			bob.push_back(9);
			bob.push_back(10);

			// Print state before swap
			std::cout << "\nalice: ";
			for (std::vector<int>::iterator it = alice.begin(); it != alice.end(); ++it)
				std::cout << *it << " ";
			std::cout << "\n" "bob  : ";
			for (std::vector<int>::iterator it = bob.begin(); it != bob.end(); ++it)
				std::cout << *it << " ";
			std::cout << '\n';

			std::cout << "-- SWAP\n";
			std::swap(alice, bob);

			// Print state astder swap
			std::cout << "alice: ";
			for (std::vector<int>::iterator it = alice.begin(); it != alice.end(); ++it)
				std::cout << *it << " ";
			std::cout << "\n" "bob  : ";
			for (std::vector<int>::iterator it = bob.begin(); it != bob.end(); ++it)
				std::cout << *it << " ";
			std::cout << '\n';
		}

		{
			std::vector<int> my_vector;
			for (int i = 0; i < 10; i++) my_vector.push_back(i * 10);

			std::vector<int>::iterator it = my_vector.begin();

			std::advance(it, 5);

			std::cout << "\niterator advance:\nThe sixth element in mylist is: " << *it << '\n';
		}

		{
			std::vector<int> mylist;
			for (int i = 0; i < 10; i++) mylist.push_back(i * 10);

			std::vector<int>::iterator first = mylist.begin();
			std::vector<int>::iterator last = mylist.end();

			std::cout << "\ndistance:\nThe distance is: " << std::distance(first, last) << '\n';
		}

		std::cout << "map\n\n";
		{
			std::map<char, int> first;

			first['a'] = 10;
			first['b'] = 30;
			first['c'] = 50;
			first['d'] = 70;

			std::map<char, int> second(first.begin(), first.end());

//       std::map<char,int> third (second);

			std::map<char, int, classcomp> fourth;                 // class as Compare

			bool (*fn_pt)(char, char) = fncomp;
			std::map<char, int, bool (*)(char, char)> fistdh(fn_pt);
		}
		{
			std::map<char, int> first;
			std::map<char, int> second;

			first['x'] = 8;
			first['y'] = 16;
			first['z'] = 32;

			second = first;                // second now contains 3 ints
			first = std::map<char, int>();  // and first is now empty

			std::cout << "Size of first: " << first.size() << '\n';
			std::cout << "Size of second: " << second.size() << '\n';
		}
		{
			std::map<char, int> mymap;

			mymap['b'] = 100;
			mymap['a'] = 200;
			mymap['c'] = 300;

			// show content:
			for (std::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

		}
		{
			std::map<char, int> mymap;

			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;

			// show content:
			std::map<char, int>::reverse_iterator rit;
			for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << '\n';

		}
		{
			std::map<char, int> mymap;

			mymap['a'] = 10;
			mymap['b'] = 20;
			mymap['c'] = 30;

			while (!mymap.empty())
			{
				std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
				mymap.erase(mymap.begin());
			}
		}

		{
			std::map<char, int> mymap;
			mymap['a'] = 101;
			mymap['b'] = 202;
			mymap['c'] = 302;

			std::cout << "mymap.size() is " << mymap.size() << '\n';

		}
		{
			int i;
			std::map<int, int> mymap;

			if (mymap.max_size() > 1000)
			{
				for (i = 0; i < 1000; i++) mymap[i] = 0;
				std::cout << "The map contains 1000 elements.\n";
			} else std::cout << "The map could not hold 1000 elements.\n";

		}
		{
			std::map<char, std::string> mymap;

			mymap['a'] = "an element";
			mymap['b'] = "another element";
			mymap['c'] = mymap['b'];

			std::cout << "mymap['a'] is " << mymap['a'] << '\n';
			std::cout << "mymap['b'] is " << mymap['b'] << '\n';
			std::cout << "mymap['c'] is " << mymap['c'] << '\n';
			std::cout << "mymap['d'] is " << mymap['d'] << '\n';

			std::cout << "mymap now contains " << mymap.size() << " elements.\n";

		}

		{
			std::map<char, int> mymap;

			// first insert function version (single parameter):
			mymap.insert(std::pair<char, int>('a', 100));
			mymap.insert(std::pair<char, int>('z', 200));

			std::pair<std::map<char, int>::iterator, bool> ret;
			ret = mymap.insert(std::pair<char, int>('z', 500));
			if (ret.second == false)
			{
				std::cout << "element 'z' already existed";
				std::cout << " with a value of " << ret.first->second << '\n';
			}

			// second insert function version (with hint position):
			std::map<char, int>::iterator it = mymap.begin();
			mymap.insert(it, std::pair<char, int>('b', 300));  // max efficiency inserting
			mymap.insert(it, std::pair<char, int>('c', 400));  // no max efficiency inserting

			// third insert function version (range insertion):
			std::map<char, int> anothermap;
			anothermap.insert(mymap.begin(), mymap.find('c'));

			// showing contents:
			std::cout << "mymap contains:\n";
			for (it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "anothermap contains:\n";
			for (it = anothermap.begin(); it != anothermap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}

		{
			std::map<char, int> mymap;
			std::map<char, int>::iterator it;

			// insert some values:
			mymap['a'] = 10;
			mymap['b'] = 20;
			mymap['c'] = 30;
			mymap['d'] = 40;
			mymap['e'] = 50;
			mymap['f'] = 60;

			it = mymap.find('b');
			mymap.erase(it);                   // erasing by iterator

			mymap.erase('c');                  // erasing by key

			it = mymap.find('e');

			mymap.erase(it, mymap.end());    // erasing by range
			// show content:
			for (it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		{
			std::map<char, int> foo, bar;

			foo['x'] = 100;
			foo['y'] = 200;

			bar['a'] = 11;
			bar['b'] = 22;
			bar['c'] = 33;

			foo.swap(bar);

			std::cout << "foo contains:\n";
			for (std::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "bar contains:\n";
			for (std::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

		}
		{
			std::map<char, int> mymap;

			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;

			std::cout << "mymap contains:\n";
			for (std::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			mymap.clear();
			mymap['a'] = 1101;
			mymap['b'] = 2202;

			std::cout << "mymap contains:\n";
			for (std::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

		}
		{
			std::map<char, int> mymap;

			std::map<char, int>::key_compare mycomp = mymap.key_comp();

			mymap['a'] = 100;
			mymap['b'] = 200;
			mymap['c'] = 300;

			std::cout << "mymap contains:\n";

			char highest = mymap.rbegin()->first;     // key value of last element

			std::map<char, int>::iterator it = mymap.begin();
			do
			{
				std::cout << it->first << " => " << it->second << '\n';
			} while (mycomp((*it++).first, highest));

			std::cout << '\n';

		}

		{
			std::map<char, int> mymap;

			mymap['x'] = 1001;
			mymap['y'] = 2002;
			mymap['z'] = 3003;

			std::cout << "mymap contains:\n";

			std::pair<char, int> highest = *mymap.rbegin();          // last element

			std::map<char, int>::iterator it = mymap.begin();
			do
			{
				std::cout << it->first << " => " << it->second << '\n';
			} while (mymap.value_comp()(*it++, highest));

		}

		{
			std::map<char, int> mymap;
			std::map<char, int>::iterator it;

			mymap['a'] = 50;
			mymap['b'] = 100;
			mymap['c'] = 150;
			mymap['d'] = 200;

			it = mymap.find('b');
			if (it != mymap.end())
				mymap.erase(it);

			// print content:
			std::cout << "elements in mymap:" << '\n';
			std::cout << "a => " << mymap.find('a')->second << '\n';
			std::cout << "c => " << mymap.find('c')->second << '\n';
			std::cout << "d => " << mymap.find('d')->second << '\n';

		}
		{
			std::map<char, int> mymap;
			char c;

			mymap['a'] = 101;
			mymap['c'] = 202;
			mymap['f'] = 303;

			for (c = 'a'; c < 'h'; c++)
			{
				std::cout << c;
				if (mymap.count(c) > 0)
					std::cout << " is an element of mymap.\n";
				else
					std::cout << " is not an element of mymap.\n";
			}

		}

		{
			std::map<char, int> mymap;
			std::map<char, int>::iterator itlow, itup;

			mymap['a'] = 20;
			mymap['b'] = 40;
			mymap['c'] = 60;
			mymap['d'] = 80;
			mymap['e'] = 100;

			itlow = mymap.lower_bound('b');  // itlow points to b
			itup = mymap.upper_bound('d');   // itup points to e (not d!)

			mymap.erase(itlow, itup);        // erases [itlow,itup)

			// print content:
			for (std::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';


		}
		{
			std::map<char, int> mymap;

			mymap['a'] = 10;
			mymap['b'] = 20;
			mymap['c'] = 30;

			std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
			ret = mymap.equal_range('b');

			std::cout << "lower bound points to: ";
			std::cout << ret.first->first << " => " << ret.first->second << '\n';

			std::cout << "upper bound points to: ";
			std::cout << ret.second->first << " => " << ret.second->second << '\n';


		}

		{
			int psize;
			std::map<char, int> mymap;
			std::pair<const char, int> *p;

			// allocate an array of 5 elements using mymap's allocator:
			p = mymap.get_allocator().allocate(5);

			// assign some values to array
			psize = sizeof(std::map<char, int>::value_type) * 5;

			std::cout << "The allocated array has a size of " << psize << " bytes.\n";

			mymap.get_allocator().deallocate(p, 5);

		}

		std::cout << "\nset\n";
		{
			{
				std::set<int> first;                           // empty set of ints

				int myints[] = {10, 20, 30, 40, 50};
				std::set<int> second(myints, myints + 5);        // range

				std::set<int> third(second);                  // a copy of second

				std::set<int> fourth(second.begin(), second.end());  // iterator ctor.

				std::set<int, classcomp_char> fistdh;                 // class as Compare

				bool (*fn_pt)(int, int) = fncomp;
				std::set<int, bool (*)(int, int)> sixth(fn_pt);  // function pointer as Compare

			}
			{
				int myints[] = {12, 82, 37, 64, 15};
				std::set<int> first(myints, myints + 5);   // set with 5 ints
				std::set<int> second;                    // empty set

				second = first;                          // now second contains the 5 ints
				first = std::set<int>();                 // and first is empty

				std::cout << "Size of first: " << int(first.size()) << '\n';
				std::cout << "Size of second: " << int(second.size()) << '\n';
			}
			{
				int myints[] = {75, 23, 65, 42, 13};
				std::set<int> myset(myints, myints + 5);

				std::cout << "myset contains:";
				for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;

				std::cout << '\n';

			}
			{
				int myints[] = {21, 64, 17, 78, 49};
				std::set<int> myset(myints, myints + 5);

				std::set<int>::reverse_iterator rit;

				std::cout << "myset contains:";
				for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
					std::cout << ' ' << *rit;

				std::cout << '\n';
			}
			{
				std::set<int> myset;

				myset.insert(20);
				myset.insert(30);
				myset.insert(10);

				std::cout << "myset contains:";
				while (!myset.empty())
				{
					std::cout << ' ' << *myset.begin();
					myset.erase(myset.begin());
				}
				std::cout << '\n';

			}
			{
				std::set<int> myints;
				std::cout << "0. size: " << myints.size() << '\n';

				for (int i = 0; i < 10; ++i) myints.insert(i);
				std::cout << "1. size: " << myints.size() << '\n';

				myints.insert(100);
				std::cout << "2. size: " << myints.size() << '\n';

				myints.erase(5);
				std::cout << "3. size: " << myints.size() << '\n';

			}
			{
				int i;
				std::set<int> myset;

				if (myset.max_size() > 1000)
				{
					for (i = 0; i < 1000; i++) myset.insert(i);
					std::cout << "The set contains 1000 elements.\n";
				} else std::cout << "The set could not hold 1000 elements.\n";

			}
			{
				std::set<int> myset;
				std::set<int>::iterator it;
				std::pair<std::set<int>::iterator, bool> ret;

				// set some initial values:
				for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50

				ret = myset.insert(20);               // no new element inserted

				if (ret.second == false) it = ret.first;  // "it" now points to element 20

				myset.insert(it, 25);                 // max efficiency inserting
				myset.insert(it, 24);                 // max efficiency inserting
				myset.insert(it, 26);                 // no max efficiency inserting

				int myints[] = {5, 10, 15};              // 10 already in set, not inserted
				myset.insert(myints, myints + 3);

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				std::set<int> myset;
				std::set<int>::iterator it;

				// insert some values:
				for (int i = 1; i < 10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

				it = myset.begin();
				++it;                                         // "it" points now to 20

				myset.erase(it);

				myset.erase(40);

				it = myset.find(60);
				myset.erase(it, myset.end());

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				int myints[] = {12, 75, 10, 32, 20, 25};
				std::set<int> first(myints, myints + 3);     // 10,12,75
				std::set<int> second(myints + 3, myints + 6);  // 20,25,32

				first.swap(second);

				std::cout << "first contains:";
				for (std::set<int>::iterator it = first.begin(); it != first.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

				std::cout << "second contains:";
				for (std::set<int>::iterator it = second.begin(); it != second.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				std::set<int> myset;

				myset.insert(100);
				myset.insert(200);
				myset.insert(300);

				std::cout << "myset contains:";
				for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

				myset.clear();
				myset.insert(1101);
				myset.insert(2202);

				std::cout << "myset contains:";
				for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				std::set<int> myset;
				int highest;

				std::set<int>::key_compare mycomp = myset.key_comp();

				for (int i = 0; i <= 5; i++) myset.insert(i);

				std::cout << "myset contains:";

				highest = *myset.rbegin();
				std::set<int>::iterator it = myset.begin();
				do
				{
					std::cout << ' ' << *it;
				} while (mycomp(*(++it), highest));

				std::cout << '\n';
			}
			{
				std::set<int> myset;

				std::set<int>::value_compare mycomp = myset.value_comp();

				for (int i = 0; i <= 5; i++) myset.insert(i);

				std::cout << "myset contains:";

				int highest = *myset.rbegin();
				std::set<int>::iterator it = myset.begin();
				do
				{
					std::cout << ' ' << *it;
				} while (mycomp(*(++it), highest));

				std::cout << '\n';
			}
			{
				std::set<int> myset;
				std::set<int>::iterator it;

				// set some initial values:
				for (int i = 1; i <= 5; i++) myset.insert(i * 10);    // set: 10 20 30 40 50

				it = myset.find(20);
				myset.erase(it);
				myset.erase(myset.find(40));

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				std::set<int> myset;

				// set some initial values:
				for (int i = 1; i < 5; ++i) myset.insert(i * 3);    // set: 3 6 9 12

				for (int i = 0; i < 10; ++i)
				{
					std::cout << i;
					if (myset.count(i) != 0)
						std::cout << " is an element of myset.\n";
					else
						std::cout << " is not an element of myset.\n";
				}
			}
			{
				std::set<int> myset;
				std::set<int>::iterator itlow, itup;

				for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

				itlow = myset.lower_bound(30);                //       ^
				itup = myset.upper_bound(60);                 //                   ^

				myset.erase(itlow, itup);                     // 10 20 70 80 90

				std::cout << "myset contains:";
				for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				std::set<int> myset;

				for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

				std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
				ret = myset.equal_range(30);

				std::cout << "the lower bound points to: " << *ret.first << '\n';
				std::cout << "the upper bound points to: " << *ret.second << '\n';
			}
			{
				std::set<int> myset;
				int *p;
				unsigned int i;

				// allocate an array of 5 elements using myset's allocator:
				p = myset.get_allocator().allocate(5);

				// assign some values to array
				for (i = 0; i < 5; i++) p[i] = (i + 1) * 10;

				std::cout << "The allocated array contains:";
				for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
				std::cout << '\n';

				myset.get_allocator().deallocate(p, 5);
			}
		}
		std::cout << "\nstack\n";
		{
			std::deque<int> mydeque(3, 100);          // deque with 3 elements
			std::vector<int> myvector(2, 200);        // vector with 2 elements

			std::stack<int> first;                    // empty stack
			std::stack<int> second(mydeque);         // stack initialized to copy of deque

			std::stack<int, std::vector<int> > third;  // empty stack using vector
			std::stack<int, std::vector<int> > fourth(myvector);

			std::cout << "size of first: " << first.size() << '\n';
			std::cout << "size of second: " << second.size() << '\n';
			std::cout << "size of third: " << third.size() << '\n';
			std::cout << "size of fourth: " << fourth.size() << '\n';
		}
		{
			std::stack<int> mystack;
			int sum(0);

			for (int i = 1; i <= 10; i++) mystack.push(i);

			while (!mystack.empty())
			{
				sum += mystack.top();
				mystack.pop();
			}

			std::cout << "total: " << sum << '\n';
		}
		{
			std::stack<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i = 0; i < 5; i++) myints.push(i);
			std::cout << "1. size: " << myints.size() << '\n';

			myints.pop();
			std::cout << "2. size: " << myints.size() << '\n';
		}
		{
			std::stack<int> mystack;

			mystack.push(10);
			mystack.push(20);

			mystack.top() -= 5;

			std::cout << "mystack.top() is now " << mystack.top() << '\n';
		}
		{
			std::stack<int> mystack;

			for (int i = 0; i < 5; ++i) mystack.push(i);

			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
				std::cout << ' ' << mystack.top();
				mystack.pop();
			}
			std::cout << '\n';
		}
		{
			std::stack<int> mystack;

			for (int i = 0; i < 5; ++i) mystack.push(i);

			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
				std::cout << ' ' << mystack.top();
				mystack.pop();
			}
			std::cout << '\n';
		}
	}
    unsigned int end_std = clock();
    std::cout << "ft_time: " << end_ft - start_ft << '\n';
	std::cout << "std_time: " << end_std - start_std << '\n';
    return 0;
}
