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
//	ft::vector<int> he;
//	he.assign(3,3);
//	std::cout << he[0] << " " << he[1] << " " << he[2] << std::endl;
////	std::vector<int> sys(4, 51);
//	ft::vector<int> tmp, tmp2;
//	std::vector<int> h;
//	h.assign(40000000, 1);
//	std::cout << h.capacity() << std::endl;
//	tmp.assign(40000000, 1);
//
////	for(int i = 0; i < tmp.size(); i++) {
////		std::cout << tmp[i] << " ";
////	}
//	tmp2.assign(4000, 1);
//	he.assign(tmp.begin(), tmp.end());
//	std::cout << "CAP " << he.capacity() << std::endl;
////
////	for(int i = 0; i < 30; i++) {
////		std::cout << tmp[i] << " ";
////	}
//	std::vector<int> a1;
//	a1.push_back(13);
//	std::cout << a1.capacity() << " " << a1.size() << " " << std::endl;
//
//	a1.push_back(20);
//
//	std::cout << a1.capacity() << " " << a1.size() << " " << std::endl;
//	a1.push_back(20);
//	std::cout << a1.capacity() << " " << a1.size() << " " << std::endl;
//
//	ft::vector<int> a2;
//	a2.push_back(13);
//	std::cout << a2.capacity() << " " << a2.size() << " " << std::endl;
//
//	a2.push_back(20);
//
//	std::cout << a2.capacity() << " " << a2.size() << " " << std::endl;
//	a2.push_back(20);
//	std::cout << a2.capacity() << " " << a2.size() << " " << std::endl;
//	a2.push_back(20);
//
//	for(int i = 0; i < 50; i++) {
//		a2.push_back(i);
//		std::cout << a2.capacity() << " " << a2.size() << " " << std::endl;
//	}
//	std::cout << a2.capacity() << " " << a2.size() << " " << std::endl;

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
//
//std::vector<int> t;
//t.assign(5,51);
//std::cout << "cap= " << t.capacity() << std::endl;
//
//ft::vector<int> a;
//a.assign(5, 51);
//std::cout << "cap= " << a.capacity() << std::endl;


	std::vector<int> v1;
	std::vector<int> tmp1;
	std::vector<int> vector1;
	vector1.assign(3, 3);
	tmp1.assign(40000000, 1);
	vector1.assign(tmp1.begin(), tmp1.end());
	for (size_t i = 0; i < tmp1.size(); ++i)
		v1.push_back(vector1[i]);
	v1.push_back(vector1.size());
	std::cout << vector1.capacity() << std::endl;

	std::cout << "---------------------------" << std::endl;

	std::vector<int> v;
	std::vector<int> tmp;
	ft::vector<int> vector;
	vector.assign(3, 3);
	tmp.assign(40000000, 1);
	std::cout << vector.capacity() << std::endl;

	vector.assign(tmp.begin(), tmp.end());
	std::cout << vector.capacity() << std::endl;
	for (size_t i = 0; i < tmp.size(); ++i)
		v.push_back(vector[i]);
	v.push_back(vector.size());
	std::cout << vector.capacity() << std::endl;
//	v.push_back(vector.capacity());

}
