//
// Created by Nelson Amerei on 10/31/21.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"
namespace ft
{
	template<class T, class Container>
		class stack {
			/*******************************************************************************
			*=================================MEMBER_TYPES=================================*
			********************************************************************************
			*___________________________________Typedefs__________________________________*
			*******************************************************************************/
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference const_reference;

			/*******************************************************************************
			*___________________________________Variables__________________________________*
			*******************************************************************************/
		private:
			container_type  					vec;

			/*******************************************************************************
			*===============================MEMBER_FUNCTIONS===============================*
			********************************************************************************
			*_________________Constructors,destructor,assignation operator_________________*
			*******************************************************************************/
			explicit stack(const Container &cont = Container()) : vec(cont) {}

			stack(const stack &other) : vec(other.vec) {}

			stack&	operator=(const stack &other) { vec = other.vec; return *this; }

		};
}

#endif //FT_CONTAINERS_STACK_HPP
