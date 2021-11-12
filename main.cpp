#include <iostream>
#include "ft.hpp"
#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"


int main() {
	std::cout << "\n/*******************************************************************************\n"
				 "*________________________ft_containers from namerei____________________________*\n"
				 "*******************************************************************************/\n" << std::endl;

	std::cout << "/*******************************************************************************\n"
				 "*___________For test please open 'ft_containers-unit-test' directory___________*\n"
				 "*____________________And print in console ./start.sh___________________________*\n"
				 "*******************************************************************************/" << std::endl;

	ft::stack<int> my_stack;
	ft::vector<char> my_vector;
	ft::map<int, std::string> my_map;

	return 0;
}

