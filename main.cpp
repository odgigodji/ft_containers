#include <vector>
#include "vector.hpp"
//leaks --atExit -- ./a.out
#include <list>
#include <stack>
#include "stack.hpp"

void test(ft::vector<int> vector) {
	std::vector<int> v;
	vector.assign(3, 3);
	std::vector<int> tmp(10000000, 4);
	ft::vector<int> tmp2(tmp.begin(), tmp.end());
	v.push_back(tmp2.size());
	v.push_back(tmp2.capacity());
	for (size_t i = 0; i < tmp.size(); ++i)
		v.push_back(tmp2[i]);
}

int main() {

	//STACK----------------------------
	/*
	std::vector<int> a;
	std::stack<int,std::vector<int>> b;
	std::stack<int> c;
	b.push(5);
	b.push(6);
	ft::stack<int,ft::vector<int>> x;
	ft::stack<int,std::vector<int>> y;
	ft::stack<int> z;
	 */

	//VECTOR----------------------------
	//resize - slow
	//assign - failed
	//push_back - slow
	//insert(singe) - slow
	//insert(fill) - slow
	//insert(range) - slow
	//swap - segfault
	//data() - not compile


	//SWAP
	/*
	std::vector<int> test(4,41);
	std::cout << test[4] << std::endl;
	ft::vector<int> swap1(3, 51);
	ft::vector<int> swap2;(3, 42);
	ft::swap(swap1, swap2);
	std::cout << swap1[0] << " " <<
	swap1[1] << " " << swap1[2]<< " " << std::endl;
	*/

	//ASSIGN
	ft::vector<int> he;
	he.assign(3,3);
	std::cout << he[0] << " " << he[1] << " " << he[2] << std::endl;
//	std::vector<int> sys(4, 51);
	ft::vector<int> tmp, tmp2;
	tmp.assign(40000000, 1);
	tmp2.assign(4000, 1);
	he.assign(tmp.begin(), tmp.end());
//	std::cout << *sys.crbegin() << std::endl;

//	sys.assign(5, 23);
//	for(int i = 0; i < sys.size(); ++i) {
//		std::cout << sys[i] << " ";
//	}
//	std::cout << "\n----------------------\n";
//
//	ft::vector<int> ass(4, 51);
//	ass.assign(5, 23);
//	for(int i = 0; i < ass.size(); ++i) {
//		std::cout << ass[i] << " ";
//	}

//	std::cout << swap2[0] << " " <<
//	swap2[1] << " " << swap2[2]<< " " << std::endl;
{
//	ft::vector<int> v;
//	test(v);
//	ft::vector<int> tmp(10000000, 4), tmp1(10000000, 5);

}

}
