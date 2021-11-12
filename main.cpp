#include <iostream>
#include "ft.hpp"
#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
# define RED  	"\x1B[31m"
# define WTH  	"\x1B[38m"
# define GRN  	"\x1B[32m"
# define YEL  	"\x1B[33m"
# define BLU  	"\x1B[34m"
# define MAG  	"\x1B[35m"
# define CYN  	"\x1B[36m"
# define RESET	"\x1B[0m"

int main() {
	std::cout << MAG"\n/*******************************************************************************\n"
				 "*________________________ft_containers from namerei____________________________*\n"
				 "*******************************************************************************/\n\n";

	std::cout << CYN"/*******************************************************************************\n"
				 "*___________For test please open 'ft_containers-unit-test' directory___________*\n"
				 "*____________________And print in console ./start.sh___________________________*\n"
				 "*******************************************************************************/\n";

	ft::stack<int> my_stack;
	ft::vector<char> my_vector;
	ft::map<int, std::string> my_map;

	return 0;
}

