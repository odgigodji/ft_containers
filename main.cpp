#include <iostream>
//#include "test.hpp"
//#include "vectorFromStackOverflow.h"
#include <vector>
#include "vector.h"

//Allocator instance:-----
//int main()
//{
//	{
//		// default allocator for ints
//		std::allocator<int> alloc;
//
//		// demonstrating the few directly usable members
////		static_assert(std::is_same_v<int, decltype(alloc)::value_type>);
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
//

template<class T>
class tess {
public:
	typedef T ass;
};

int main() {
//	ft::Vector<int> a;
//	a.push_back(51);
//	std::cout << a.capacity() << std::endl;
//	std::cout << a[0] << std::endl;

//	std::vector
//	ft::vector

	std::vector<int>::size_type t;
	ft::vector<int, int>::const_iterator a;
	std::vector<int>::const_iterator  b;

	tess<int>::
//	std::vector<int>::ite
//	ft::vector<int>(4,6) a;

//	t = 65;
//	std::cout << t << std::endl;
	return 0;


}