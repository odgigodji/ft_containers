#include <vector>
#include "vector.hpp"


int main() {
    std::vector<int>::iterator hh;
    std::vector<int>::iterator hh2;

    std::vector<int> h1(1,42);
    h1.push_back(51);
    std::cout << h1[0] << std::endl;
    hh = h1.begin();
//    hh = hh++;
//	hh += 5;
//	hh2 = 5 + hh;
	std::cout << hh[0] << std::endl;
    std::cout << "HH " << *hh << std::endl;
    ft::vector<int> a(5, 50);
    ft::vector<int>::iterator z;
	z++;
	ft::vector<int>::iterator z1 = z + 5;
	std::ptrdiff_t r ;
//	hh + r;
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    a[3] = 40;

    z = a.begin();
    std::cout << "first is " << *z << std::endl;
    std::cout << z[3] << std::endl;
//    z = a.end();
//    z += 3;
    std::cout << *z << std::endl;
//    z = a.end();
//    std::cout << "last is " << *z << std::endl;

//    std::cout << "-------" << std::endl;
//
//    for (int i = 0; i < a.size(); i++) {
//        std::cout << a[i] << std::endl;
//    }
    std::cout << "-------" << std::endl;
    ft::vector<int> y(5, 42);

    std::cout << *y.rend() << std::endl;
//    ++z;
//    std::cout << "now iter= " << *z << std::endl;
    for (z = a.begin(); z < a.end(); ++z) {
//        std::cout << *z << std::endl;
    }
    std::vector<int> g(5,41);

    return 0;
}