#include <iostream>
//#include "test.hpp"
//#include "vectorFromStackOverflow.h"
#include <vector>
//#include "vector.hpp"



class vec {
public:

    char *_arr;

    class iterator {
    public:
        char *_ptr;

        iterator() {
            _ptr = nullptr;
        }
        explicit iterator(char *_arr) {
            _ptr = _arr;
        }
        char&        operator * () const { return *_ptr; };
    };

    std::allocator<char> _alloc;
    unsigned int _size;

    vec(const char *text, unsigned int n) {
        _arr = _alloc.allocate(n);
        _size = n;
        for(size_t i = 0; i < n; i++) {
//            std::cout << static_cast<char>(*(text + i)) << std::endl;
            _alloc.construct(_arr + i, *(text + i));
//            std::cout << "test: " << i << " " << _arr[i] << std::endl;
        }
    }
    iterator  begin() const { return iterator(_arr); }
    iterator  end() const {
        std::cout << "end: size=" << _size << " _arr + _size =" << _arr + _size - 1 << std::endl;
        return iterator(_arr + _size - 1); }
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

    vec a("hello_world", 11);
    for (int i = 0 ; i< a._size; i++) {
//        std::cout << i << " ";
        std::cout << static_cast<char>(*(a._arr + i)) << std::endl;
    }
    std::cout << "---end_print---" << std::endl;
    std::vector<int>::iterator z0;
    vec::iterator z = a.begin();
    std::cout << *z << std::endl;

    z = a.end();
    std::cout << *z << std::endl;
//    std::cout << "beg=" << a.begin() << " end=" << a.end() << std::endl;
	return 0;

}