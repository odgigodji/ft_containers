#include <iostream>
//#include "map.hpp"
#include "MMMAp.hpp"
#include <map>
#include "ft.hpp"

int main() {

//	ft::pair<int, std::string> z(51, "hello");
//	ft::pair<int, std::string> x(63, "vay");
//
//	std::pair<int, std::string> x1(63, "vay");
//
	ft::map<int, std::string> a;
	ft::map<int, int> mp;
	std::map<int, int> mp1;

//
//	ft::map<int, std::string>::iterator b = a.begin();
//
//
//	std::map<int, std::string> zz;
//	zz.insert(x1);
//	zz.insert(std::make_pair(33, "jesus"));
//
//	a.insert(z);
//	a.insert(x);
//
//	a.insert(ft::make_pair(33, std::string("hesus")));
//
//	ft::map<int, std::string>::iterator bbb;
//	a.insert(z);
//	a.insert(x);
//	b = a.begin();
	std::cout << mp1.count(0) << std::endl;
	mp1.insert(std::make_pair(0, 0));
	std::cout << mp1.count(0) << std::endl;


	std::cout << mp.count(0) << std::endl;
	mp.insert(ft::make_pair(0, 0));
	std::cout << mp.count(0) << std::endl;
	return 0;
}


//int main()
//{
//	//	ft::map<int, std::string> a;
//
//
//	{
//		// default allocator for ints
//		std::allocator<int> alloc;
//
//		// demonstrating the few directly usable members
//		int* p = alloc.allocate(1);  // space for one int
//		alloc.deallocate(p, 1);      // and it is gone
//
//		// Even those can be used through traits though, so no need
//		using traits_t = std::allocator_traits<decltype(alloc)>; // The matching trait
//		p = traits_t::allocate(alloc, 1);
//		traits_t::construct(alloc, p, 7);       // construct the int
//		std::cout << *p << '\n';
//		traits_t::deallocate(alloc, p, 1);      // deallocate space for one int
//	}
//
//	{
//		// default allocator for strings
//		std::allocator<std::string> alloc;
//		// matching traits
//		using traits_t = std::allocator_traits<decltype(alloc)>;
//
//		// Rebinding the allocator using the trait for strings gets the same type
//		traits_t::rebind_alloc<std::string> alloc_ = alloc;
//
//		std::string* p = traits_t::allocate(alloc, 2); // space for 2 strings
//
//		traits_t::construct(alloc, p, "foo");
//		traits_t::construct(alloc, p + 1, "bar");
//
//		std::cout << p[0] << ' ' << p[1] << '\n';
//
//		traits_t::destroy(alloc, p + 1);
//		traits_t::destroy(alloc, p);
//		traits_t::deallocate(alloc, p, 2);
//	}
//}