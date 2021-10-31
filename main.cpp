#include <vector>
#include "vector.hpp"
//leaks --atExit -- ./a.out
#include <list>

int main() {
	std::vector<int> a;
//	std::vector<int> b;
	std::cout << "cap= " << a.capacity() << std::endl;
	a.resize(5);
	std::cout << "cap= " << a.capacity() << std::endl;
}
