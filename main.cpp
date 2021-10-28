#include <vector>
#include "vector.hpp"

int main() {

    ft::vector<int> a(5, 51);
//    a[5] = 42;
    ft::vector<int>::iterator z;

    z = a.begin();
    std::cout << *z << std::endl;
    z = a.end();
    std::cout << "main: " << *z << std::endl;

    return 0;
}