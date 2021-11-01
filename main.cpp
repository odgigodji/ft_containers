#include <vector>
#include "vector.hpp"
//leaks --atExit -- ./a.out
#include <list>
#include <stack>
#include "stack.hpp"

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
	std::vector<int> sys(4, 51);
	std::cout << *sys.crbegin() << std::endl;
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
}
