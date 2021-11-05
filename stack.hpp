//
// Created by Nelson Amerei on 10/31/21.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"
namespace ft
{
	template<class T, class Container = ft::vector<T> >
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

		public:
			container_type getVec() const { return vec; }

			/*******************************************************************************
			*===============================MEMBER_FUNCTIONS===============================*
			********************************************************************************
			*_________________Constructors,destructor,assignation operator_________________*
			*******************************************************************************/

		public:
			explicit stack(const Container &cont = Container()) : vec(cont) {}

			stack(const stack &other) : vec(other.vec) {}

			stack&	operator=(const stack &other) { vec = other.vec; return *this; }

			/*******************************************************************************
			*______________________________Element_access__________________________________*
			*******************************************************************************/
			reference		top() { return vec.back(); }

			const_reference	top() const { return vec.back(); }

			/*******************************************************************************
			*_________________________________Capacity:____________________________________*
			*******************************************************************************/
			bool			empty() const { return vec.empty(); }

			size_t			size() const { return vec.size(); }

			/*******************************************************************************
			*__________________________________Modifiers___________________________________*
			*******************************************************************************/
			void			pop() { vec.pop_back(); }

			void			push(const_reference value) { vec.push_back(value); }
		};
	/*******************************************************************************
	*_________________________Non-member function overloads________________________*
	*******************************************************************************/
	template<class T, class Container>
	bool    operator == (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return lhs.getVec() == rhs.getVec();
	}

	template<class T, class Container>
	bool    operator != (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return lhs.getVec() != rhs.getVec();
	}

	template<class T, class Container>
	bool    operator < (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return lhs.getVec() < rhs.getVec();
	}

	template<class T, class Container>
	bool    operator > (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return lhs.getVec() > rhs.getVec();
	}

	template<class T, class Container>
	bool    operator <= (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return lhs.getVec() <= rhs.getVec();
	}

	template<class T, class Container>
	bool    operator >= (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return lhs.getVec() >= rhs.getVec();
	}
}

#endif //FT_CONTAINERS_STACK_HPP
