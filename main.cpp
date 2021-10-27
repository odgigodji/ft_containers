#include <iostream>
//#include "test.hpp"
//#include "vectorFromStackOverflow.h"
#include <vector>
//#include "vector.hpp"

class iterator {
public:
    char *_ptr;

    iterator() {
        _ptr = nullptr;
    }

};

class vec {
public:

    char *_arr;
    class iterator;
    std::allocator<char> _alloc;

    vec(const char *text, int n) {
        _arr = _alloc.allocate(n);
        for(size_t i = 0; i < n; i++) {
            std::cout << static_cast<char>(*(text + i)) << std::endl;
            _alloc.construct(_arr + i, *text + i);
//            std::cout << "test: " << i << " " << _arr[i] << std::endl;
        }
    }
//    iterator  begin() { return iterator(_arr); }

};



int main() {
	//ALLOCATORS---------------------------------------------------------------
	std::allocator<int> alloc;

	int *p = alloc.allocate(5); //space for one int
//	alloc.deallocate(p, 1);	 	//and it's gone

//	int *z = nullptr;
	for(int i = 0; i < 5; i++) {
		alloc.construct(p + i, i);
	}

//	for(int i = 0; i < 5; i++) {
//		std::cout << p[i] << std::endl;
//	}


	//ALLOCATORS---------------------------------------------------------------
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (40,100);                // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);
//	fourth.push_back(51);
//	for(int i  = 0; i < 20; i++) {
//		std::cout << second[0] << std::endl;
//	}

//	ft::vector<int> b(5,50);
//	std::cout << b.size() << std::endl;

//	ft::vector<int> l(b);
//	ft::vector<int> g(5, 5);
//	std::cout << l.size() << " " << l._arr[3] << std::endl;
//	std::cout << b.begin() << std::endl;

//    std::cout << a << std::endl;

    vec a("hello", 5);
    for (int i =0 ; i< 5; i++) {
//std::cout << a._arr << std::endl;

    }
    std::cout << std::endl;
	return 0;

}