#include <vector>
#include "vector.hpp"

int main() {

    ft::vector<int> a(5, 50);
//    a[5] = 42;
    ft::vector<int>::iterator z;

    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    a[3] = 40;

    z = a.begin();
    std::cout << "first is " << *z << std::endl;
    z = a.end();
    std::cout << "last is " << *z << std::endl;

    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << std::endl;
    }
    return 0;
}