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
//    std::
std::vector<int> a0(5, 42);
std::cout << a0.size() << std::endl;
    return 0;
}