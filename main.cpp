#include <vector>
#include "vector.hpp"
//leaks --atExit -- ./a.out
#include <list>
/*
int main() {
	std::vector<int> a1 = {1, 2,3, 4};
//	ft::vector<int> m1 = {1, 2, 3, 4};
	ft::vector<int> m1;

	std::list<int> b1;
	b1.push_back(11);
	b1.push_back(12);
	b1.push_back(13);
	std::vector<int>::iterator z1 = a1.begin();
	std::list<int>::iterator z2 = b1.begin();
	m1.assign(a1.begin(), a1.end());
//	m1.assign(b1.begin(), b1.end());  //didnt work
	std::cout << m1[0] << " " << m1[1] << " " << m1[2] << std::endl;
}
 */

#include <iostream>
#include <iterator>
#include <vector>
#include <list>

template<class T>
	void my_reverse(T first, T last)
	{
		typename std::iterator_traits<T>::difference_type n = std::distance(first, last);
		for (--n; n > 0; n -= 2) {
			typename std::iterator_traits<T>::value_type tmp = *first;
			*first++ = *--last;
			*last = tmp;
		}
	}

int main()
{
	std::vector<int> v{1, 2, 3, 4, 5};
	my_reverse(v.begin(), v.end());
	for (int n : v) {
		std::cout << n << ' ';
	}
	std::cout << '\n';

	std::list<int> l{1, 2, 3, 4, 5};
	my_reverse(l.begin(), l.end());
	for (int n : l) {
		std::cout << n << ' ';
	}
	std::cout << '\n';

	int a[] = {1, 2, 3, 4, 5};
//			my_reverse(a, a + std::size(a));
	for (int n : a) {
		std::cout << n << ' ';
	}
	std::cout << '\n';

	//    std::istreambuf_iterator<char> i1(std::cin), i2;
	//    my_reverse(i1, i2); // compilation error

}