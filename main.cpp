#include <vector>
#include "vector.hpp"
//leaks --atExit -- ./a.out

//int main() {
////	std::allocator<int> alloc;
////
////	std::vector<int> t1;
////	std::vector<int> t2(5, 51);
////	t1 < t2;
////	int *p = alloc.allocate(3); //space for one int
////	*p = 1;
////	*(p + 1) = 2;
////	*(p + 2) = 3;
//////	alloc.destroy(p); //--
//////	alloc.destroy(p + 1);
////	alloc.deallocate(p, 3); // -- free the memory
////	std::cout << p << " " << *p << std::endl;
////	std::cout << p + 1 << " " << *(p + 1) << std::endl;
////	std::cout << p + 2 << " " << *(p + 2) <<  std::endl;
////
////	std::cout << "========" << std::endl;
////	return 0;
//	//	int *z = nullptr;
////	for(int i = 0; i < 5; i++) {
////		alloc.construct(p + i, i);
////	}
////	for(int i =0; i < 5; i++) { //print
////		std::cout << p[i] << std::endl;
////	}
////	std::cout << "----------after dealloc------" << std::endl;
////	alloc.deallocate(p, 2);
////	alloc.destroy(p);
////
////
////	for(int i =0; i < 5; i++) {			//print
////		std::cout << p[i] << std::endl;
////	}
////	int goo = p[3] + 51;
////	std::cout << goo << std::endl;
////	return 0;
//
///*
//
//    std::vector<int>::iterator hh;
//    std::vector<int>::iterator hh2;
//
//    std::vector<int> h1(3,42);
//    h1.clear();
////    h1.erase(h1.begin(), h1.end());
//    std::cout << h1[2] << " " << h1.size() << " " << h1.capacity() << std::endl;
////    return 0;
//    std::cout << h1.size() << " " << h1.capacity() << std::endl;
////    h1.resize(150);
//	h1.reserve(100);
//	h1.clear();
//    std::cout << h1.size() << " " << h1.capacity() << std::endl;
////    return 0;
//
//    h1.push_back(51);
//    std::cout << h1[0] << std::endl;
//    hh = h1.begin();
////    hh = hh++;
////	hh += 5;
////	hh2 = 5 + hh;
//	std::cout << hh[0] << std::endl;
//    std::cout << "HH " << *hh << std::endl;
//
//*/
//    std::vector<int> a(5, 50);
//	ft::vector<int> b(5, 50);
//
//	ft::vector<int>::iterator z;
//	z++;
//	ft::vector<int>::iterator z1 = z + 5;
//	std::ptrdiff_t r ;
////	hh + r;
//
//    a[0] = 10;
//    a[1] = 20;
//    a[2] = 30;
//    a[3] = 40;
//
//	b[0] = 10;
//	b[1] = 20;
//	b[2] = 30;
//	b[3] = 40;
////    z = a.begin();
////    std::cout << "first is " << *z << std::endl;
////    std::cout << z[3] << std::endl;
////    z = a.end();
////    z += 3;
////    std::cout << *z << std::endl;
////    z = a.end();
////    std::cout << "last is " << *z << std::endl;
//
////    std::cout << "-------" << std::endl;
////    for (int i = 0; i < a.size(); i++) {
////        std::cout << a[i] << std::endl;
////    }
////    std::cout << "-------" << std::endl;
////	a.erase(a.begin() + 3);
////	for (int i = 0; i < a.size(); i++) {
////		std::cout << a[i] << std::endl;
////	}
////	std::cout << "-------" << std::endl;
//
//	std::cout << "-------" << std::endl;
//	for (int i = 0; i < b.size(); i++) {
//		std::cout << b[i] << std::endl;
//	}
//	std::cout << "-------" << std::endl;
////	b.erase(b.begin() + 3);
////	b.erase(b.begin() + 1, b.begin() + 3);
//	for (int i = 0; i < b.size(); i++) {
//		std::cout << b[i] << std::endl;
//	}
////	b.erase(b.begin(), b.end());
//	std::cout << "-------" << std::endl;
////	std::cout << b.empty() << std::endl;
//
///*
//    ft::vector<int> y(5, 42);
//
//    std::cout << *y.rend() << std::endl;
////    ++z;
////    std::cout << "now iter= " << *z << std::endl;
//    for (z = a.begin(); z < a.end(); ++z) {
////        std::cout << *z << std::endl;
//    }
//    std::vector<int> g(5,41);
//*/
//    return 0;
//}

int main ()
{
	std::vector<int> first;
	std::vector<int> second;
//	std::vector<int> third(5, 51);
	ft::vector<int> fifth;
//	first.assign (5,100); // 7 ints with a value of 100


//	first.push_back(51);
//	first.push_back(51);
//	first.push_back(51);
//	first.push_back(51);
//	first.push_back(51);
//	std::cout << "capacity: " << first.capacity() << std::endl;
//	std::cout << "size: " << first.size() << std::endl;
//		std::cout << "----------------" << std::endl;
//	first.assign(2,100);
//	std::cout << "capacity: " << first.capacity() << std::endl;
//	std::cout << "size: " << first.size() << std::endl;
//	for(int i = 0; i < first.size(); i++) {
//		std::cout << first[i] << std::endl;
//	}

//my----------------------------------------------------------------------
	std::cout << "capacity: " << fifth.capacity() << std::endl;
	std::cout << "size: " << fifth.size() << std::endl;
	std::cout << "----------------" << std::endl;

	fifth.assign(10, 100);
	std::cout << "capacity: " << fifth.capacity() << std::endl;
	std::cout << "size: " << fifth.size() << std::endl;
	for(int i = 0; i < fifth.size(); i++) {
		std::cout << fifth[i] << std::endl;
	}
	std::cout << "----------------" << std::endl;
//----------------------------------------------------------------------



//	std::vector<int>::iterator it;
//	it = first.begin() + 1;
//
//	second.assign (it,first.end() - 1);// the 5 central values of first
//	std::cout << "capacity: " << second.capacity() << std::endl;
//	std::cout << "size: " << second.size() << std::endl;
//	for(int i = 0; i < second.size(); i++) {
//		std::cout << second[i] << std::endl;
//	}
//	int myints[] = { 1776 ,7 ,4 };
//	third.assign (myints,myints + 3);  // assigning from array.
//
//	std::cout << "Size of first: " << int (first.size()) << '\n';
//	std::cout << "Size of second: " << int (second.size()) << '\n';
//	std::cout << "Size of third: " << int (third.size()) << '\n';

	return 0;
}
