#include <iostream>
//#include "test.hpp"
//#include "vectorFromStackOverflow.h"
#include <vector>
#include "vector.hpp"

int main() {
	//ALLOCATORS---------------------------------------------------------------
	std::allocator<int> alloc;

	int *p = alloc.allocate(1); //space for one int
	alloc.deallocate(p, 1);		//and it's gone

//	int *z = nullptr;
	for(int i = 0; i < 2; i++) {
		alloc.construct(p, 5);
	}

	for(int i = 2; i < 5; i++) {
		alloc.construct(p, 3);
	}
	for(int i = 0; i < 5; i++) {
		std::cout << *p << std::endl;
	}





	//ALLOCATORS---------------------------------------------------------------
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (40,100);                // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);
//	fourth.push_back(51);


//	for(int i  = 0; i < 20; i++) {
//		std::cout << second[0] << std::endl;
//	}

	ft::vector<int> b(5,50);



	return 0;


}