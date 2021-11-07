//
// Created by Nelson Amerei on 10/30/21.
//

#ifndef FT_HPP
#define FT_HPP
#pragma once
#include <iostream>

namespace ft
{
	/*******************************************************************************
	*______________________________Enable_if_______________________________________*
	*******************************************************************************/
	#ifndef ENABLE_IF_HPP
	# define ENABLE_IF_HPP
	template<bool B, class T = void>
		struct    enable_if {};

	template<class T>
		struct    enable_if<true, T> { typedef T type; };
	#endif

	/*******************************************************************************
	*____________________________Iterator_traits___________________________________*
	*******************************************************************************/
	#ifndef ITERATOR_TRAITS_HPP
	# define ITERATOR_TRAITS_HPP
	template<class Category, class T>
		struct   	iterator_traits {
			typedef 	T				 value_type;
			typedef 	value_type*      pointer;
			typedef 	value_type&      reference;
			typedef 	ptrdiff_t        difference_type;
			typedef 	Category		 iterator_category;
		};
	#endif

	/*******************************************************************************
	*____________________________Reverse_iterator__________________________________*
	*******************************************************************************/
	#ifndef REVERSE_ITERATOR_HPP
	# define REVERSE_ITERATOR_HPP
	template<class Iter>
		struct    reverse_iterator {
			typedef Iter										iterator_type;
			typedef typename iterator_type::value_type			value_type;
			typedef typename iterator_type::pointer				pointer;
			typedef typename iterator_type::reference			reference;
			typedef typename iterator_type::difference_type		difference_type;
			typedef typename iterator_type::iterator_category	iterator_category;
		};
	#endif

	/*******************************************************************************
	*______________________________Equal_compare___________________________________*
	*******************************************************************************/
	#ifndef EQUAL_HPP
	# define EQUAL_HPP
	template<class InputIt1, class InputIt2>
	bool    equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for ( ; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2)
				return false;
		}
		return true;
	}
	#endif

	/*******************************************************************************
	*__________________________Lexicographical_compare_____________________________*
	*******************************************************************************/
	#ifndef LEXICOGRAPHICAL_HPP
	# define LEXICOGRAPHICAL_HPP
	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare (InputIt1 first1, InputIt1 last1, InputIt2 first2,
									 InputIt2 last2) {
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) { return false; }
			else if (*first1 < *first2) { return true; }
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	template<class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
									InputIt2 last2, Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void)++first2 )
		{
			if (comp(*first1, *first2)) { return true; }
			if (comp(*first2, *first1)) { return false; }
		}
		return (first1 == last1) && (first2 != last2);
	}
	#endif

	/*******************************************************************************
	*_________________________________Is_integral__________________________________*
	*******************************************************************************/

	#ifndef IS_INTEGRAL_HPP
	# define IS_INTEGRAL_HPP
	template <class T>
		struct is_integral : public std::integral_constant<bool, __is_integral(T)> {};
	#endif

	/*******************************************************************************
	*__________________________________Pair________________________________________*
	*******************************************************************************/
	#ifndef PAIR_HPP
	# define PAIR_HPP
	template<class T1, class T2> struct pair {

		typedef T1		first_type;
		typedef T2		second_type;

		first_type		first;
		second_type		second;

		/*
		 * Parameters:
		 *
		 * pr - Another pair object. This may be an object of the same type as the
		 * object being constructed or of a pair type whose elements' types are
		 * implicitly convertible to those in the pair being constructed.
		 *
		 * a - An object of the type of first, or some other type implicitly convertible to it.
		 *
		 * b - An object of the type of second, or some other type implicitly convertible to it.
		 *
		 * first_args, second_args - tuple objects with the arguments to be
		 * passed to the constructors of members first and second.
		 */

		/*    						CONSTRUCTORS								*/

		/*						default constructor								*/
		pair() : first(first_type()), second(second_type()) {}

		/*						initialization constructor 						*/
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		/*							move/copy constructor						*/
		template<class U, class V>
			explicit pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

			/*						ASSIGNMENT OPERATOR							*/
			pair&    operator = (const pair &orig) {
				if (this != &orig) {
					first = orig.first;
					second = orig.second;
				}
				return *this;
			}
		};
	#endif

	/*******************************************************************************
	*_____________________________Make_pair________________________________________*
	*******************************************************************************/
	#ifndef MAKE_PAIR_HPP
	# define MAKE_PAIR_HPP
	//Constructs a pair object with its first element set to x and its second element set to y.
	template<class T1, class T2> pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}
	#endif
};
#endif
