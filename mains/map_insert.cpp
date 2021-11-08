#include <vector>
#include "vector.hpp"
#include "ft.hpp"
//leaks --atExit -- ./a.out
#include <list>
#include <stack>
#include "stack.hpp"
#include "map.hpp"
#include <map>

#include <iostream>
#include<cctype>
#include <stdlib.h>
//#include <conio.h>

int main() {
	std::map<int, std::string> a;
	a.insert(a.begin(), std::make_pair(51," hello "));

	return 0;
}