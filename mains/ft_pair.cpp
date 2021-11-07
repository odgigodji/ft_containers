#include "../ft.hpp"
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

int main () {
	/*******************************************************************************
	*________________________________ft::pair example______________________________*
	*******************************************************************************/

	std::pair <std::string,double> product1;             // default constructor
	ft::pair <std::string,int> product_my1;

	std::pair <std::string,double> product2 ("tomatoes",2.30);// value init
	ft::pair <std::string,int> product_my2("apples", 51);

	std::pair <std::string,double> product3 (product2);          // copy constructor
	ft::pair <std::string, int> product_my3(product_my2);

	product_my3.second = 33;
	product_my1 = product_my3;
	std::cout << product_my1.first << " " << product_my1.second << std::endl;

	std::cout << "-------------------------------------------------------\n";

	/*******************************************************************************
	*________________________________ft::make_pair_________________________________*
	*******************************************************************************/

	ft::pair<int, std::string> mp1;
	mp1 = ft::make_pair(1, std::string("one"));   // using make_pair (move)

	std::cout << mp1.first << " " << mp1.second << '\n';

	ft::pair <int,int> foo;
	std::pair <int,int> bar;

	foo = ft::make_pair (10,20);
	bar = std::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
	return 0;
}